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

public:
	FormatField();
	virtual ~FormatField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	bool has_genotypes() const;
	const vector<string>& get_values() const;
};

}

#endif
