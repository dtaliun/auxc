#include "include/GzipReader.h"

namespace sph_umich_edu {

const unsigned int GzipReader::DEFAULT_BUFFER_SIZE = 67108864u;

GzipReader::GzipReader(unsigned int buffer_size) throw (ReaderCreateException) : buffer(nullptr), max_line_length(0u), gzfile(nullptr) {

	if (strcmp(zlibVersion(), ZLIB_VERSION) != 0) {
		throw ReaderCreateException(__FILE__, __FUNCTION__, __LINE__, "Incompatible ZLIB version");
	}

	try {
		buffer = new char[buffer_size];
		max_line_length = buffer_size - 1u;
	} catch (bad_alloc& e) {
		throw ReaderCreateException(__FILE__, __FUNCTION__, __LINE__, "Error in memory allocation");
	}
}

GzipReader::~GzipReader() {
	delete[] buffer;
	buffer = nullptr;

	if (gzfile != nullptr) {
		gzclose(gzfile);
		gzfile = nullptr;
	}
}

void GzipReader::open() throw (ReaderOpenException) {
	if (gzfile == nullptr) {
		gzfile = gzopen(file_name.c_str(), "rb");
		if (gzfile == nullptr) {
			throw ReaderOpenException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

void GzipReader::close() throw (ReaderCloseException) {
	if (gzfile != nullptr) {
		int gzerrno = 0;
		gzerrno = gzclose(gzfile);
		gzfile = nullptr;
		if (gzerrno != Z_OK) {
			throw ReaderCloseException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
		}
	}
}

char* GzipReader::get_line() {
	return buffer;
}

long int GzipReader::read_line() throw (ReaderReadException) {
	long int i = 0;
	int c = 0;

	while ((i < max_line_length) && ((c = gzgetc(gzfile)) >= 0)) {
		buffer[i] = (char)c;

		if (buffer[i] == '\n') {
			buffer[i] = '\0';
			return i;
		} else if (buffer[i] == '\r') {
			buffer[i] = '\0';
			if ((c = gzgetc(gzfile)) >= 0) {
				if ((char)c != '\n') {
					c = gzungetc(c, gzfile);
				}
			}
			return i;
		}

		i += 1;
	}

	buffer[i] = '\0';

	if ((c < 0) && (gzeof(gzfile) < 1)) {
		throw ReaderReadException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}

	return (i == 0 ? -1 : i);
}

void GzipReader::reset() throw (ReaderReadException) {
	if (gzseek(gzfile, 0L, SEEK_SET) < 0) {
		throw ReaderReadException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}
}

bool GzipReader::eof() {
	return gzeof(gzfile) > 0;
}

bool GzipReader::is_open() {
	return gzfile != nullptr;
}

}
