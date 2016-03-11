#ifndef SRC_READEROPENEXCEPTION_H_
#define SRC_READEROPENEXCEPTION_H_

#include "ReaderException.h"

namespace sph_umich_edu {

class ReaderOpenException: public ReaderException {
public:
	ReaderOpenException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~ReaderOpenException();
};

}

#endif
