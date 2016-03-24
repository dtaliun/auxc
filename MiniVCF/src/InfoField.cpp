#include "include/InfoField.h"

namespace sph_umich_edu {

InfoField::InfoField():
	empty_info_regex("\\."),
	info_keyvalue_regex("([\\.]*[a-zA-Z0-9_][a-zA-Z0-9_\\.]*)(?:=([^=;,[:space:]]+(?:,[^=;,[:space:]]+)*))?"),
	info_split_regex(";") {
}

InfoField::~InfoField() {

}

void InfoField::parse(const char* start, const char* end) throw (VCFException) {
	values.clear();
	text.assign(start, end);

//	if (regex_match(this->text, empty_info_regex)) {
//		return;
//	}

	if ((text.length() == 1) && (text[0] == '.')) {
		return;
	}

	smatch matches;
	sregex_token_iterator fields_iter(text.begin(), text.end(), info_split_regex, -1);
	while (fields_iter != send) {
		if (!regex_match(fields_iter->first, fields_iter->second, matches, info_keyvalue_regex)) {
			values.clear();
			throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing INFO field.");
		}
		values.emplace(std::move(matches.str(1u)), std::move(matches.str(2u)));
		++fields_iter;
	}
}

const unordered_map<string, string>& InfoField::get_values() const {
	return values;
}

void InfoField::print() const {

}

}
