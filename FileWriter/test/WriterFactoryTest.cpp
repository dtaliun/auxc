#include <gtest/gtest.h>
#include "../src/include/WriterFactory.h"

class WriterFactoryTest : public::testing::Test {
protected:
	virtual ~WriterFactoryTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(WriterFactoryTest, Factory) {
	bool exception = false;

	try {
		unique_ptr<sph_umich_edu::Writer> writer(nullptr);

		writer = sph_umich_edu::WriterFactory::create(sph_umich_edu::WriterFactory::GZIP);
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::GzipWriter*>(writer.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::TextWriter*>(writer.get()));

		writer = sph_umich_edu::WriterFactory::create(sph_umich_edu::WriterFactory::TEXT);
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::TextWriter*>(writer.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::GzipWriter*>(writer.get()));

		writer = sph_umich_edu::WriterFactory::create("");
		ASSERT_NE(nullptr, dynamic_cast<sph_umich_edu::TextWriter*>(writer.get()));
		ASSERT_EQ(nullptr, dynamic_cast<sph_umich_edu::GzipWriter*>(writer.get()));
	} catch (sph_umich_edu::WriterCreateException& e) {
		exception = true;
	}

	ASSERT_FALSE(exception);
}
