#ifndef SRC_READER_H_
#define SRC_READER_H_

#include <exception>
#include <iostream>
#include <string>
#include <cstdio>

#include "ReaderException.h"
#include "ReaderOpenException.h"
#include "ReaderCloseException.h"
#include "ReaderReadException.h"

using namespace std;

namespace sph_umich_edu {

class Reader {
protected:
	string file_name;

public:
	Reader();
	virtual ~Reader();

	void set_file_name(const string& file_name);
	const string& get_file_name();

	virtual void open() throw (ReaderOpenException) = 0;
	virtual void close() throw (ReaderCloseException) = 0;
	virtual char* get_line() = 0;
	virtual long int read_line() throw (ReaderReadException) = 0;
	virtual void reset() throw (ReaderReadException) = 0;
	virtual bool eof() = 0;
	virtual bool is_open() = 0;
};

}

#endif
