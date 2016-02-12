#include "Writer.h"

namespace sph_umich_edu {

Writer::Writer() {

}

Writer::~Writer() {

}

void Writer::set_file_name(const string& file_name) {
	if (!is_open()) {
		this->file_name = file_name;
	}
}

const string& Writer::get_file_name() {
	return file_name;
}

}
