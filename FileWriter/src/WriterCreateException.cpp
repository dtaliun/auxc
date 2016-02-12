#include "WriterCreateException.h"

namespace sph_umich_edu {

WriterCreateException::WriterCreateException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
			WriterException(source_file, function, line, message) {

}

WriterCreateException::~WriterCreateException() {

}

}
