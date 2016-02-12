#include "GzipWriter.h"

namespace sph_umich_edu {

const unsigned int GzipWriter::DEFAULT_BUFFER_SIZE = 33554432u;

GzipWriter::GzipWriter(unsigned int buffer_size) throw (WriterCreateException): buffer(nullptr), max_string_length(0u), gzfile(nullptr) {

	if (strcmp(zlibVersion(), ZLIB_VERSION) != 0) {
		throw WriterCreateException(__FILE__, __FUNCTION__, __LINE__, "Incompatible ZLIB version");
	}

	try {
		buffer = new char[buffer_size];
		max_string_length = buffer_size - 1u;
	} catch (bad_alloc& e) {
		throw WriterCreateException(__FILE__, __FUNCTION__, __LINE__, "Error in memory allocation");
	}
}

GzipWriter::~GzipWriter() {
	delete[] buffer;
	buffer = nullptr;

	if (gzfile != nullptr) {
		gzclose(gzfile);
		gzfile = nullptr;
	}
}

void GzipWriter::open() throw (WriterOpenException) {
	if (gzfile == nullptr) {
		gzfile = gzopen(file_name.c_str(), "wb");
		if (gzfile == nullptr) {
			throw WriterOpenException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

void GzipWriter::close() throw (WriterCloseException) {
	if (gzfile != nullptr) {
		int gzerrno = 0;
		gzerrno = gzclose(gzfile);
		if (gzerrno != Z_OK) {
			throw WriterCloseException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
		gzfile = nullptr;
	}
}

void GzipWriter::write(const char* format, ...) throw (WriterWriteException) {
	va_list arguments;
	long int n = 0;

	va_start(arguments, format);
	if ((n = vsnprintf(buffer, max_string_length, format, arguments)) < 0) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	} else if (n > max_string_length) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}
	va_end(arguments);

	if (gzputs(gzfile, buffer) < 0) {
		throw WriterWriteException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}
}

bool GzipWriter::is_open() {
	return gzfile != nullptr;
}

}
