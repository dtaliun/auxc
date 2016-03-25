#include "include/GenotypeField.h"

namespace sph_umich_edu {

GenotypeField::GenotypeField(const FormatField& format):
	token_start(nullptr),
	token_end(nullptr),
	format(format),
	phased(false),
	missing_alleles(false) {

	values.reserve(10);
	alleles.reserve(10);
}

GenotypeField::~GenotypeField() {

}

long long unsigned int GenotypeField::toul_nocheck(const char* start, const char* end) {
	long long unsigned int value = 0ul;

	while (start != end) {
		value = value * 10 + (*start - 48);
		++start;
	}

	return value;
}

void GenotypeField::parse(const char* start, const char* end) throw (VCFException) {
	values.clear();
	phased = false;
	missing_alleles = false;
	alleles.clear();
	text.assign(start, end);

	token_start = start;
	token_end = start;

	while (token_end != end) {
		if (*token_end == ':') {
			if (token_start == token_end) { // empty token
				values.clear();
				throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
			}
			values.emplace_back(token_start, token_end);
			token_start = ++token_end;
		} else if (isspace(*token_end)) { // token with spaces
			values.clear();
			throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
		} else {
			++token_end;
		}
	}
	if (token_start == token_end) { // empty token
		values.clear();
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
	}
	values.emplace_back(token_start, token_end);

	if (format.has_genotypes()) {
		start = values[0u].c_str();
		end = values[0u].c_str() + values[0u].length();

		token_start = start;
		token_end = start;

		unsigned int n_vbars = 0u;
		unsigned int n_fslashes = 0u;
		unsigned int n_dots = 0u;
		unsigned int n_tokens = 0u;
		unsigned int n_dots_in_token = 0u;

//		cout << values[0u] << " >: ";

		while (token_end != end) {
//			cout << "here";
			if (*token_end == '/') {
				switch (token_end - token_start) {
					case 0:
						throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
						break;
					case 1:
						if (n_dots_in_token == 0) {
							alleles.push_back(toul_nocheck(token_start, token_end));
						}
						break;
					default:
						if ((n_dots_in_token > 0) || (*token_start == '0')) {
							throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
						}
						alleles.push_back(toul_nocheck(token_start, token_end));
						break;
				}

				token_start = ++token_end;
				++n_fslashes;
				++n_tokens;
				n_dots += n_dots_in_token;
				n_dots_in_token = 0u;
			} else if (*token_end == '|') {
				switch (token_end - token_start) {
					case 0:
						throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
						break;
					case 1:
						if (n_dots_in_token == 0) {
							alleles.push_back(toul_nocheck(token_start, token_end));
						}
						break;
					default:
						if ((n_dots_in_token > 0) || (*token_start == '0')) {
							throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
						}
						alleles.push_back(toul_nocheck(token_start, token_end));
						break;
				}

				token_start = ++token_end;
				++n_vbars;
				++n_tokens;
				n_dots += n_dots_in_token;
				n_dots_in_token = 0u;
			} else if (*token_end == '.') {
				++n_dots_in_token;
				++token_end;
			} else if (!isdigit(*token_end)) {
				throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
			} else {
				++token_end;
			}
		}

		switch (token_end - token_start) {
			case 0:
				throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
				break;
			case 1:
				if (n_dots_in_token == 0) {
					alleles.push_back(toul_nocheck(token_start, token_end));
				}
				break;
			default:
				if ((n_dots_in_token > 0) || (*token_start == '0')) {
					throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing genotype field.");
				}
				alleles.push_back(toul_nocheck(token_start, token_end));
				break;
		}
		n_dots += n_dots_in_token;
		++n_tokens;

//		cout << " vbars=" << n_vbars << " fslashes=" << n_fslashes << " tokens=" << n_tokens << " dots=" << n_dots << endl;

		if ((n_vbars != 0) && (n_fslashes != 0)) {
			throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing alleles in genotype field.");
		} else if (n_fslashes > 0) {
			phased = false;
		} else {
			phased = true;
		}

		if (n_dots > 0) {
			if (n_tokens == n_dots) {
				missing_alleles = true;
			} else {
				throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Error while parsing alleles in genotype field.");
			}
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

const string& GenotypeField::get_text() const {
	return text;
}

const vector<unsigned int>& GenotypeField::get_alleles() const {
	return alleles;
}

void GenotypeField::print() const {

}


}
