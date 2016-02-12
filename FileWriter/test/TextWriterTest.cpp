#include <gtest/gtest.h>
#include "../src/TextWriter.h"

class TextWriterTest : public::testing::Test {
protected:
	virtual ~TextWriterTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(TextWriterTest, FileName) {
	sph_umich_edu::TextWriter writer;

	writer.set_file_name("output_file1.txt");
	ASSERT_EQ("output_file1.txt", writer.get_file_name());

	writer.open();

	writer.set_file_name("output_file2.txt");
	ASSERT_EQ("output_file1.txt", writer.get_file_name());

	writer.close();

	writer.set_file_name("output_file2.txt");
	ASSERT_EQ("output_file2.txt", writer.get_file_name());

	ASSERT_EQ(0, system("test -e output_file1.txt"));
	ASSERT_EQ(0, system("rm -f output_file1.txt"));

	ASSERT_NE(0, system("test -e output_file2.txt"));
}

TEST_F(TextWriterTest, OpenClose) {
	bool exception = false;

	try {
		sph_umich_edu::TextWriter writer;
		writer.open();
	} catch (sph_umich_edu::WriterOpenException& e) {
		exception = true;
		ASSERT_EQ("", e.get_message());
	}
	ASSERT_TRUE(exception);

	exception = false;
	try {
		sph_umich_edu::TextWriter writer;
		writer.set_file_name("output_file.txt");
		writer.open();
		writer.open();
	} catch (sph_umich_edu::WriterOpenException& e) {
		exception = true;
		ASSERT_EQ("output_file.txt", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_EQ(0, system("test -e output_file.txt"));
	ASSERT_EQ(0, system("rm -f output_file.txt"));

	exception = false;
	try {
		sph_umich_edu::TextWriter writer;
		writer.set_file_name("output_file.txt");
		writer.close();
	} catch (sph_umich_edu::WriterException& e) {
		exception = true;
		ASSERT_EQ("output_file.txt", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_NE(0, system("test -e output_file.txt"));

}

TEST_F(TextWriterTest, Write) {
	bool exception = false;

	try {
		sph_umich_edu::TextWriter writer;
		writer.set_file_name("output_file.txt");
		writer.write("");
	} catch (sph_umich_edu::WriterWriteException& e) {
		exception = true;
		ASSERT_EQ("output_file.txt", e.get_message());
	}
	ASSERT_FALSE(exception);
	ASSERT_NE(0, system("test -e output_file.txt"));

	exception = false;
	try {
		sph_umich_edu::TextWriter writer(5);
		writer.set_file_name("output_file.txt");
		writer.open();
		writer.write("0123456789\n");
	} catch (sph_umich_edu::WriterWriteException& e) {
		exception = true;
		ASSERT_EQ("output_file.txt", e.get_message());
	}
	ASSERT_TRUE(exception);
	ASSERT_EQ(0, system("test -e output_file.txt"));
	ASSERT_EQ(0, system("rm -f output_file.txt"));

	exception = false;
	try {
		sph_umich_edu::TextWriter writer;
		writer.set_file_name("output_file.txt");
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
	ASSERT_EQ(0, system("test -e output_file.txt"));
	ASSERT_EQ(0, system("diff output_file.txt example.txt"));
	ASSERT_EQ(0, system("rm -f output_file.txt"));
}
