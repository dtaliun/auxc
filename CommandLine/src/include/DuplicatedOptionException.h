#ifndef DUPLICATEDOPTIONEXCEPTION_H_
#define DUPLICATEDOPTIONEXCEPTION_H_

#include "CommandLineException.h"

using namespace std;

namespace sph_umich_edu {

class DuplicatedOptionException : public CommandLineException {

public:
	DuplicatedOptionException(const char* file, const char* function, unsigned int line, const char* message);
	virtual ~DuplicatedOptionException();
};

}

#endif
