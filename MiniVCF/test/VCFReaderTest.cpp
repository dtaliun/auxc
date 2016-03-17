#include <array>
#include <gtest/gtest.h>
#include <cmath>
#include "../src/include/VCFReader.h"

class VCFReaderTest : public::testing::Test {
protected:
	virtual ~VCFReaderTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(VCFReaderTest, ChromField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::ChromField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("20", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("X", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("chr-20", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("chr_20", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("chr:20", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("<20>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("chr<20>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
}

TEST_F(VCFReaderTest, PosField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::PosField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("1", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("1000", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("1099", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));

	ASSERT_TRUE(regex_match("-1099", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("00", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
}

TEST_F(VCFReaderTest, IdField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::IdField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("rs123", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("rs123", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("rs123;rs892", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("rs123", field.get_values().at(0u));
	ASSERT_EQ("rs892", field.get_values().at(1u));


	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("..", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("rs123; rs892", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("chr20:123", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("chr20:123", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("rs123,rs892", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("rs123;;rs892", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, RefField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::RefField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("A", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ("A", field.get_value());

	ASSERT_TRUE(regex_match("AnNTNNcGC", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ("AnNTNNcGC", field.get_value());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("S", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);

	ASSERT_TRUE(regex_match("ABC", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
}

TEST_F(VCFReaderTest, AltField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::AltField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("A", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("A", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("*", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("*", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("An*T*NNcGC", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("An*T*NNcGC", field.get_values().at(0u));

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("..", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AT,A,N", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("AT", field.get_values().at(0u));
	ASSERT_EQ("A", field.get_values().at(1u));
	ASSERT_EQ("N", field.get_values().at(2u));

	ASSERT_TRUE(regex_match("A T,A, N", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AT,,A,N", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("<ID>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("<ID>", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("<<ID>>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("< ID >", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("<ID1:SUBID2>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("<ID1:SUBID2>", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("<ID1 SUBID2>", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, QualField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::QualField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.is_empty());
	ASSERT_TRUE(std::isnan(field.get_value()));

	ASSERT_TRUE(regex_match("0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.0, field.get_value());

	ASSERT_TRUE(regex_match("30", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(30.0, field.get_value());

	ASSERT_TRUE(regex_match("-30", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	ASSERT_TRUE(regex_match("12.2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(12.2, field.get_value());

	ASSERT_TRUE(regex_match("12.0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(12.0, field.get_value());

	ASSERT_TRUE(regex_match("0.0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.0, field.get_value());

	ASSERT_TRUE(regex_match("0.12", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.12, field.get_value());

	ASSERT_TRUE(regex_match(".12", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	ASSERT_TRUE(regex_match("aBc", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
}

TEST_F(VCFReaderTest, FilterField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::FilterField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("PASS", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_TRUE(field.is_pass());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("PASS", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("some filter", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("filter1;filter2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("filter1", field.get_values().at(0u));
	ASSERT_EQ("filter2", field.get_values().at(1u));

	ASSERT_TRUE(regex_match("some filter1; some filter2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("q10;s50", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("q10", field.get_values().at(0u));
	ASSERT_EQ("s50", field.get_values().at(1u));

	ASSERT_TRUE(regex_match("q10 ; s50", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, InfoField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::InfoField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("H2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ("", field.get_values().at("H2"));

	ASSERT_TRUE(regex_match("1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	ASSERT_TRUE(regex_match("GL.1", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("GL.1"));
	ASSERT_EQ("", field.get_values().at("GL.1"));

	ASSERT_TRUE(regex_match(".1", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count(".1"));
	ASSERT_EQ("", field.get_values().at(".1"));

	ASSERT_TRUE(regex_match("H2 1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("H2,1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("H2;1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	ASSERT_TRUE(regex_match("H2;;1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("H2;1000G;", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	ASSERT_TRUE(regex_match("H2;1000G;;", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("H2; ;1000G", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AF=0.333", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("0.333", field.get_values().at("AF"));

	ASSERT_TRUE(regex_match("AF = 0.333", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("twowords key=0.333", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("twowords_key=0.333", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("twowords_key"));
	ASSERT_EQ("0.333", field.get_values().at("twowords_key"));

	ASSERT_TRUE(regex_match("AA=A=T", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AF=0.333,0.667", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("0.333,0.667", field.get_values().at("AF"));

	ASSERT_TRUE(regex_match("AF=0.333,,0.667", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AF=0.333,0.667,", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("AF=0.333, 0.667", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("DP=154;MQ=52;H2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP"));
	ASSERT_EQ(1u, field.get_values().count("MQ"));
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ("154", field.get_values().at("DP"));
	ASSERT_EQ("52", field.get_values().at("MQ"));
	ASSERT_EQ("", field.get_values().at("H2"));

	ASSERT_TRUE(regex_match("DP=154; MQ=52 ;H2", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("DP=154;MQ=52;H2;AF=0.333,0.667", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(4u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP"));
	ASSERT_EQ(1u, field.get_values().count("MQ"));
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("154", field.get_values().at("DP"));
	ASSERT_EQ("52", field.get_values().at("MQ"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("0.333,0.667", field.get_values().at("AF"));

	ASSERT_TRUE(regex_match("CADD_RAW=-0.512010;CADD_PHRED=0.205000", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("CADD_RAW"));
	ASSERT_EQ(1u, field.get_values().count("CADD_PHRED"));
	ASSERT_EQ("-0.512010", field.get_values().at("CADD_RAW"));
	ASSERT_EQ("0.205000", field.get_values().at("CADD_PHRED"));

	ASSERT_TRUE(regex_match("DP_HIST=133|365|645|904|938|854|678|480|390|237|160|91|51|33|18|8|1|3|4|2,0|0|0|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP_HIST"));
	ASSERT_EQ("133|365|645|904|938|854|678|480|390|237|160|91|51|33|18|8|1|3|4|2,0|0|0|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0", field.get_values().at("DP_HIST"));

	ASSERT_TRUE(regex_match("CSQ=G|intergenic_variant|MODIFIER||||||||||||||||1||||||||||||||||||||||||||||||||", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("CSQ"));
	ASSERT_EQ("G|intergenic_variant|MODIFIER||||||||||||||||1||||||||||||||||||||||||||||||||", field.get_values().at("CSQ"));

	ASSERT_TRUE(regex_match("CSQ=G|intergenic_variant|MODIFIER|||||||||| ||||||1||||||||||| |||||||||||||||||||||", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, FormatField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::FormatField field;

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("GT", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("GT", field.get_values().at(0u));
	ASSERT_TRUE(field.has_genotypes());

	ASSERT_TRUE(regex_match("GT:", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("GT:DP", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("GT", field.get_values().at(0u));
	ASSERT_EQ("DP", field.get_values().at(1u));
	ASSERT_TRUE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GT", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GTA", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GTA", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:AGT", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("AGT", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GT:GL", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GL:GT", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GL:AGT", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GL", field.get_values().at(1u));
	ASSERT_EQ("AGT", field.get_values().at(2u));
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:GL:GTA", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GL", field.get_values().at(1u));
	ASSERT_EQ("GTA", field.get_values().at(2u));
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("DP:TG", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("TG", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("GT::DP", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	ASSERT_TRUE(regex_match("GT:.:DP", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());
}


TEST_F(VCFReaderTest, GenotypeField) {
	regex any_regex("(.*)");
	cmatch matches;

	sph_umich_edu::FormatField format;
	sph_umich_edu::GenotypeField field(format);

	ASSERT_TRUE(regex_match("", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match(".", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(".", field.get_values().at(0u));

	ASSERT_TRUE(regex_match(":", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("::", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match(" : : ", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match(".:.:.", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ(".", field.get_values().at(0u));
	ASSERT_EQ(".", field.get_values().at(1u));
	ASSERT_EQ(".", field.get_values().at(2u));

	ASSERT_TRUE(regex_match(".:.:", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("0/0", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("0/0", field.get_values().at(0u));

	ASSERT_TRUE(regex_match("0/0:255:62,0:0:0,430,2742", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_EQ(5u, field.get_values().size());
	ASSERT_EQ("0/0", field.get_values().at(0u));
	ASSERT_EQ("255", field.get_values().at(1u));
	ASSERT_EQ("62,0", field.get_values().at(2u));
	ASSERT_EQ("0", field.get_values().at(3u));
	ASSERT_EQ("0,430,2742", field.get_values().at(4u));

	ASSERT_TRUE(regex_match("0/0:255:62,0:0:0,430 ,2742", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	ASSERT_TRUE(regex_match("GT:DP", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(format.parse(matches[1]));
	ASSERT_TRUE(format.has_genotypes());

	ASSERT_TRUE(regex_match(".:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	ASSERT_TRUE(regex_match("./.:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	ASSERT_TRUE(regex_match(".|.:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	ASSERT_TRUE(regex_match("12:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(1u, field.get_alleles().size());
	ASSERT_EQ(12u, field.get_alleles().at(0u));

	ASSERT_TRUE(regex_match("0/11:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(2u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(11u, field.get_alleles().at(1u));

	ASSERT_TRUE(regex_match("11|0:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(2u, field.get_alleles().size());
	ASSERT_EQ(11u, field.get_alleles().at(0u));
	ASSERT_EQ(0u, field.get_alleles().at(1u));

	ASSERT_TRUE(regex_match("0/1/2:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(3u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(1u, field.get_alleles().at(1u));
	ASSERT_EQ(2u, field.get_alleles().at(2u));

	ASSERT_TRUE(regex_match("0|1|2:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_NO_THROW(field.parse(matches[1]));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(3u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(1u, field.get_alleles().at(1u));
	ASSERT_EQ(2u, field.get_alleles().at(2u));

	ASSERT_TRUE(regex_match(".|0:255", matches, any_regex));
	ASSERT_EQ(2u, matches.size());
	ASSERT_THROW(field.parse(matches[1]), sph_umich_edu::VCFException);
}

TEST_F(VCFReaderTest, MetaTest) {
	sph_umich_edu::Meta meta;

	ASSERT_NO_THROW(meta.parse("##INFO=value"));
	ASSERT_THROW(meta.parse("##INFO=<value>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<value"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=value>"), sph_umich_edu::VCFException);
	ASSERT_NO_THROW(meta.parse("##INFO=<attribute1=value,attribute2=\"value\",attribute3=value>"));
	ASSERT_THROW(meta.parse("##INFO=<attribute1=value,attribute2=\"value\",attribute3=value"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=attribute1=value,attribute2=\"value\",attribute3=value>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<attribute1=value,attribute2=\"value\",attribute1=value>"), sph_umich_edu::VCFException);

	ASSERT_NO_THROW(meta.parse("##INFO=<ID=noquotes>"));
	ASSERT_THROW(meta.parse("##INFO=<ID=noqu,otes>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=noqu\"otes>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=noqu\\\"otes>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=\"noquotes>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=\\\"noquotes>"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=noquotes\">"), sph_umich_edu::VCFException);
	ASSERT_THROW(meta.parse("##INFO=<ID=noquotes\\\">"), sph_umich_edu::VCFException);
	ASSERT_NO_THROW(meta.parse("##INFO=<ID=\"quo,tes\">"));
	ASSERT_THROW(meta.parse("##INFO=<ID=\"quo\"tes\">"), sph_umich_edu::VCFException);
	ASSERT_NO_THROW(meta.parse("##INFO=<ID=\"qu\\\"ot\\\"es\">"));
	ASSERT_NO_THROW(meta.parse("##INFO=<ID=\"\">"));

	ASSERT_NO_THROW(meta.parse("##fileformat=VCFv4.2"));
	ASSERT_EQ(meta.get_key(), "fileformat");
	ASSERT_EQ(meta.get_value(), "VCFv4.2");
	ASSERT_EQ(meta.get_n_attributes(), 0u);

	ASSERT_NO_THROW(meta.parse("##filedate=2015.11.25"));
	ASSERT_EQ(meta.get_key(), "filedate");
	ASSERT_EQ(meta.get_value(), "2015.11.25");
	ASSERT_EQ(meta.get_n_attributes(), 0u);

	ASSERT_NO_THROW(meta.parse("##assembly=ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/sv/breakpoint_assemblies.fasta"));
	ASSERT_EQ(meta.get_key(), "assembly");
	ASSERT_EQ(meta.get_value(), "ftp://ftp-trace.ncbi.nih.gov/1000genomes/ftp/release/sv/breakpoint_assemblies.fasta");
	ASSERT_EQ(meta.get_n_attributes(), 0u);

	ASSERT_NO_THROW(meta.parse("##dicitionary=S0,S1,S2,S3"));
	ASSERT_EQ(meta.get_key(), "dicitionary");
	ASSERT_EQ(meta.get_value(), "S0,S1,S2,S3");
	ASSERT_EQ(meta.get_n_attributes(), 0u);

	ASSERT_NO_THROW(meta.parse("##contig=<ID=20,length=62435964,assembly=B36,md5=f126cdf8a6e0c7f379d618ff66beb2da,species=\"Homo sapiens\",taxonomy=x>"));
	ASSERT_EQ(meta.get_key(), "contig");
	ASSERT_EQ(meta.get_value(), "<ID=20,length=62435964,assembly=B36,md5=f126cdf8a6e0c7f379d618ff66beb2da,species=\"Homo sapiens\",taxonomy=x>");
	ASSERT_NO_THROW(meta.has_attribute("ID"));
	ASSERT_EQ(meta.get_attribute("ID"), "20");
	ASSERT_NO_THROW(meta.has_attribute("length"));
	ASSERT_EQ(meta.get_attribute("length"), "62435964");
	ASSERT_NO_THROW(meta.has_attribute("assembly"));
	ASSERT_EQ(meta.get_attribute("assembly"), "B36");
	ASSERT_NO_THROW(meta.has_attribute("md5"));
	ASSERT_EQ(meta.get_attribute("md5"), "f126cdf8a6e0c7f379d618ff66beb2da");
	ASSERT_NO_THROW(meta.has_attribute("species"));
	ASSERT_EQ(meta.get_attribute("species"), "\"Homo sapiens\"");
	ASSERT_NO_THROW(meta.has_attribute("taxonomy"));
	ASSERT_EQ(meta.get_attribute("taxonomy"), "x");
	ASSERT_EQ(meta.get_n_attributes(), 6u);

	ASSERT_NO_THROW(meta.parse("##contig=<ID=ctg1,URL=ftp://somewhere.org/assembly.fa>"));
	ASSERT_EQ(meta.get_key(), "contig");
	ASSERT_EQ(meta.get_value(), "<ID=ctg1,URL=ftp://somewhere.org/assembly.fa>");
	ASSERT_NO_THROW(meta.has_attribute("ID"));
	ASSERT_EQ(meta.get_attribute("ID"), "ctg1");
	ASSERT_NO_THROW(meta.has_attribute("URL"));
	ASSERT_EQ(meta.get_attribute("URL"), "ftp://somewhere.org/assembly.fa");
	ASSERT_EQ(meta.get_n_attributes(), 2u);

	ASSERT_NO_THROW(meta.parse("##FORMAT=<ID=DS,Number=1,Type=Float,Description=\"Estimated Alternate Allele Dosage : [P(0/1)+2*P(1/1)]\">"));
	ASSERT_EQ(meta.get_key(), "FORMAT");
	ASSERT_EQ(meta.get_value(), "<ID=DS,Number=1,Type=Float,Description=\"Estimated Alternate Allele Dosage : [P(0/1)+2*P(1/1)]\">");
	ASSERT_NO_THROW(meta.has_attribute("ID"));
	ASSERT_EQ(meta.get_attribute("ID"), "DS");
	ASSERT_NO_THROW(meta.has_attribute("Number"));
	ASSERT_EQ(meta.get_attribute("Number"), "1");
	ASSERT_NO_THROW(meta.has_attribute("Type"));
	ASSERT_EQ(meta.get_attribute("Type"), "Float");
	ASSERT_NO_THROW(meta.has_attribute("Description"));
	ASSERT_EQ(meta.get_attribute("Description"), "\"Estimated Alternate Allele Dosage : [P(0/1)+2*P(1/1)]\"");
	ASSERT_EQ(meta.get_n_attributes(), 4u);

	ASSERT_NO_THROW(meta.parse("##PEDIGREE=<Child=CHILD-GENOME-ID,Mother=MOTHER-GENOME-ID,Father=FATHER-GENOME-ID>"));
	ASSERT_EQ(meta.get_key(), "PEDIGREE");
	ASSERT_EQ(meta.get_value(), "<Child=CHILD-GENOME-ID,Mother=MOTHER-GENOME-ID,Father=FATHER-GENOME-ID>");
	ASSERT_NO_THROW(meta.has_attribute("Child"));
	ASSERT_EQ(meta.get_attribute("Child"), "CHILD-GENOME-ID");
	ASSERT_NO_THROW(meta.has_attribute("Mother"));
	ASSERT_EQ(meta.get_attribute("Mother"), "MOTHER-GENOME-ID");
	ASSERT_NO_THROW(meta.has_attribute("Father"));
	ASSERT_EQ(meta.get_attribute("Father"), "FATHER-GENOME-ID");
	ASSERT_EQ(meta.get_n_attributes(), 3u);

	ASSERT_NO_THROW(meta.parse("##VEP=v82 cache=/net/wonderland/home/dtaliun/.vep/homo_sapiens/82_GRCh37 db=. polyphen=2.2.2 sift=sift5.2.2 COSMIC=71 ESP=20141103 gencode=GENCODE 19 HGMD-PUBLIC=20152 genebuild=2011-04 regbuild=13 assembly=GRCh37.p13 dbSNP=144 ClinVar=201507"));
	ASSERT_EQ(meta.get_key(), "VEP");
	ASSERT_EQ(meta.get_value(), "v82 cache=/net/wonderland/home/dtaliun/.vep/homo_sapiens/82_GRCh37 db=. polyphen=2.2.2 sift=sift5.2.2 COSMIC=71 ESP=20141103 gencode=GENCODE 19 HGMD-PUBLIC=20152 genebuild=2011-04 regbuild=13 assembly=GRCh37.p13 dbSNP=144 ClinVar=201507");
	ASSERT_EQ(meta.get_n_attributes(), 0u);

	ASSERT_NO_THROW(meta.parse("##INFO=<ID=CSQ,Number=.,Type=String,Description=\"Consequence annotations from Ensembl VEP. Format: Allele|Consequence|IMPACT|SYMBOL|Gene|Feature_type|Feature|BIOTYPE|EXON|INTRON|HGVSc|HGVSp|cDNA_position|CDS_position|Protein_position|Amino_acids|Codons|Existing_variation|ALLELE_NUM|DISTANCE|STRAND|SYMBOL_SOURCE|HGNC_ID|CANONICAL|CCDS|ENSP|SWISSPROT|TREMBL|UNIPARC|SIFT|PolyPhen|DOMAINS|HGVS_OFFSET|GMAF|AFR_MAF|AMR_MAF|EAS_MAF|EUR_MAF|SAS_MAF|CLIN_SIG|SOMATIC|PHENO|PUBMED|MOTIF_NAME|MOTIF_POS|HIGH_INF_POS|MOTIF_SCORE_CHANGE|LoF|LoF_filter|LoF_flags|LoF_info\">"));
	ASSERT_EQ(meta.get_key(), "INFO");
	ASSERT_EQ(meta.get_value(), "<ID=CSQ,Number=.,Type=String,Description=\"Consequence annotations from Ensembl VEP. Format: Allele|Consequence|IMPACT|SYMBOL|Gene|Feature_type|Feature|BIOTYPE|EXON|INTRON|HGVSc|HGVSp|cDNA_position|CDS_position|Protein_position|Amino_acids|Codons|Existing_variation|ALLELE_NUM|DISTANCE|STRAND|SYMBOL_SOURCE|HGNC_ID|CANONICAL|CCDS|ENSP|SWISSPROT|TREMBL|UNIPARC|SIFT|PolyPhen|DOMAINS|HGVS_OFFSET|GMAF|AFR_MAF|AMR_MAF|EAS_MAF|EUR_MAF|SAS_MAF|CLIN_SIG|SOMATIC|PHENO|PUBMED|MOTIF_NAME|MOTIF_POS|HIGH_INF_POS|MOTIF_SCORE_CHANGE|LoF|LoF_filter|LoF_flags|LoF_info\">");
	ASSERT_NO_THROW(meta.has_attribute("ID"));
	ASSERT_EQ(meta.get_attribute("ID"), "CSQ");
	ASSERT_NO_THROW(meta.has_attribute("Number"));
	ASSERT_EQ(meta.get_attribute("Number"), ".");
	ASSERT_NO_THROW(meta.has_attribute("Type"));
	ASSERT_EQ(meta.get_attribute("Type"), "String");
	ASSERT_NO_THROW(meta.has_attribute("Description"));
	ASSERT_EQ(meta.get_attribute("Description"), "\"Consequence annotations from Ensembl VEP. Format: Allele|Consequence|IMPACT|SYMBOL|Gene|Feature_type|Feature|BIOTYPE|EXON|INTRON|HGVSc|HGVSp|cDNA_position|CDS_position|Protein_position|Amino_acids|Codons|Existing_variation|ALLELE_NUM|DISTANCE|STRAND|SYMBOL_SOURCE|HGNC_ID|CANONICAL|CCDS|ENSP|SWISSPROT|TREMBL|UNIPARC|SIFT|PolyPhen|DOMAINS|HGVS_OFFSET|GMAF|AFR_MAF|AMR_MAF|EAS_MAF|EUR_MAF|SAS_MAF|CLIN_SIG|SOMATIC|PHENO|PUBMED|MOTIF_NAME|MOTIF_POS|HIGH_INF_POS|MOTIF_SCORE_CHANGE|LoF|LoF_filter|LoF_flags|LoF_info\"");
	ASSERT_EQ(meta.get_n_attributes(), 4u);
}

TEST_F(VCFReaderTest, TestGZVCF) {
	sph_umich_edu::VCFReader vcf;
	bool has_next = false;

	vector<string> vcf_samples{"NA00001", "NA00002", "NA00003"};

	vcf.open("valid-4.1.vcf.gz");

	vector<string> read_vcf_samples = std::move(vcf.get_variant().get_samples());
	ASSERT_EQ(vcf_samples.size(), read_vcf_samples.size());
	for (unsigned int i = 0u; i < vcf_samples.size(); ++i) {
		ASSERT_EQ(vcf_samples[i], read_vcf_samples[i]);
	}

	for (unsigned int variant = 0u; variant < 12u; ++variant) {
		has_next = false;
		if ((variant == 5) || (variant == 6) || (variant == 7) || (variant == 9) || (variant == 10)) {
			ASSERT_THROW(has_next = vcf.read_next_variant(), sph_umich_edu::VCFException);
			ASSERT_FALSE(has_next);
		} else {
			ASSERT_NO_THROW(has_next = vcf.read_next_variant());
			ASSERT_TRUE(has_next);
		}
	}
	ASSERT_FALSE(vcf.read_next_variant());
	vcf.close();
}



