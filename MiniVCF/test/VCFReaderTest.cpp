#include <array>
#include <gtest/gtest.h>
#include <cmath>
#include <chrono>
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
	const char* value = nullptr;
	sph_umich_edu::ChromField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = "20";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "X";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "chr-20";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "chr_20";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "chr:20";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = "<20>";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "chr<20>";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = ".";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());
}

TEST_F(VCFReaderTest, PosField) {
	const char* value = nullptr;
	sph_umich_edu::PosField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(std::numeric_limits<long long unsigned int>::min(), field.get_value());

	value = "0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(0ul, field.get_value());

	value = "1";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1ul, field.get_value());

	value = "1000";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1000ul, field.get_value());

	value = "1099";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1099ul, field.get_value());

	value = "-1099";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(std::numeric_limits<long long unsigned int>::min(), field.get_value());

	value = "00";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(std::numeric_limits<long long unsigned int>::min(), field.get_value());

	value = ".";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(std::numeric_limits<long long unsigned int>::min(), field.get_value());
}

TEST_F(VCFReaderTest, IdField) {
	const char* value = nullptr;
	sph_umich_edu::IdField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "rs123";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("rs123", field.get_values().at(0u));

	value = "rs123;rs892";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("rs123", field.get_values().at(0u));
	ASSERT_EQ("rs892", field.get_values().at(1u));

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "..";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "rs123; rs892";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "chr20:123";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("chr20:123", field.get_values().at(0u));

	value = "rs123,rs892";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "rs123;;rs892";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, RefField) {
	const char* value = nullptr;
	sph_umich_edu::RefField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = "A";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = "AnNTNNcGC";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(value, field.get_value());

	value = ".";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = "S";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());

	value = "ABC";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ("", field.get_value());
}

TEST_F(VCFReaderTest, AltField) {
	const char* value = nullptr;
	sph_umich_edu::AltField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "A";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("A", field.get_values().at(0u));

	value = "*";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("*", field.get_values().at(0u));

	value = "An*T*NNcGC";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("An*T*NNcGC", field.get_values().at(0u));

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "..";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "AT,A,N";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("AT", field.get_values().at(0u));
	ASSERT_EQ("A", field.get_values().at(1u));
	ASSERT_EQ("N", field.get_values().at(2u));

	value = "A T,A, N";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "AT,,A,N";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "<ID>";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("<ID>", field.get_values().at(0u));

	value = "<<ID>>";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "< ID >";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "<ID1:SUBID2>";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("<ID1:SUBID2>", field.get_values().at(0u));

	value = "<ID1 SUBID2>";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_EQ(0u, field.get_values().size());

	value = "<CN0>,<CN2>";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("<CN0>", field.get_values().at(0u));
	ASSERT_EQ("<CN2>", field.get_values().at(01));
}

TEST_F(VCFReaderTest, QualField) {
	const char* value = nullptr;
	sph_umich_edu::QualField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.is_empty());
	ASSERT_TRUE(std::isnan(field.get_value()));

	value = "0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.0, field.get_value());

	value = "30";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(30.0, field.get_value());

	value = "-30";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	value = "12.2";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(12.2, field.get_value());

	value = "12.0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(12.0, field.get_value());

	value = "0.0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.0, field.get_value());

	value = "0.12";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FLOAT_EQ(0.12, field.get_value());

	value = ".12";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());

	value = "aBc";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
}

TEST_F(VCFReaderTest, FilterField) {
	const char* value = nullptr;
	sph_umich_edu::FilterField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	value = "PASS";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_TRUE(field.is_pass());
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("PASS", field.get_values().at(0u));

	value = "some filter";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	value = "filter1;filter2";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("filter1", field.get_values().at(0u));
	ASSERT_EQ("filter2", field.get_values().at(1u));

	value = "some filter1; some filter2";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());

	value = "q10;s50";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_FALSE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("q10", field.get_values().at(0u));
	ASSERT_EQ("s50", field.get_values().at(1u));

	value = "q10 ; s50";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_TRUE(field.is_empty());
	ASSERT_FALSE(field.is_pass());
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, InfoField) {
	const char* value = nullptr;
	sph_umich_edu::InfoField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(0u, field.get_values().size());

	value = "H2";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ("", field.get_values().at("H2"));

	value = "1000G";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	value = "GL.1";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("GL.1"));
	ASSERT_EQ("", field.get_values().at("GL.1"));

	value = ".1";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count(".1"));
	ASSERT_EQ("", field.get_values().at(".1"));

	value = "H2 1000G";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "H2,1000G";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "H2;1000G";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	value = "H2;;1000G";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "H2;1000G;";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("1000G"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("", field.get_values().at("1000G"));

	value = "H2;1000G;;";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "H2; ;1000G";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "AF=0.333";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("0.333", field.get_values().at("AF"));

	value = "AF = 0.333";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "twowords key=0.333";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "twowords_key=0.333";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("twowords_key"));
	ASSERT_EQ("0.333", field.get_values().at("twowords_key"));

	value = "AA=A=T";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "AF=0.333,0.667";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("0.333,0.667", field.get_values().at("AF"));

	value = "AF=0.333,,0.667";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "AF=0.333,0.667,";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "AF=0.333, 0.667";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "DP=154;MQ=52;H2";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP"));
	ASSERT_EQ(1u, field.get_values().count("MQ"));
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ("154", field.get_values().at("DP"));
	ASSERT_EQ("52", field.get_values().at("MQ"));
	ASSERT_EQ("", field.get_values().at("H2"));

	value = "DP=154; MQ=52 ;H2";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "DP=154;MQ=52;H2;AF=0.333,0.667";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(4u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP"));
	ASSERT_EQ(1u, field.get_values().count("MQ"));
	ASSERT_EQ(1u, field.get_values().count("H2"));
	ASSERT_EQ(1u, field.get_values().count("AF"));
	ASSERT_EQ("154", field.get_values().at("DP"));
	ASSERT_EQ("52", field.get_values().at("MQ"));
	ASSERT_EQ("", field.get_values().at("H2"));
	ASSERT_EQ("0.333,0.667", field.get_values().at("AF"));

	value = "CADD_RAW=-0.512010;CADD_PHRED=0.205000";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("CADD_RAW"));
	ASSERT_EQ(1u, field.get_values().count("CADD_PHRED"));
	ASSERT_EQ("-0.512010", field.get_values().at("CADD_RAW"));
	ASSERT_EQ("0.205000", field.get_values().at("CADD_PHRED"));

	value = "DP_HIST=133|365|645|904|938|854|678|480|390|237|160|91|51|33|18|8|1|3|4|2,0|0|0|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("DP_HIST"));
	ASSERT_EQ("133|365|645|904|938|854|678|480|390|237|160|91|51|33|18|8|1|3|4|2,0|0|0|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0", field.get_values().at("DP_HIST"));

	value = "CSQ=G|intergenic_variant|MODIFIER||||||||||||||||1||||||||||||||||||||||||||||||||";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(1u, field.get_values().count("CSQ"));
	ASSERT_EQ("G|intergenic_variant|MODIFIER||||||||||||||||1||||||||||||||||||||||||||||||||", field.get_values().at("CSQ"));

	value = "CSQ=G|intergenic_variant|MODIFIER|||||||||| ||||||1||||||||||| |||||||||||||||||||||";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
}

TEST_F(VCFReaderTest, FormatField) {
	const char* value = nullptr;
	sph_umich_edu::FormatField field;

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = ".";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "GT";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("GT", field.get_values().at(0u));
	ASSERT_TRUE(field.has_genotypes());

	value = "GT:";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "GT:DP";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("GT", field.get_values().at(0u));
	ASSERT_EQ("DP", field.get_values().at(1u));
	ASSERT_TRUE(field.has_genotypes());

	value = "DP:GT";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:GTA";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GTA", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:AGT";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("AGT", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:GT:GL";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:GL:GT";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:GL:AGT";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GL", field.get_values().at(1u));
	ASSERT_EQ("AGT", field.get_values().at(2u));
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:GL:GTA";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("GL", field.get_values().at(1u));
	ASSERT_EQ("GTA", field.get_values().at(2u));
	ASSERT_FALSE(field.has_genotypes());

	value = "DP:TG";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(2u, field.get_values().size());
	ASSERT_EQ("DP", field.get_values().at(0u));
	ASSERT_EQ("TG", field.get_values().at(1u));
	ASSERT_FALSE(field.has_genotypes());

	value = "GT::DP";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());

	value = "GT:.:DP";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());
	ASSERT_FALSE(field.has_genotypes());
}


TEST_F(VCFReaderTest, GenotypeField) {
	const char* value = nullptr;

	sph_umich_edu::FormatField format;
	sph_umich_edu::GenotypeField field(format);

	value = "0";
	ASSERT_EQ(0ul, sph_umich_edu::GenotypeField::toul_nocheck(value, value + strlen(value)));

	value = "1";
	ASSERT_EQ(1ul, sph_umich_edu::GenotypeField::toul_nocheck(value, value + strlen(value)));

	value = "10";
	ASSERT_EQ(10ul, sph_umich_edu::GenotypeField::toul_nocheck(value, value + strlen(value)));

	value = "1234567";
	ASSERT_EQ(1234567ul, sph_umich_edu::GenotypeField::toul_nocheck(value, value + strlen(value)));

	value = "";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = ".";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ(".", field.get_values().at(0u));

	value = ":";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "::";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = " : : ";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = ".:.:.";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(3u, field.get_values().size());
	ASSERT_EQ(".", field.get_values().at(0u));
	ASSERT_EQ(".", field.get_values().at(1u));
	ASSERT_EQ(".", field.get_values().at(2u));

	value = ".:.:";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "0/0";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(1u, field.get_values().size());
	ASSERT_EQ("0/0", field.get_values().at(0u));

	value = "0/0:255:62,0:0:0,430,2742";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_EQ(5u, field.get_values().size());
	ASSERT_EQ("0/0", field.get_values().at(0u));
	ASSERT_EQ("255", field.get_values().at(1u));
	ASSERT_EQ("62,0", field.get_values().at(2u));
	ASSERT_EQ("0", field.get_values().at(3u));
	ASSERT_EQ("0,430,2742", field.get_values().at(4u));

	value = "0/0:255:62,0:0:0,430 ,2742";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
	ASSERT_EQ(0u, field.get_values().size());

	value = "GT:DP";
	ASSERT_NO_THROW(format.parse(value, value + strlen(value)));
	ASSERT_TRUE(format.has_genotypes());

	value = ".:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	value = "./.:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	value = ".|.:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_TRUE(field.has_missing_alleles());
	ASSERT_EQ(0u, field.get_alleles().size());

	value = "12:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(1u, field.get_alleles().size());
	ASSERT_EQ(12u, field.get_alleles().at(0u));

	value = "0/11:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(2u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(11u, field.get_alleles().at(1u));

	value = "11|0:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(2u, field.get_alleles().size());
	ASSERT_EQ(11u, field.get_alleles().at(0u));
	ASSERT_EQ(0u, field.get_alleles().at(1u));

	value = "0/1/2:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_FALSE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(3u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(1u, field.get_alleles().at(1u));
	ASSERT_EQ(2u, field.get_alleles().at(2u));

	value = "0|1|2:255";
	ASSERT_NO_THROW(field.parse(value, value + strlen(value)));
	ASSERT_TRUE(field.has_genotypes());
	ASSERT_TRUE(field.is_phased());
	ASSERT_FALSE(field.has_missing_alleles());
	ASSERT_EQ(3u, field.get_alleles().size());
	ASSERT_EQ(0u, field.get_alleles().at(0u));
	ASSERT_EQ(1u, field.get_alleles().at(1u));
	ASSERT_EQ(2u, field.get_alleles().at(2u));

	value = ".|0:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "0|010|0:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|..|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|.1|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|1.|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|1.1|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|11a|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);

	value = "1|-11|1:255";
	ASSERT_THROW(field.parse(value, value + strlen(value)), sph_umich_edu::VCFException);
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

TEST_F(VCFReaderTest, Test1000GenomesSample) {
	sph_umich_edu::VCFReader vcf;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	unsigned int count = 0u;

	vcf.open("1000G_phase3.EUR.chr20.100K.vcf.gz");
	ASSERT_EQ(503u, vcf.get_variant().get_n_samples());

	start = std::chrono::system_clock::now();
	while (vcf.read_next_variant()) {
		++count;
	}
	end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	GTEST_LOG_(INFO) << "Number of variants = " << count;
	GTEST_LOG_(INFO) << "Elapsed = " << elapsed_seconds.count() << " sec";
	GTEST_LOG_(INFO) << "Speed = " << (count / elapsed_seconds.count()) << " variants/sec";

	ASSERT_EQ(100000u, count);

	vcf.close();
}



