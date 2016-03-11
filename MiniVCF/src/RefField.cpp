#include "include/RefField.h"

namespace sph_umich_edu {

RefField::RefField() : ref_regex("[acgtnACGTN]+") {

}

RefField::~RefField() {

}

void RefField::parse(const csub_match& text) throw (VCFException) {
	this->text = std::move(text.str());
	if (!regex_match(this->text, ref_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing REF field.");
	}
	value = this->text;
}

const string& RefField::get_value() {
	return value;
}

void RefField::print() const {

}

}
