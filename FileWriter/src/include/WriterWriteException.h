#ifndef SRC_WRITERWRITEEXCEPTION_H_
#define SRC_WRITERWRITEEXCEPTION_H_

#include "WriterException.h"

namespace sph_umich_edu {

class WriterWriteException: public WriterException {
public:
	WriterWriteException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~WriterWriteException();
};

}

#endif
