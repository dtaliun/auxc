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
	static const string TEXT;
	static const string GZIP;

	virtual ~WriterFactory();

	static unique_ptr<Writer> create(const string& type) throw (WriterCreateException);
};

}

#endif
