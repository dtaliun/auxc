#include "WriterOpenException.h"

namespace sph_umich_edu {

WriterOpenException::WriterOpenException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
			WriterException(source_file, function, line, message) {

}

WriterOpenException::~WriterOpenException() {

}

}
