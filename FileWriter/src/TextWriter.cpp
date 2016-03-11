#include "include/TextWriter.h"

namespace sph_umich_edu {

const unsigned int TextWriter::DEFAULT_BUFFER_SIZE = 33554432u;

TextWriter::TextWriter(unsigned int buffer_size) throw (WriterCreateException) : buffer(nullptr), max_string_length(0u) {
	try {
		buffer = new char[buffer_size];
		max_string_length = buffer_size - 1u;
	} catch (bad_alloc& e) {
		throw WriterCreateException(__FILE__, __FUNCTION__, __LINE__, "Error in memory allocation");
	}
}

TextWriter::~TextWriter() {
	delete[] buffer;
	buffer = nullptr;
}

void TextWriter::open() throw (WriterOpenException) {
	if (!output_stream.is_open()) {
		output_stream.clear();
		output_stream.open(file_name, ios::binary);
		if (output_stream.fail()) {
			throw WriterOpenException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

void TextWriter::close() throw (WriterCloseException) {
	if (output_stream.is_open()) {
		output_stream.clear();
		output_stream.close();
		if (output_stream.fail()) {
			throw WriterCloseException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

void TextWriter::write(const char* format, ...) throw (WriterWriteException) {
	va_list arguments;
	long int n = 0;

	va_start(arguments, format);
	if ((n = vsnprintf(buffer, max_string_length, format, arguments)) < 0) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	} else if (n > max_string_length) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}
	va_end(arguments);

	output_stream << buffer;

	if (output_stream.fail()) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}
}

bool TextWriter::is_open() {
	return output_stream.is_open();
}

}
