#include <array>
#include <gtest/gtest.h>
#include "../src/include/GzipReader.h"

class GzipReaderTest : public::testing::Test {
protected:
	virtual ~GzipReaderTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(GzipReaderTest, SetFileName) {
	sph_umich_edu::GzipReader reader;

	reader.set_file_name("example_unix.gz");
	ASSERT_EQ("example_unix.gz", reader.get_file_name());

	reader.open();

	reader.set_file_name("example_windows.gz");
	ASSERT_EQ("example_unix.gz", reader.get_file_name());

	reader.close();

	reader.set_file_name("example_windows.gz");
	ASSERT_EQ("example_windows.gz", reader.get_file_name());
}

TEST_F(GzipReaderTest, OpenClose) {
	bool exception = false;

	try {
		sph_umich_edu::GzipReader reader;
		reader.open();
	} catch (sph_umich_edu::ReaderOpenException& e) {
		exception = true;
		ASSERT_EQ("", e.get_message());
	}
	ASSERT_TRUE(exception);

	exception = false;
	try {
		sph_umich_edu::GzipReader reader;
		reader.set_file_name("example_unix.gz");
		reader.open();
		reader.open();
	} catch (sph_umich_edu::ReaderOpenException& e) {
		exception = true;
		ASSERT_EQ("example_unix.gz", e.get_message());
	}
	ASSERT_FALSE(exception);

	exception = false;
	try {
		sph_umich_edu::GzipReader reader;
		reader.set_file_name("example_unix.gz");
		reader.close();
	} catch (sph_umich_edu::ReaderException& e) {
		exception = true;
		ASSERT_EQ("example_unix.gz", e.get_message());
	}
	ASSERT_FALSE(exception);

}

TEST_F(GzipReaderTest, Read) {
	bool exception = false;
	array<const char*, 3> examples = {"example_unix.gz", "example_windows.gz", "example_mac.gz"};

	for (const auto& example : examples) {
		exception = false;

		try {
			sph_umich_edu::GzipReader reader;
			reader.set_file_name(example);
			reader.open();

			unsigned int line_number = 0u;
			char* line = reader.get_line();

			while (reader.read_line() >= 0) {
				++line_number;
				switch (line_number) {
					case 1: ASSERT_STREQ("", line);
							break;
					case 2: ASSERT_STREQ("Line 2", line);
							break;
					case 3: ASSERT_STREQ("", line);
							break;
					case 4: ASSERT_STREQ("Line 4", line);
							break;
					case 5: ASSERT_STREQ(" \t", line);
							break;
					case 6: ASSERT_STREQ("Line 6", line);
							break;
				}
			}

			ASSERT_EQ(6u, line_number);

			reader.close();
		} catch  (sph_umich_edu::ReaderException& e) {
			exception = true;
			ASSERT_EQ(example, e.get_message());
		}

		ASSERT_FALSE(exception);
	}
}

TEST_F(GzipReaderTest, Reset) {
	bool exception = false;

	try {
		sph_umich_edu::GzipReader reader;
		reader.set_file_name("example_unix.gz");
		reader.open();

		unsigned int line_number = 0u;
		char* line = reader.get_line();

		while (reader.read_line() >= 0) {
			++line_number;
			switch (line_number) {
				case 1: ASSERT_STREQ("", line);
						break;
				case 2: ASSERT_STREQ("Line 2", line);
						break;
				case 3: ASSERT_STREQ("", line);
						break;
				case 4: ASSERT_STREQ("Line 4", line);
						break;
				case 5: ASSERT_STREQ(" \t", line);
						break;
				case 6: ASSERT_STREQ("Line 6", line);
						break;
			}
		}

		ASSERT_EQ(6u, line_number);

		reader.reset();
		line_number = 0u;

		while (reader.read_line() >= 0) {
			++line_number;
			switch (line_number) {
				case 1: ASSERT_STREQ("", line);
						break;
				case 2: ASSERT_STREQ("Line 2", line);
						break;
				case 3: ASSERT_STREQ("", line);
						break;
				case 4: ASSERT_STREQ("Line 4", line);
						break;
				case 5: ASSERT_STREQ(" \t", line);
						break;
				case 6: ASSERT_STREQ("Line 6", line);
						break;
			}
		}

		ASSERT_EQ(6u, line_number);

		reader.close();
	} catch (sph_umich_edu::ReaderException& e) {
		exception = true;
		ASSERT_EQ("example_unix.gz", e.get_message());
	}
	ASSERT_FALSE(exception);
}

