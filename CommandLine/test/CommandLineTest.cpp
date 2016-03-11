#include <gtest/gtest.h>
#include "../src/include/CommandLine.h"

class CommandLineTest : public::testing::Test {
protected:
	virtual ~CommandLineTest() {
	}

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(CommandLineTest, AddOption) {
	bool exception = false;
	sph_umich_edu::CommandLine commandLine;

	commandLine.add_option_to_dictionary("--option1");
	ASSERT_TRUE(commandLine.is_option_in_dictionary("--option1"));

	commandLine.add_option_to_dictionary("-option2");
	ASSERT_TRUE(commandLine.is_option_in_dictionary("-option2"));

	try {
		commandLine.add_option_to_dictionary("option3");
	} catch (sph_umich_edu::InvalidOptionException& e) {
		exception = true;
		ASSERT_EQ("option3", e.get_message());
		ASSERT_EQ("option3", string(e.what()));
	}

	ASSERT_TRUE(exception);
	ASSERT_FALSE(commandLine.is_option_in_dictionary("option3"));
}

TEST_F(CommandLineTest, NoOptions) {
	int argc = 1;
	const char* argv[] = {"program"};

	sph_umich_edu::CommandLine commandLine;

	commandLine.read_command_line(argc, argv);

	ASSERT_EQ(0u, commandLine.get_options_count());
	ASSERT_FALSE(commandLine.is_option_specified("--help"));
	ASSERT_THROW(commandLine.get_argument("--help", 0u), sph_umich_edu::CommandLineException);
	ASSERT_THROW(commandLine.get_argument("--help", 1u), sph_umich_edu::CommandLineException);
}

TEST_F(CommandLineTest, OptionsNoArguments) {
	int argc = 3;
	const char* argv[] = {"program", "--help", "--version"};

	sph_umich_edu::CommandLine commandLine;

	commandLine.read_command_line(argc, argv);

	ASSERT_EQ(2u, commandLine.get_options_count());
	ASSERT_TRUE(commandLine.is_option_specified("--help"));
	ASSERT_TRUE(commandLine.is_option_specified("--version"));
	ASSERT_EQ(0u, commandLine.get_arguments_count("--help"));
	ASSERT_EQ(0u, commandLine.get_arguments_count("--version"));
	ASSERT_THROW(commandLine.get_argument("--help", 0u), sph_umich_edu::CommandLineException);
	ASSERT_THROW(commandLine.get_argument("--help", 1u), sph_umich_edu::CommandLineException);
	ASSERT_THROW(commandLine.get_argument("--version", 0u), sph_umich_edu::CommandLineException);
	ASSERT_THROW(commandLine.get_argument("--version", 1u), sph_umich_edu::CommandLineException);
}

TEST_F(CommandLineTest, OptionsWithArguments) {
	int argc = 6;
	const char* argv[] = {"program", "--help", "arg1", "--version", "arg1", "arg2"};

	sph_umich_edu::CommandLine commandLine;

	commandLine.read_command_line(argc, argv);

	ASSERT_EQ(2u, commandLine.get_options_count());
	ASSERT_EQ(1u, commandLine.get_arguments_count("--help"));
	ASSERT_EQ(2u, commandLine.get_arguments_count("--version"));
	ASSERT_EQ("arg1", commandLine.get_argument("--help", 0u));
	ASSERT_THROW(commandLine.get_argument("--help", 1u), sph_umich_edu::CommandLineException);
	ASSERT_EQ("arg1", commandLine.get_argument("--version", 0u));
	ASSERT_EQ("arg2", commandLine.get_argument("--version", 1u));
	ASSERT_THROW(commandLine.get_argument("--version", 2u), sph_umich_edu::CommandLineException);
}

TEST_F(CommandLineTest, UnkownOption) {
	bool exception1 = false;
	int argc1 = 2;
	const char* argv1[] = {"program", "--opt"};
	sph_umich_edu::CommandLine commandLine1;

	try {
		commandLine1.read_command_line(argc1, argv1);
	} catch (sph_umich_edu::UnknownOptionException& e) {
		exception1 = true;
		ASSERT_EQ("--opt", e.get_message());
		ASSERT_EQ("--opt", string(e.what()));
	}
	ASSERT_TRUE(exception1);

	bool exception2 = false;
	int argc2 = 2;
	const char* argv2[] = {"program", "arg"};
	sph_umich_edu::CommandLine commandLine2;

	try {
		commandLine2.read_command_line(argc2, argv2);
	} catch (sph_umich_edu::InvalidOptionException& e) {
		exception2 = true;
		ASSERT_EQ("arg", e.get_message());
		ASSERT_EQ("arg", string(e.what()));
	}
	ASSERT_TRUE(exception2);

	bool exception3 = false;
	int argc3 = 3;
	const char* argv3[] = {"program", "--help", "--opt"};
	sph_umich_edu::CommandLine commandLine3;

	try {
		commandLine3.read_command_line(argc3, argv3);
	} catch (sph_umich_edu::UnknownOptionException& e) {
		exception3 = true;
		ASSERT_EQ("--opt", e.get_message());
		ASSERT_EQ("--opt", string(e.what()));
	}
	ASSERT_TRUE(exception3);
}

TEST_F(CommandLineTest, DuplicatedOption) {
	int argc1 = 4;
	const char* argv1[] = {"program", "--help", "arg1", "--help"};
	sph_umich_edu::CommandLine commandLine1;

	ASSERT_THROW(commandLine1.read_command_line(argc1, argv1), sph_umich_edu::DuplicatedOptionException);

	int argc2 = 4;
	const char* argv2[] = {"program", "--help", "--version", "--help"};
	sph_umich_edu::CommandLine commandLine2;

	ASSERT_THROW(commandLine2.read_command_line(argc2, argv2), sph_umich_edu::DuplicatedOptionException);
}


