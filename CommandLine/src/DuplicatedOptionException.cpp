#include "DuplicatedOptionException.h"

namespace sph_umich_edu {

DuplicatedOptionException::DuplicatedOptionException(const char* file, const char* function, unsigned int line, const char* message) :
		CommandLineException(file, function, line, message) {

}

DuplicatedOptionException::~DuplicatedOptionException() {

}

}
