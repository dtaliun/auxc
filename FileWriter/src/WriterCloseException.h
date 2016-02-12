#ifndef SRC_WRITERCLOSEEXCEPTION_H_
#define SRC_WRITERCLOSEEXCEPTION_H_

#include "WriterException.h"

namespace sph_umich_edu {

class WriterCloseException: public WriterException {
public:
	WriterCloseException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~WriterCloseException();
};

}

#endif
