#ifndef SRC_FORMATFIELD_H_
#define SRC_FORMATFIELD_H_

#include <iostream>
#include <vector>
#include <string>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class FormatField: public Field {
private:
	string text;

	regex format_regex;
	regex format_split_regex;

	bool genotypes;
	vector<string> values;

	const sregex_token_iterator send;

public:
	FormatField();
	virtual ~FormatField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	bool has_genotypes() const;
	const string& get_text() const;
	const vector<string>& get_values() const;
};

}

#endif
