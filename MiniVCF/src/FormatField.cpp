#include "include/FormatField.h"

namespace sph_umich_edu {

FormatField::FormatField():
	format_regex("[[:alnum:]]+(:(?!GT\\b)[[:alnum:]]+)*"),
	format_split_regex(":"),
	genotypes(false) {

}

FormatField::~FormatField() {

}

void FormatField::parse(const char* start, const char* end) throw (VCFException) {
	genotypes = false;
	values.clear();
	text.assign(start, end);

	if (!regex_match(text, format_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing FORMAT field.");
	}

	sregex_token_iterator fields_iter(text.begin(), text.end(), format_split_regex, -1);
	while (fields_iter != send) {
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

const string& FormatField::get_text() const {
	return text;
}

const vector<string>& FormatField::get_values() const {
	return values;
}

void FormatField::print() const {

}

}
