#include "include/RefField.h"

namespace sph_umich_edu {

RefField::RefField() : ref_regex("[acgtnACGTN]+", std::regex_constants::optimize) {

}

RefField::~RefField() {

}

void RefField::parse(const char* start, const char* end) throw (VCFException) {
	text.assign(start, end);
	if (!regex_match(text, ref_regex)) {
		value.clear();
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing REF field.");
	}
	value = text;
}

const string& RefField::get_text() const {
	return text;
}

const string& RefField::get_value() {
	return value;
}

void RefField::print() const {

}

}
