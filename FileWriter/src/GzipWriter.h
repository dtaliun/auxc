#ifndef SRC_GZIPWRITER_H_
#define SRC_GZIPWRITER_H_

#include <cstring>
#include <zlib.h>

#include "Writer.h"
#include "WriterCreateException.h"

using namespace std;

namespace sph_umich_edu {

class GzipWriter : public Writer {
private:
	char* buffer;
	unsigned int max_string_length;

	gzFile gzfile;

public:
	static const unsigned int DEFAULT_BUFFER_SIZE;

	GzipWriter(unsigned int buffer_size = DEFAULT_BUFFER_SIZE) throw (WriterCreateException);
	virtual ~GzipWriter();

	void open() throw (WriterOpenException);
	void close() throw (WriterCloseException);

	void write(const char* format, ...) throw (WriterWriteException);

	bool is_open();
};

}

#endif
