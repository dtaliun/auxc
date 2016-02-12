#ifndef SRC_READERCLOSEEXCEPTION_H_
#define SRC_READERCLOSEEXCEPTION_H_

#include "ReaderException.h"

namespace sph_umich_edu {

class ReaderCloseException: public ReaderException {
public:
	ReaderCloseException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~ReaderCloseException();
};

}

#endif
