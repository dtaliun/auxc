#include "include/VCFException.h"

namespace sph_umich_edu {

VCFException::VCFException(
		const char* source_file, const char* function, unsigned int line, const char* message):
				source_file(source_file), function(function), line(line), message(message) {

}

VCFException::~VCFException() {

}

const char* VCFException::what() const noexcept {
	return message.c_str();
}

const string& VCFException::get_source_file_name() {
	return source_file;
}

const string& VCFException::get_function_name() {
	return function;
}

unsigned int VCFException::get_line() {
	return line;
}

const string& VCFException::get_message() {
	return message;
}

}
