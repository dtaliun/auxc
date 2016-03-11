#include "include/FormatField.h"

namespace sph_umich_edu {

FormatField::FormatField():
	format_regex("[[:alnum:]]+(:(?!GT\\b)[[:alnum:]]+)*"),
	format_split_regex(":"),
	genotypes(false) {

}

FormatField::~FormatField() {

}

void FormatField::parse(const csub_match& text) throw (VCFException) {
	genotypes = false;
	values.clear();
	this->text = std::move(text.str());

	if (!regex_match(this->text, format_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing FORMAT field.");
	}

	const sregex_token_iterator end;
	sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), format_split_regex, -1);
	while (fields_iter != end) {
		values.emplace_back(std::move(fields_iter->str()));
		++fields_iter;
	}
	if (values.front().compare("GT") == 0) {
		genotypes = true;
	}
}

bool FormatField::has_genotypes() const {
	return genotypes;
}

const vector<string>& FormatField::get_values() const {
	return values;
}

void FormatField::print() const {

}

}
