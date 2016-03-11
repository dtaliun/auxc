#ifndef SRC_QUALFIELD_H_
#define SRC_QUALFIELD_H_

#include <iostream>
#include <string>
#include <limits>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class QualField: public Field {
private:
	string text;
	regex empty_qual_regex;
	regex qual_regex;

	bool empty;
	double value;

public:
	QualField();
	virtual ~QualField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	bool is_empty() const;
	double get_value() const;
};

}

#endif
