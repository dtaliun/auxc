#include "include/ChromField.h"

namespace sph_umich_edu {

ChromField::ChromField() : chrom_name_regex("^[a-zA-Z0-9-_]+|<[a-zA-Z0-9-_]+>$", std::regex_constants::optimize) {

}

ChromField::~ChromField() {

}

void ChromField::parse(const char* start, const char* end) throw (VCFException) {
	text.assign(start, end);
	if (!regex_match(text, chrom_name_regex)) {
		value.clear();
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing CHROM field.");
	}
	value = text;
}

const string& ChromField::get_text() const {
	return text;
}

const string& ChromField::get_value() const {
	return value;
}

void ChromField::print() const {

}

}
