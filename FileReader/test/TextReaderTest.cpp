#include <array>
#include <gtest/gtest.h>
#include "../src/TextReader.h"

class ReaderTestTest : public::testing::Test {
protected:
	virtual ~ReaderTestTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(ReaderTestTest, SetFileName) {
	sph_umich_edu::TextReader reader;

	reader.set_file_name("example_unix.txt");
	ASSERT_EQ("example_unix.txt", reader.get_file_name());

	reader.open();

	reader.set_file_name("example_windows.txt");
	ASSERT_EQ("example_unix.txt", reader.get_file_name());

	reader.close();

	reader.set_file_name("example_windows.txt");
	ASSERT_EQ("example_windows.txt", reader.get_file_name());
}

TEST_F(ReaderTestTest, OpenClose) {
	bool exception = false;

	try {
		sph_umich_edu::TextReader reader;
		reader.open();
	} catch (sph_umich_edu::ReaderOpenException& e) {
		exception = true;
		ASSERT_EQ("", e.get_message());
	}
	ASSERT_TRUE(exception);

	exception = false;
	try {
		sph_umich_edu::TextReader reader;
		reader.set_file_name("example_unix.txt");
		reader.open();
		reader.open();
	} catch (sph_umich_edu::ReaderOpenException& e) {
		exception = true;
		ASSERT_EQ("example_unix.txt", e.get_message());
	}
	ASSERT_FALSE(exception);

	exception = false;
	try {
		sph_umich_edu::TextReader reader;
		reader.set_file_name("example_unix.txt");
		reader.close();
	} catch (sph_umich_edu::ReaderException& e) {
		exception = true;
		ASSERT_EQ("example_unix.txt", e.get_message());
	}
	ASSERT_FALSE(exception);

}

TEST_F(ReaderTestTest, Read) {
	bool exception = false;
	array<const char*, 3> examples = {"example_unix.txt", "example_windows.txt", "example_mac.txt"};


	for (const auto& example : examples) {
		exception = false;

		try {
			sph_umich_edu::TextReader reader;
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

TEST_F(ReaderTestTest, Reset) {
	bool exception = false;

	try {
		sph_umich_edu::TextReader reader;
		reader.set_file_name("example_unix.txt");
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
		ASSERT_EQ("example_unix.txt", e.get_message());
	}
	ASSERT_FALSE(exception);
}

