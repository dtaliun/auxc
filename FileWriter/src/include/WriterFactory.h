#ifndef SRC_WRITERFACTORY_H_
#define SRC_WRITERFACTORY_H_

#include <memory>

#include "TextWriter.h"
#include "GzipWriter.h"
#include "WriterCreateException.h"

using namespace std;

namespace sph_umich_edu {

class WriterFactory {
private:
	WriterFactory();

public:
	enum class WRITER_TYPE {
		TEXT, GZIP
	};

	virtual ~WriterFactory();

	static unique_ptr<Writer> create(WRITER_TYPE type) throw (WriterCreateException);
};

}

#endif
