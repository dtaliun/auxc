#include "include/CommandLine.h"

namespace sph_umich_edu {

const string CommandLine::HELP = "--help";
const string CommandLine::VERSION = "--version";

CommandLine::CommandLine() : option_regex("-{1,2}[a-zA-Z0-9]+") {

}

CommandLine::~CommandLine() {

}

void CommandLine::initialize_options_dictionary() {
	add_option_to_dictionary(HELP);
	add_option_to_dictionary(VERSION);
}

void CommandLine::add_option_to_dictionary(const string& option) throw (InvalidOptionException) {
	if (!regex_match(option, option_regex)) {
		throw InvalidOptionException(__FILE__, __FUNCTION__, __LINE__, option.c_str());
	}

	options_dictionary.insert(option);
}

bool CommandLine::is_option_in_dictionary(const string& option) const {
	return options_dictionary.count(option) > 0;
}

void CommandLine::read_command_line(int argc, const char* const* argv) throw (InvalidOptionException, UnknownOptionException, DuplicatedOptionException) {
	initialize_options_dictionary();

	auto options_it = options.end();
	auto options_dictionory_it = options_dictionary.end();

	for (int arg = 1; arg < argc; ++arg) {
		string value = argv[arg];

		if (regex_match(value, option_regex)) {
			options_dictionory_it = options_dictionary.find(value);
			if (options_dictionory_it != options_dictionary.end()) {
				if (options.find(value) != options.end()) {
					throw DuplicatedOptionException(__FILE__, __FUNCTION__, __LINE__, value.c_str());
				}
				options_it = options.emplace(make_pair(std::move(string(value)), vector<string>())).first;
			} else {
				throw UnknownOptionException(__FILE__, __FUNCTION__, __LINE__, value.c_str());
			}
		} else if (options_it != options.end()) {
			options_it->second.push_back(std::move(string(value)));
		} else {
			throw InvalidOptionException(__FILE__, __FUNCTION__, __LINE__, value.c_str());
		}
	}
}

unsigned int CommandLine::get_options_count() const {
	return options.size();
}

bool CommandLine::is_option_specified(const string& option) const {
	return options.count(option) > 0;
}

unsigned int CommandLine::get_arguments_count(const string& option) const {
	auto options_it = options.find(option);
	if (options_it != options.end()) {
		return options_it->second.size();
	}

	return 0u;
}

const string& CommandLine::get_argument(const string& option, unsigned int pos) const throw (CommandLineException) {
	auto options_it = options.find(option);
	if (options_it == options.end()) {
		throw CommandLineException(__FILE__, __FUNCTION__, __LINE__, "Option not found.");
	}

	if (pos >= options_it->second.size()) {
		throw CommandLineException(__FILE__, __FUNCTION__, __LINE__, "No argument at specified position.");
	}

	return options_it->second[pos];
}

}
