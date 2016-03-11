#ifndef SRC_GZIPREADER_H_
#define SRC_GZIPREADER_H_

#include <cstring>
#include <zlib.h>

#include "Reader.h"
#include "ReaderCreateException.h"

using namespace std;

namespace sph_umich_edu {

class GzipReader : public Reader {
private:
	char* buffer;
	unsigned int max_line_length;

	gzFile gzfile;

public:
	static const unsigned int DEFAULT_BUFFER_SIZE;

	GzipReader(unsigned int buffer_size = DEFAULT_BUFFER_SIZE) throw (ReaderCreateException);
	virtual ~GzipReader();

	void open() throw (ReaderOpenException);
	void close() throw (ReaderCloseException);
	char* get_line();
	long int read_line() throw (ReaderReadException);
	void reset() throw (ReaderReadException);
	bool eof();
	bool is_open();
};

}

#endif
