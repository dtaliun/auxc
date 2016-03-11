#include <gtest/gtest.h>
#include "../src/include/GzipWriter.h"

class GzipWriterTest : public::testing::Test {
protected:
	virtual ~GzipWriterTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(GzipWriterTest, FileName) {
	sph_umich_edu::GzipWriter writer;

	writer.set_file_name("output_file1.gz");
	ASSERT_EQ("output_file1.gz", writer.get_file_name());

	writer.open();

	writer.set_file_name("output_file2.gz");
	ASSERT_EQ("output_file1.gz", writer.get_file_name());

	writer.close();

	writer.set_file_name("output_file2.gz");
	ASSERT_EQ("output_file2.gz", writer.get_file_name());

	ASSERT_EQ(0, system("test -e output_file1.gz"));
	ASSERT_EQ(0, system("rm -f output_file1.gz"));

	ASSERT_NE(0, system("test -e output_file2.gz"));
}

TEST_F(GzipWriterTest, OpenClose) {
	bool exception = false;

	try {
		sph_umich_edu::GzipWriter writer;
		writer.open();
	} catch (sph_umich_edu::WriterOpenException& e) {
		exception = true;
		ASSERT_EQ("", e.get_message());
	}
	ASSERT_TRUE(exception);

	exception = false;
	try {
		sph_umich_edu::GzipWriter writer;
		writer.set_file_name("output_file.gz");
		writer.open();
		writer.open();
	} catch (sph_umich_edu::WriterOpenException& e) {
		exception = true;
		ASSERT_EQ("output_file.gz", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_EQ(0, system("test -e output_file.gz"));
	ASSERT_EQ(0, system("rm -f output_file.gz"));

	exception = false;
	try {
		sph_umich_edu::GzipWriter writer;
		writer.set_file_name("output_file.gz");
		writer.close();
	} catch (sph_umich_edu::WriterException& e) {
		exception = true;
		ASSERT_EQ("output_file.gz", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_NE(0, system("test -e output_file.gz"));

}

TEST_F(GzipWriterTest, Write) {
	bool exception = false;

	try {
		sph_umich_edu::GzipWriter writer;
		writer.set_file_name("output_file.gz");
		writer.write("");
	} catch (sph_umich_edu::WriterWriteException& e) {
		exception = true;
		ASSERT_EQ("output_file.gz", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_NE(0, system("test -e output_file.gz"));

	exception = false;
	try {
		sph_umich_edu::GzipWriter writer(5);
		writer.set_file_name("output_file.gz");
		writer.open();
		writer.write("0123456789\n");
	} catch (sph_umich_edu::WriterWriteException& e) {
		exception = true;
		ASSERT_EQ("output_file.gz", e.get_message());
	}
	ASSERT_TRUE(exception);
	ASSERT_EQ(0, system("test -e output_file.gz"));
	ASSERT_EQ(0, system("rm -f output_file.gz"));

	exception = false;
	try {
		sph_umich_edu::GzipWriter writer;
		writer.set_file_name("output_file.gz");
		writer.open();

		writer.write("");
		writer.write("\n");
		writer.write("Test\n");
		writer.write("%s\t%c\n", "Test", 'c');
		writer.write("%d\t%u\t%.2f\n", -1, 1u, 1.0);

		writer.close();
	} catch (sph_umich_edu::WriterException& e) {
		exception = true;
		ASSERT_EQ("output_file.gz", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_EQ(0, system("test -e output_file.gz"));
	ASSERT_EQ(0, system("diff output_file.gz example.gz"));
	ASSERT_EQ(0, system("rm -f output_file.gz"));
}
