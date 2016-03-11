#include "include/ReaderCreateException.h"

namespace sph_umich_edu {

ReaderCreateException::ReaderCreateException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				ReaderException(source_file, function, line, message) {

}

ReaderCreateException::~ReaderCreateException() {

}

}
