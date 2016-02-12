#include "ReaderException.h"

namespace sph_umich_edu {

ReaderException::ReaderException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				source_file(source_file), function(function), line(line), message(message) {

}

ReaderException::~ReaderException() {

}

const char* ReaderException::what() const noexcept {
	return message.c_str();
}

const string& ReaderException::get_source_file_name() {
	return source_file;
}

const string& ReaderException::get_function_name() {
	return function;
}

unsigned int ReaderException::get_line() {
	return line;
}

const string& ReaderException::get_message() {
	return message;
}

}
