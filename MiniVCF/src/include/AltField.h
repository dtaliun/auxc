#ifndef SRC_ALTFIELD_H_
#define SRC_ALTFIELD_H_

#include <iostream>
#include <string>
#include <regex>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class AltField: public Field {
private:
	string text;

	regex empty_alt_regex;
	regex id_alt_regex;
	regex alt_regex;
	regex alt_split_regex;

	bool empty;
	vector<string> values;

	const sregex_token_iterator send;

public:
	AltField();
	virtual ~AltField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	bool is_empty() const;
	const vector<string>& get_values() const;
};

}

#endif
