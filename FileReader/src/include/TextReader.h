 #ifndef SRC_TEXTREADER_H_
#define SRC_TEXTREADER_H_

#include <fstream>
#include <memory>

#include "Reader.h"
#include "ReaderCreateException.h"

using namespace std;

namespace sph_umich_edu {

class TextReader : public Reader {
private:
	char* buffer;
	unsigned int max_line_length;

	ifstream input_stream;

public:
	static const unsigned int DEFAULT_BUFFER_SIZE;

	TextReader(unsigned int buffer_size = DEFAULT_BUFFER_SIZE) throw (ReaderCreateException);
	virtual ~TextReader();

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
