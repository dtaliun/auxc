#include "include/ChromField.h"

namespace sph_umich_edu {

ChromField::ChromField() : chrom_name_regex("^[a-zA-Z0-9-_]+|<[a-zA-Z0-9-_]+>$") {

}

ChromField::~ChromField() {

}

void ChromField::parse(const csub_match& text) throw (VCFException) {
	this->text = std::move(text.str());
	if (!regex_match(this->text, chrom_name_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing CHROM field.");
	}
	value = this->text;
}

const string& ChromField::get_value() const {
	return value;
}

void ChromField::print() const {

}

}
