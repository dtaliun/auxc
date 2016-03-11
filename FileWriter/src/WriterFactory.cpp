#include "include/WriterFactory.h"

namespace sph_umich_edu {

const string WriterFactory::TEXT = "TEXT";
const string WriterFactory::GZIP = "GZIP";

WriterFactory::WriterFactory() {

}

WriterFactory::~WriterFactory() {

}

unique_ptr<Writer> WriterFactory::create(const string& type) throw (WriterCreateException) {
	if (type.compare(GZIP) == 0) {
		return unique_ptr<Writer>(new GzipWriter());
	}

	return unique_ptr<Writer>(new TextWriter());
}

}
