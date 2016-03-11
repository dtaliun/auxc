#ifndef SRC_WRITERCREATEEXCEPTION_H_
#define SRC_WRITERCREATEEXCEPTION_H_

#include "WriterException.h"

namespace sph_umich_edu {

class WriterCreateException: public WriterException {
public:
	WriterCreateException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~WriterCreateException();
};

}

#endif
