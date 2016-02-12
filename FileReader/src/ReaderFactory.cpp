#include "ReaderFactory.h"

namespace sph_umich_edu {

const string ReaderFactory::TEXT = "TEXT";
const string ReaderFactory::GZIP = "GZIP";

ReaderFactory::ReaderFactory() {

}

ReaderFactory::~ReaderFactory() {

}

bool ReaderFactory::is_gzip(const string& file_name) throw (ReaderException) {
	ifstream in_stream;
	char characters[2] = {'\x00', '\x00'};

	in_stream.open(file_name);
	if (in_stream.fail()) {
		throw ReaderException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}

	in_stream.read(characters, 2);
	if (in_stream.fail() && !in_stream.eof()) {
		throw ReaderException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}

	in_stream.clear();
	in_stream.close();
	if (in_stream.fail()) {
		throw ReaderException(__FILE__, __FUNCTION__, __LINE__, file_name.c_str());
	}

	if ((characters[0] == '\x1F') && (characters[1] == '\x8B')) {
		return true;
	}

	return false;
}

unique_ptr<Reader> ReaderFactory::create(const string& type) throw (ReaderCreateException) {
	if (type.compare(GZIP) == 0) {
		return unique_ptr<Reader>(new GzipReader());
	}

	return unique_ptr<Reader>(new TextReader());
}

}
