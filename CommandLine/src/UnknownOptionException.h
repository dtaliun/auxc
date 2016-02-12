#ifndef SRC_UNKNOWNOPTIONEXCEPTION_H_
#define SRC_UNKNOWNOPTIONEXCEPTION_H_

#include "CommandLineException.h"

namespace sph_umich_edu {

class UnknownOptionException : public CommandLineException {
public:
	UnknownOptionException(const char* file, const char* function, unsigned int line, const char* message);
	virtual ~UnknownOptionException();
};

}

#endif
