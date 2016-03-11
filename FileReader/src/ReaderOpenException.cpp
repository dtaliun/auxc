#include "include/ReaderOpenException.h"

namespace sph_umich_edu {

ReaderOpenException::ReaderOpenException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
				ReaderException(source_file, function, line, message) {

}

ReaderOpenException::~ReaderOpenException() {

}

}
