#ifndef INVALIDOPTIONEXCEPTION_H_
#define INVALIDOPTIONEXCEPTION_H_

#include "CommandLineException.h"

namespace sph_umich_edu {

class InvalidOptionException : public CommandLineException {
public:
	InvalidOptionException(const char* file, const char* function, unsigned int line, const char* message);
	virtual ~InvalidOptionException();
};

}

#endif
