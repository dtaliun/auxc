#include "TextReader.h"

namespace sph_umich_edu {

const unsigned int TextReader::DEFAULT_BUFFER_SIZE = 67108864u;

TextReader::TextReader(unsigned int buffer_size) throw (ReaderCreateException): buffer(nullptr), max_line_length(0u) {
	try {
		buffer = new char[buffer_size];
		max_line_length = buffer_size - 1u;
	} catch (bad_alloc& e) {
		throw ReaderCreateException(__FILE__, __FUNCTION__, __LINE__, "Error in memory allocation");
	}
}

TextReader::~TextReader() {
	delete[] buffer;
	buffer = nullptr;
}

void TextReader::open() throw (ReaderOpenException) {
	if (!input_stream.is_open()) {
		input_stream.clear();
		input_stream.open(file_name, ios::binary);
		if (input_stream.fail()) {
			throw ReaderOpenException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

void TextReader::close() throw (ReaderCloseException) {
	if (input_stream.is_open()) {
		input_stream.clear();
		input_stream.close();
		if (input_stream.fail()) {
			throw ReaderCloseException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

char* TextReader::get_line() {
	return buffer;
}

long int TextReader::read_line() throw (ReaderReadException) {
	long int i = 0;
	int c = 0;

	while ((i < max_line_length) && ((c = input_stream.get()) != ifstream::traits_type::eof())) {
		buffer[i] = (char)c;

		if (buffer[i] == '\n') {
			buffer[i] = '\0';
			return i;
		} else if (buffer[i] == '\r') {
			buffer[i] = '\0';
			if ((c = input_stream.peek()) != ifstream::traits_type::eof()) {
				if ((char)c == '\n') {
					input_stream.ignore();
				}
			}
			return i;
		}

		i += 1;
	}

	buffer[i] = '\0';

	if (!input_stream.eof() && input_stream.fail()) {
		throw ReaderReadException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}

	return (i == 0 ? -1 : i);
}

void TextReader::reset() throw (ReaderReadException) {
	if (input_stream.is_open()) {
		input_stream.clear();
		input_stream.seekg((streampos)0, ifstream::beg);
		if (input_stream.fail()) {
			throw ReaderReadException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

bool TextReader::eof() {
	return input_stream.eof();
}

bool TextReader::is_open() {
	return input_stream.is_open();
}

}
