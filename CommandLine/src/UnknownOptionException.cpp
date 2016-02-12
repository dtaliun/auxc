#include "UnknownOptionException.h"

namespace sph_umich_edu {

UnknownOptionException::UnknownOptionException(const char* file, const char* function, unsigned int line, const char* message) :
	CommandLineException(file, function, line, message) {

}

UnknownOptionException::~UnknownOptionException() {

}

}
