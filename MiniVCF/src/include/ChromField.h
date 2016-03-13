#ifndef SRC_CHROMFIELD_H_
#define SRC_CHROMFIELD_H_

#include <iostream>
#include <string>
#include <regex>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class ChromField: public Field {
protected:
	string text;
	regex chrom_name_regex;

	string value;

public:
	ChromField();
	virtual ~ChromField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	const string& get_value() const;
};

}

#endif