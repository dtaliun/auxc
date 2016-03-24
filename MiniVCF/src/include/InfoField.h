#ifndef SRC_INFOFIELD_H_
#define SRC_INFOFIELD_H_

#include <iostream>
#include <string>
#include <unordered_map>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class InfoField: public Field {
private:
	string text;

	regex empty_info_regex;
	regex info_keyvalue_regex;
	regex info_split_regex;

	unordered_map<string, string> values;

	const sregex_token_iterator send;

public:
	InfoField();
	virtual ~InfoField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	const unordered_map<string, string>& get_values() const;
};

}

#endif
