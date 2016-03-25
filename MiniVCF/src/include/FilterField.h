#ifndef SRC_FILTERFIELD_H_
#define SRC_FILTERFIELD_H_

#include <iostream>
#include <string>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class FilterField: public Field {
private:
	string text;

	regex empty_filter_regex;
	regex filter_regex;
	regex filters_split_regex;

	bool empty;
	bool pass;
	vector<string> values;

	const sregex_token_iterator send;

public:
	FilterField();
	virtual ~FilterField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	bool is_empty() const;
	bool is_pass() const;
	const string& get_text() const;
	const vector<string>& get_values() const;
};

}

#endif
