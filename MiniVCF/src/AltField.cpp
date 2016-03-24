#include "include/AltField.h"

namespace sph_umich_edu {

AltField::AltField() :
		empty_alt_regex("^\\.$"),
		id_alt_regex("<[^\\s,<>]+>(?:,<[^\\s,<>]+>)*", std::regex_constants::optimize),
		alt_regex("[acgtnACGTN\\*]+(?:,[acgtnACGTN\\*]+)*", std::regex_constants::optimize),
		alt_split_regex(","),
		empty(true) {

}

AltField::~AltField() {

}

void AltField::parse(const char* start, const char* end) throw (VCFException) {
	empty = true;
	values.clear();
	text.assign(start, end);

	if (text.compare(".") == 0) {
		return;
	}

//	if (regex_match(text, empty_alt_regex)) {
//		return;
//	}

	if (regex_match(text, alt_regex) || regex_match(text, id_alt_regex)) {
		sregex_token_iterator fields_iter(text.begin(), text.end(), alt_split_regex, -1);
		while (fields_iter != send) {
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
