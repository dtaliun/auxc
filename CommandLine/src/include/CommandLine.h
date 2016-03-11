#ifndef SRC_COMMANDLINE_H_
#define SRC_COMMANDLINE_H_

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <regex>

#include "DuplicatedOptionException.h"
#include "InvalidOptionException.h"
#include "UnknownOptionException.h"

using namespace std;

namespace sph_umich_edu {

class CommandLine {
protected:
	regex option_regex;

	unordered_set<string> options_dictionary;
//	unordered_set<string>::iterator options_dictionory_it;
	unordered_map<string, vector<string>> options;
//	unordered_map<string, vector<string>>::iterator options_it;

	virtual void initialize_options_dictionary();

public:
	static const string HELP;
	static const string VERSION;

	CommandLine();
	virtual ~CommandLine();

	void add_option_to_dictionary(const string& option) throw (InvalidOptionException);
	bool is_option_in_dictionary(const string& option) const;

	void read_command_line(int args, const char* const* argv) throw (InvalidOptionException, UnknownOptionException, DuplicatedOptionException);

	unsigned int get_options_count() const;
	bool is_option_specified(const string& option) const;
	unsigned int get_arguments_count(const string& option) const;
	const string& get_argument(const string& option, unsigned int pos) const throw (CommandLineException);
};

}

#endif
