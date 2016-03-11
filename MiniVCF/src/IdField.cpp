#include "include/IdField.h"

namespace sph_umich_edu {

IdField::IdField() :
		empty_id_regex("^\\.$"),
		ids_regex("[a-zA-Z0-9_]+[^\\s;,]*(;[a-zA-Z0-9_]+[^\\s;,]*)*"),
		ids_split_regex(";"),
		empty(true) {

}

IdField::~IdField() {

}

void IdField::parse(const csub_match& text) throw (VCFException) {
	empty = true;
	values.clear();
	this->text = std::move(text.str());

	if (regex_match(this->text, empty_id_regex)) {
		return;
	}

	if (!regex_match(this->text, ids_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing ID field.");
	}

	const sregex_token_iterator end;
	sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), ids_split_regex, -1);
	while (fields_iter != end) {
		values.emplace_back(std::move(fields_iter->str()));
		++fields_iter;
	}
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
