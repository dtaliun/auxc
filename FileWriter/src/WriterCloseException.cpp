#include "include/WriterCloseException.h"

namespace sph_umich_edu {

WriterCloseException::WriterCloseException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
			WriterException(source_file, function, line, message) {

}

WriterCloseException::~WriterCloseException() {

}

}
