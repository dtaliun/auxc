#include "include/FilterField.h"

namespace sph_umich_edu {

FilterField::FilterField():
		empty_filter_regex("\\."),
		filter_regex("[a-zA-Z0-9_]+[^\\s;]*(;[a-zA-Z0-9_]+[^\\s;]*)*"),
		filters_split_regex(";"),
		empty(true),
		pass(false) {

}

FilterField::~FilterField() {

}

void FilterField::parse(const char* start, const char* end) throw (VCFException) {
	empty = true;
	pass = false;
	values.clear();
	text.assign(start, end);

//	if (regex_match(this->text, empty_filter_regex)) {
//		return;
//	}

	if ((this->text.length() == 1) && (this->text[0] == '.')) {
		return;
	}

	if (!regex_match(text, filter_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing FILTER field.");
	}

	sregex_token_iterator fields_iter(text.begin(), text.end(), filters_split_regex, -1);
	while (fields_iter != send) {
		values.emplace_back(std::move(fields_iter->str()));
		if (values.back().compare("PASS") == 0) {
			pass = true;
		}
		++fields_iter;
	}
	empty = false;
}

bool FilterField::is_empty() const {
	return empty;
}

bool FilterField::is_pass() const {
	return pass;
}

const vector<string>& FilterField::get_values() const {
	return values;
}

void FilterField::print() const {

}

}
