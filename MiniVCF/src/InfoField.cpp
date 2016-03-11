#include "include/InfoField.h"

namespace sph_umich_edu {

InfoField::InfoField():
	info_keyvalue_regex("([\\.]*[a-zA-Z0-9_][a-zA-Z0-9_\\.]*)(?:=([^=;,[:space:]]+(?:,[^=;,[:space:]]+)*))?"),
	info_split_regex(";") {
}

InfoField::~InfoField() {

}

void InfoField::parse(const csub_match& text) throw (VCFException) {
	values.clear();
	this->text = std::move(text.str());

	const sregex_token_iterator end;
	smatch matches;
	sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), info_split_regex, -1);
	while (fields_iter != end) {
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
