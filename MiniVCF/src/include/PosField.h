#ifndef SRC_POSFIELD_H_
#define SRC_POSFIELD_H_

#include <iostream>
#include <string>
#include <regex>
#include <limits>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class PosField : public Field {
private:
	string text;
	regex pos_regex;

	long long unsigned int value;

public:
	PosField();
	virtual ~PosField();

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;
	const string& get_text() const;
	long long unsigned int get_value() const;
};

}

#endif
