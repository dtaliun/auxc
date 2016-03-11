#ifndef SRC_VARIANT_H_
#define SRC_VARIANT_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include "ChromField.h"
#include "PosField.h"
#include "IdField.h"
#include "RefField.h"
#include "AltField.h"
#include "QualField.h"
#include "FilterField.h"
#include "InfoField.h"
#include "FormatField.h"
#include "GenotypeField.h"

using namespace std;

namespace sph_umich_edu {

class Variant {
protected:
	regex field_split_regex;

	ChromField chrom;
	PosField pos;
	IdField id;
	RefField ref;
	AltField alt;
	QualField qual;
	FilterField filter;
	InfoField info;
	FormatField format;
	vector<unique_ptr<GenotypeField>> genotypes;

	unordered_map<string, unsigned int> samples;

public:
	Variant();
	virtual ~Variant();

	Variant(const Variant& variant) = delete;
	Variant& operator=(const Variant& variant) = delete;
	Variant(Variant&& variant) = delete;
	Variant& operator=(Variant&& variant) = delete;

	void add_sample(const string& sample) throw (VCFException);
	void add_sample(string&& sample) throw (VCFException);

	void parse(const char* start, const char* end) throw (VCFException);

	unsigned int get_n_samples() const;
	bool has_sample(const string& sample) const;
	long int get_sample_index(const string& sample) const;
	const ChromField& get_chrom() const;
	const PosField& get_pos() const;
	const IdField& get_id() const;
	const RefField& get_ref() const;
	const AltField& get_alt() const;
	const QualField& get_qual() const;
	const FilterField& get_filter() const;
	const InfoField& get_info() const;
	const FormatField& get_format() const;
	const GenotypeField& get_genotype(const string& sample) const throw (VCFException);
	const GenotypeField& get_genotype(unsigned int index) const throw (VCFException);

};

}

#endif
