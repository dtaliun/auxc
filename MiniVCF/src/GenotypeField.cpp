#include "include/GenotypeField.h"

namespace sph_umich_edu {

GenotypeField::GenotypeField(const FormatField& format):
	genotype_regex("[^:[:space:]]+(:[^:[:space:]]+)*"),
	genotype_split_regex(":"),
	missing_alleles_regex("\\.(?:[\\|/]\\.)*"),
	alleles_regex("[0-9]+(?:[\\|/][0-9]+)*"),
	alleles_split_regex("[\\|/]"),
	format(format),
	phased(false),
	missing_alleles(false) {

}

GenotypeField::~GenotypeField() {

}

void GenotypeField::parse(const csub_match& text) throw (VCFException) {
	values.clear();
	phased = false;
	missing_alleles = false;
	alleles.clear();
	this->text = std::move(text.str());

	if (!regex_match(this->text, genotype_regex)) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
	}

	const sregex_token_iterator end;

	sregex_token_iterator fields_iter(this->text.begin(), this->text.end(), genotype_split_regex, -1);
	while (fields_iter != end) {
		values.emplace_back(std::move(fields_iter->str()));
		++fields_iter;
	}

	if (format.has_genotypes()) {
		if (regex_match(values[0u], missing_alleles_regex)) {
			missing_alleles = true;
			if ((values[0].length() > 1u) && (values[0].find_first_of('|') == string::npos)) {
				phased = false;
			} else {
				phased = true;
			}
		} else if (regex_match(values[0u], alleles_regex)) {
			missing_alleles = false;
			sregex_token_iterator fields_iter(values[0u].begin(), values[0u].end(), alleles_split_regex, -1);
			while (fields_iter != end) {
				alleles.push_back(stoull(fields_iter->str(), nullptr, 10));
				++fields_iter;
			}
			if ((alleles.size() > 1u) && (values[0].find_first_of('|') == string::npos)) {
				phased = false;
			} else {
				phased = true;
			}
		} else {
			throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing alleles in genotype field.");
		}
	}
}

const vector<string>& GenotypeField::get_values() const {
	return values;
}

bool GenotypeField::has_genotypes() const {
	return format.has_genotypes();
}

bool GenotypeField::is_phased() const {
	return phased;
}

bool GenotypeField::has_missing_alleles() const {
	return missing_alleles;
}

const vector<unsigned int>& GenotypeField::get_alleles() const {
	return alleles;
}

void GenotypeField::print() const {

}


}
