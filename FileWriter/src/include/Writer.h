#ifndef SRC_WRITER_H_
#define SRC_WRITER_H_

#include <exception>
#include <iostream>
#include <string>
#include <cstdarg>
#include <cstdio>

#include "WriterOpenException.h"
#include "WriterCloseException.h"
#include "WriterWriteException.h"

using namespace std;

namespace sph_umich_edu {

class Writer {
protected:
	string file_name;

public:
	Writer();
	virtual ~Writer();

	void set_file_name(const string& file_name);
	const string& get_file_name();

	virtual void open() throw (WriterOpenException) = 0;
	virtual void close() throw (WriterCloseException) = 0;

	virtual void write(const char* format, ...) throw (WriterWriteException) = 0;

	virtual bool is_open() = 0;
};

}

#endif
