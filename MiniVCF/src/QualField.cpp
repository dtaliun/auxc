#include "include/QualField.h"

namespace sph_umich_edu {

QualField::QualField():
		empty_qual_regex("\\."),
		qual_regex("(0|[1-9][0-9]*)(\\.[0-9]*)?"),
		empty(true),
		value(numeric_limits<double>::quiet_NaN()) {

}

QualField::~QualField() {

}

void QualField::parse(const csub_match& text) throw (VCFException) {
	empty = true;
	this->text = std::move(text.str());

	if (regex_match(this->text, empty_qual_regex)) {
		value = numeric_limits<double>::quiet_NaN();
		return;
	}

	if (!regex_match(this->text, qual_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing QUAL field.");
	}

	value = stod(this->text, nullptr);
	empty = false;
}

bool QualField::is_empty() const {
	return empty;
}

double QualField::get_value() const {
	return value;
}

void QualField::print() const {

}

}
