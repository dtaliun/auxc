#include "include/PosField.h"

namespace sph_umich_edu {

PosField::PosField() :
		pos_regex("0|[1-9][0-9]*", std::regex_constants::optimize),
		value(numeric_limits<long long unsigned int>::min()) {

}

PosField::~PosField() {

}

void PosField::parse(const char* start, const char* end) throw (VCFException) {
	text.assign(start, end);
	if (!regex_match(text, pos_regex)) {
		value = numeric_limits<long long unsigned int>::min();
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing POS field.");
	}
	value = stoull(text, nullptr, 10);
}

long long unsigned int PosField::get_value() const {
	return value;
}

void PosField::print() const {

}

}
