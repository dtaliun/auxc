#include "include/PosField.h"

namespace sph_umich_edu {

PosField::PosField() : pos_regex("0|[1-9][0-9]*"), value(numeric_limits<long long unsigned int>::min()) {

}

PosField::~PosField() {

}

void PosField::parse(const csub_match& text) throw (VCFException) {
	this->text = std::move(text.str());
	if (!regex_match(this->text, pos_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing POS field.");
	}
	value = stoull(this->text, nullptr, 10);
}

long long unsigned int PosField::get_value() const {
	return value;
}

void PosField::print() const {

}

}
