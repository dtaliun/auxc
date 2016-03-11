#ifndef SRC_GENOTYPEFIELD_H_
#define SRC_GENOTYPEFIELD_H_

#include <iostream>
#include <string>
#include <vector>

#include "Field.h"

using namespace std;

namespace sph_umich_edu {

class GenotypeField: public Field {
private:
	string text;

	regex genotype_regex;
	regex genotype_split_regex;

	vector<string> values;

public:
	GenotypeField();
	virtual ~GenotypeField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	const vector<string>& get_values() const;

};

}

#endif
