#ifndef SRC_REFFIELD_H_
#define SRC_REFFIELD_H_

#include <iostream>
#include <string>
#include <regex>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class RefField: public Field {
private:
	string text;
	regex ref_regex;

	string value;

public:
	RefField();
	virtual ~RefField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	virtual const string& get_value();
};

}

#endif
