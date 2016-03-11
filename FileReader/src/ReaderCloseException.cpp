#include "include/ReaderCloseException.h"

namespace sph_umich_edu {

ReaderCloseException::ReaderCloseException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				ReaderException(source_file, function, line, message) {

}

ReaderCloseException::~ReaderCloseException() {

}

}
