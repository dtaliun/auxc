#include "include/GenotypeField.h"

namespace sph_umich_edu {

GenotypeField::GenotypeField():
	genotype_regex("[^:[:space:]]+(:[^:[:space:]]+)*"),
	genotype_split_regex(":")
	/*phased(false)*/ {

}

GenotypeField::~GenotypeField() {

}

void GenotypeField::parse(const csub_match& text) throw (VCFException) {
	values.clear();
	this->text = std::move(text.str());
//	phased = false;
//	alleles.clear();

	if (!regex_match(this->text, genotype_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
	}

	const sregex_token_iterator end;
	sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), genotype_split_regex, -1);
	while (fields_iter != end) {
		values.emplace_back(std::move(fields_iter->str()));
		++fields_iter;
	}
}

const vector<string>& GenotypeField::get_values() const {
	return values;
}

void GenotypeField::print() const {

}


}
