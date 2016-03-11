#ifndef SRC_TEXTWRITER_H_
#define SRC_TEXTWRITER_H_

#include <fstream>
#include <memory>

#include "Writer.h"
#include "WriterCreateException.h"

using namespace std;

namespace sph_umich_edu {

class TextWriter : public Writer {
private:
	char* buffer;
	unsigned int max_string_length;

	ofstream output_stream;

public:
	static const unsigned int DEFAULT_BUFFER_SIZE;

	TextWriter(unsigned int buffer_size = DEFAULT_BUFFER_SIZE) throw (WriterCreateException);
	virtual ~TextWriter();

	void open() throw (WriterOpenException);
	void close() throw (WriterCloseException);

	void write(const char* format, ...) throw (WriterWriteException);

	bool is_open();
};

}

#endif
