#include "CommandLineException.h"

namespace sph_umich_edu {

CommandLineException::CommandLineException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				source_file(source_file), function(function), line(line), message(message) {

}

CommandLineException::~CommandLineException() {

}

const char* CommandLineException::what() const noexcept {
	return message.c_str();
}

const string& CommandLineException::get_source_file_name() {
	return source_file;
}

const string& CommandLineException::get_function_name() {
	return function;
}

unsigned int CommandLineException::get_line() {
	return line;
}

const string& CommandLineException::get_message() {
	return message;
}

}
