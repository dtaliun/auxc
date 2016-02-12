#ifndef SRC_READERCREATEEXCEPTION_H_
#define SRC_READERCREATEEXCEPTION_H_

#include "ReaderException.h"

namespace sph_umich_edu {

class ReaderCreateException: public ReaderException {
public:
	ReaderCreateException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~ReaderCreateException();
};

}

#endif
