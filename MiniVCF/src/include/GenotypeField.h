#ifndef SRC_GENOTYPEFIELD_H_
#define SRC_GENOTYPEFIELD_H_

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "FormatField.h"

using namespace std;

namespace sph_umich_edu {

class GenotypeField: public Field {
private:
	string text;

	const char* token_start;
	const char* token_end;

	const FormatField& format;

	vector<string> values;

	bool phased;
	bool missing_alleles;
	vector<unsigned int> alleles;

	const sregex_token_iterator send;

public:
	GenotypeField(const FormatField& format);
	virtual ~GenotypeField();

	static long long unsigned int toul_nocheck(const char* start, const char* end);

	virtual void parse(const char* start, const char* end) throw (VCFException);

	virtual void print() const;

	const vector<string>& get_values() const;

	bool has_genotypes() const;
	bool is_phased() const;
	bool has_missing_alleles() const;
	const string& get_text() const;
	const vector<unsigned int>& get_alleles() const;

};

}

#endif
