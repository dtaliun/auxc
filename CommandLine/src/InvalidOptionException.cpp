#include "include/InvalidOptionException.h"

namespace sph_umich_edu {

InvalidOptionException::InvalidOptionException(const char* file, const char* function, unsigned int line, const char* message) :
	CommandLineException(file, function, line, message) {

}

InvalidOptionException::~InvalidOptionException() {

}

}
