#include "include/IdField.h"

namespace sph_umich_edu {

IdField::IdField() :
		ids_regex("[a-zA-Z0-9_]+[^\\s;,]*(?:;[a-zA-Z0-9_]+[^\\s;,]*)*", std::regex_constants::optimize),
		token_start(nullptr), token_end(nullptr),
		empty(true) {

}

IdField::~IdField() {

}

void IdField::parse(const char* start, const char* end) throw (VCFException) {
	empty = true;
	values.clear();
	text.assign(start, end);

	if (text.compare(".") == 0) {
		return;
	}

//	if ((*start == '.') && (end - start == 1)) {
//		return;
//	}

	if (!regex_match(text, ids_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing ID field.");
	}

	token_start = start;
	token_end = start;

	while (token_end != end) {
		if (*token_end == ';') {
			values.emplace_back(token_start, token_end);
			token_start = ++token_end;
		} else {
			++token_end;
		}
	}
	values.emplace_back(token_start, token_end);

	empty = false;
}

bool IdField::is_empty() const {
	return empty;
}

const vector<string>& IdField::get_values() const {
	return values;
}

void IdField::print() const {

}

}
