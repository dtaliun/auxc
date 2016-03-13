#include "include/WriterFactory.h"

namespace sph_umich_edu {

WriterFactory::WriterFactory() {

}

WriterFactory::~WriterFactory() {

}

unique_ptr<Writer> WriterFactory::create(WRITER_TYPE type) throw (WriterCreateException) {
	if (type == WRITER_TYPE::GZIP) {
		return unique_ptr<Writer>(new GzipWriter());
	}

	return unique_ptr<Writer>(new TextWriter());
}

}
