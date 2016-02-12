#ifndef SRC_WRITEROPENEXCEPTION_H_
#define SRC_WRITEROPENEXCEPTION_H_

#include "WriterException.h"

namespace sph_umich_edu {

class WriterOpenException: public WriterException {
public:
	WriterOpenException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~WriterOpenException();
};

}

#endif
