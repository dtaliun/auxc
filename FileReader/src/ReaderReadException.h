#ifndef SRC_READERREADEXCEPTION_H_
#define SRC_READERREADEXCEPTION_H_

#include "ReaderException.h"

namespace sph_umich_edu {

class ReaderReadException: public ReaderException {
public:
	ReaderReadException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~ReaderReadException();
};

}

#endif
