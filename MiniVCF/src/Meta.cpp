#include "include/Meta.h"

namespace sph_umich_edu {

Meta::Meta():
	meta_key_value_regex("##([[:alnum:]]+)=(.+)"),
	meta_attributes_regex("<([[:alnum:]]+=(?:(?:\"(?:[^\"]|\\\\\")*\")|[^,\"]+))(?:,([[:alnum:]]+=(?:(?:\"(?:[^\"]|\\\\\")*\")|[^,\"]+)))*>"),
	meta_attribute_value_regex("([[:alnum:]]+)=((?:\"(?:[^\"]|\\\\\")*\")|[^,\"]+)") {
}

Meta::~Meta() {

}

void Meta::parse(const string& text) throw (VCFException) {
	this->text = text;

	smatch key_value_match;
	const sregex_iterator end;

	attributes_order.clear();
	attributes.clear();

	if (!regex_match(this->text, key_value_match, meta_key_value_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing meta information line.");
	}

	this->key = std::move(key_value_match.str(1));
	this->value = std::move(key_value_match.str(2));

	if ((this->value.front() == '<') || (this->value.back() == '>')) {
		if (!regex_match(key_value_match[2].first, key_value_match[2].second, meta_attributes_regex)) {
			throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing meta information line.");
		}
		sregex_iterator attr_iter(this->value.begin() + 1, this->value.end() - 1, meta_attribute_value_regex);
		while (attr_iter != end) {
			attributes_order.emplace_back(std::move(attr_iter->str(1)));
			if (attributes.count(attributes_order.back()) > 0) {
				throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing meta information line.");
			}
			attributes.emplace(std::move(attr_iter->str(1)), std::move(attr_iter->str(2)));
			++attr_iter;
		}
	}
}

const string& Meta::get_key() {
	return key;
}

const string& Meta::get_value() {
	return value;
}

unsigned int Meta::get_n_attributes() {
	return attributes.size();
}

bool Meta::has_attribute(const string& name) {
	return attributes.count(name) > 0;
}

const string& Meta::get_attribute(const string& name) {
	return attributes.at(name);
}

}
