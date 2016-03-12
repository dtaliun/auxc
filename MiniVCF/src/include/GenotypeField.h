#ifndef SRC_GENOTYPEFIELD_H_
#define SRC_GENOTYPEFIELD_H_

#include <iostream>
#include <string>
#include <vector>

#include "FormatField.h"

using namespace std;

namespace sph_umich_edu {

class GenotypeField: public Field {
private:
	string text;

	regex genotype_regex;
	regex genotype_split_regex;
	regex missing_alleles_regex;
	regex alleles_regex;
	regex alleles_split_regex;

	const FormatField& format;

	vector<string> values;

	bool phased;
	bool missing_alleles;
	vector<unsigned int> alleles;

public:
	GenotypeField(const FormatField& format);
	virtual ~GenotypeField();

	virtual void parse(const csub_match& text) throw (VCFException);
	virtual void print() const;

	const vector<string>& get_values() const;

	bool has_genotypes() const;
	bool is_phased() const;
	bool has_missing_alleles() const;
	const vector<unsigned int>& get_alleles() const;

};

}

#endif
