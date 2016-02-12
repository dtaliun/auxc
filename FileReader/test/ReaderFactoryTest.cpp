#include <gtest/gtest.h>
#include "../src/ReaderFactory.h"

class ReaderFactoryTest : public::testing::Test {
protected:
	virtual ~ReaderFactoryTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(ReaderFactoryTest, IsGzip) {
	bool exception = false;
	bool is_gzip = false;

	try {
		is_gzip = sph_umich_edu::ReaderFactory::is_gzip("");
	} catch (sph_umich_edu::ReaderException& e) {
		exception = true;
		ASSERT_EQ("", e.get_message());
	}
	ASSERT_TRUE(exception);

	try {
		is_gzip = sph_umich_edu::ReaderFactory::is_gzip("nonexisting_file");
	} catch (sph_umich_edu::ReaderException& e) {
		exception = true;
		ASSERT_EQ("nonexisting_file", e.get_message());
	}
	ASSERT_TRUE(exception);

	is_gzip = sph_umich_edu::ReaderFactory::is_gzip("example_unix.gz");
	ASSERT_TRUE(is_gzip);

	is_gzip = sph_umich_edu::ReaderFactory::is_gzip("example_unix.txt");
	ASSERT_FALSE(is_gzip);
}

TEST_F(ReaderFactoryTest, Factory) {
	bool exception = false;

	try {
		unique_ptr<sph_umich_edu::Reader> reader(nullptr);

		reader = sph_umich_edu::ReaderFactory::create(sph_umich_edu::ReaderFactory::GZIP);
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::GzipReader*>(reader.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::TextReader*>(reader.get()));

		reader = sph_umich_edu::ReaderFactory::create(sph_umich_edu::ReaderFactory::TEXT);
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::TextReader*>(reader.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::GzipReader*>(reader.get()));

		reader = sph_umich_edu::ReaderFactory::create("");
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::TextReader*>(reader.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::GzipReader*>(reader.get()));
	} catch (sph_umich_edu::ReaderCreateException& e) {
		exception = true;
	}

	ASSERT_FALSE(exception);
}
