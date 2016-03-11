#ifndef SRC_INCLUDE_META_H_
#define SRC_INCLUDE_META_H_

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <unordered_map>
#include <tuple>
#include "VCFException.h"

using namespace std;

namespace sph_umich_edu {

class Meta {
protected:
	string text;

	regex meta_key_value_regex;
	regex meta_attributes_regex;
	regex meta_attribute_value_regex;

	string key;
	string value;
	unordered_map<string, string> attributes;
	vector<string> attributes_order;

public:
	Meta();
	virtual ~Meta();

	Meta(const Meta& meta) = delete;
	Meta& operator=(const Meta& meta) = delete;
	Meta(Meta&& meta) = delete;
	Meta& operator=(Meta&& meta) = delete;

	virtual void parse(const string& text) throw (VCFException);

	const string& get_key();
	const string& get_value();
	unsigned int get_n_attributes();
	bool has_attribute(const string& name);
	const string& get_attribute(const string& name);
};

}

#endif
