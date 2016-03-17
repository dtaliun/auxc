#include "include/AltField.h"

namespace sph_umich_edu {

AltField::AltField() :
		empty_alt_regex("^\\.$"),
		id_alt_regex("<[^\\s,<>]+>(,<[^\\s,<>]+>)*"),
		alt_regex("[acgtnACGTN\\*]+(,[acgtnACGTN\\*]+)*"),
		alt_split_regex(","),
		empty(true) {

}

AltField::~AltField() {

}

void AltField::parse(const csub_match& text) throw (VCFException) {
	empty = true;
	values.clear();
	this->text = std::move(text.str());

	if (regex_match(this->text, empty_alt_regex)) {
		return;
	}

	if (regex_match(this->text, alt_regex) || regex_match(this->text, id_alt_regex)) {
		const sregex_token_iterator end;
		sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), alt_split_regex, -1);
		while (fields_iter != end) {
			values.emplace_back(std::move(fields_iter->str()));
			++fields_iter;
		}
	} else {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing ALT field.");
	}
	empty = false;
}

bool AltField::is_empty() const {
	return empty;
}

const vector<string>& AltField::get_values() const {
	return values;
}

void AltField::print() const {

}

}
