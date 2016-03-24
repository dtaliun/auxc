#ifndef SRC_IDFIELD_H_
#define SRC_IDFIELD_H_

#include <iostream>
#include <string>
#include <regex>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class IdField: public Field {
private:
	string text;
	regex ids_regex;
	const char* token_start;
	const char* token_end;


	bool empty;
	vector<string> values;

	const sregex_token_iterator send;

public:
	IdField();
	virtual ~IdField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	bool is_empty() const;
	const vector<string>& get_values() const;
};

}

#endif
