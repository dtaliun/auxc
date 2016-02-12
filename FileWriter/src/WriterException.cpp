#include "WriterException.h"

namespace sph_umich_edu {

WriterException::WriterException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				source_file(source_file), function(function), line(line), message(message) {

}

WriterException::~WriterException() {

}

const char* WriterException::what() const noexcept {
	return message.c_str();
}

const string& WriterException::get_source_file_name() {
	return source_file;
}

const string& WriterException::get_function_name() {
	return function;
}

unsigned int WriterException::get_line() {
	return line;
}

const string& WriterException::get_message() {
	return message;
}

}
