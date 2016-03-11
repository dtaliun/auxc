#include "include/WriterWriteException.h"

namespace sph_umich_edu {

WriterWriteException::WriterWriteException(
		const char* source_file, const char* function, unsigned int line, const char* message) :
			WriterException(source_file, function, line, message) {

}

WriterWriteException::~WriterWriteException() {

}

}
