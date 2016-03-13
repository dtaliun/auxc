#ifndef SRC_READERFACTORY_H_
#define SRC_READERFACTORY_H_

#include <exception>
#include <iostream>
#include <fstream>
#include <memory>

#include "GzipReader.h"
#include "TextReader.h"

using namespace std;

namespace sph_umich_edu {

class ReaderFactory {
private:
	ReaderFactory();

public:
	enum class READER_TYPE {
		TEXT, GZIP
	};

	virtual ~ReaderFactory();

	static unique_ptr<Reader> create(READER_TYPE type) throw (ReaderCreateException);
	static bool is_gzip(const string& file_name) throw (ReaderException);
};

}

#endif
