#include "include/Reader.h"

namespace sph_umich_edu {

Reader::Reader() {

}

Reader::~Reader() {

}

void Reader::set_file_name(const string& file_name) {
	if (!is_open()) {
		this->file_name = file_name;
	}
}

const string& Reader::get_file_name() {
	return file_name;
}

}
