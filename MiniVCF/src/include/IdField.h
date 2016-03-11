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
	regex empty_id_regex;
	regex ids_regex;
	regex ids_split_regex;

	bool empty;
	vector<string> values;

public:
	IdField();
	virtual ~IdField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	bool is_empty() const;
	const vector<string>& get_values() const;
};

}

#endif
