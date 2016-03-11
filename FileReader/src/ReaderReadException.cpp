#include "include/ReaderReadException.h"

namespace sph_umich_edu {

ReaderReadException::ReaderReadException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				ReaderException(source_file, function, line, message) {

}

ReaderReadException::~ReaderReadException() {

}

}
