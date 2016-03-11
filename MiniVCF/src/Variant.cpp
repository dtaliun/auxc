#include "include/Variant.h"

namespace sph_umich_edu {

Variant::Variant() :
		field_split_regex("\\t") {

}

Variant::~Variant() {

}

void Variant::add_sample(const string& sample) throw (VCFException) {
	if (samples.count(sample) > 0) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Duplicated sample names detected.");
	}
	unsigned int index = samples.size();
	samples.emplace(sample, index);
	genotypes.emplace_back(new GenotypeField);
}

void Variant::add_sample(string&& sample) throw (VCFException) {
	if (samples.count(sample) > 0) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Duplicated sample names detected.");
	}
	unsigned int index = samples.size();
	samples.emplace(std::move(sample), index);
	genotypes.emplace_back(new GenotypeField());
}

void Variant::parse(const char* text_start, const char* text_end) throw (VCFException) {
	unsigned int i = 0u;
	const cregex_token_iterator end;
	cregex_token_iterator fields_iter(text_start, text_end, field_split_regex, -1);
	while (fields_iter != end) {
		switch (i) {
			case 0u:
				chrom.parse(*fields_iter);
				break;
			case 1u:
				pos.parse(*fields_iter);
				break;
			case 2u:
				id.parse(*fields_iter);
				break;
			case 3u:
				ref.parse(*fields_iter);
				break;
			case 4u:
				alt.parse(*fields_iter);
				break;
			case 5u:
				qual.parse(*fields_iter);
				break;
			case 6u:
				filter.parse(*fields_iter);
				break;
			case 7u:
				info.parse(*fields_iter);
				break;
			case 8u:
				format.parse(*fields_iter);
				break;
			default:
				try {
					genotypes.at(i - 9u)->parse(*fields_iter);
				} catch (std::out_of_range &e) {
					throw VCFException(__FILE__, __FUNCTION__, __LINE__, "Number of genotype fields does not match number of samples.");
				}
				break;
		}
		++fields_iter;
		++i;
	}
}

unsigned int Variant::get_n_samples() const {
	return samples.size();
}

bool Variant::has_sample(const string& sample) const {
	return samples.count(sample) > 0;
}

long int Variant::get_sample_index(const string& sample) const {
	auto samples_it = samples.find(sample);
	if (samples_it != samples.end()) {
		return static_cast<long int>(samples_it->second);
	} else {
		return numeric_limits<long int>::min();
	}
}

const ChromField& Variant::get_chrom() const {
	return chrom;
}

const PosField& Variant::get_pos() const {
	return pos;
}

const IdField& Variant::get_id() const {
	return id;
}

const RefField& Variant::get_ref() const {
	return ref;
}

const AltField& Variant::get_alt() const {
	return alt;
}

const QualField& Variant::get_qual() const {
	return qual;
}

const FilterField& Variant::get_filter() const {
	return filter;
}

const InfoField& Variant::get_info() const {
	return info;
}

const FormatField& Variant::get_format() const {
	return format;
}

const GenotypeField& Variant::get_genotype(const string& sample) const throw (VCFException) {
	auto samples_it = samples.find(sample);
	if (samples_it == samples.end()) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "No sample with such name.");
	}
	return *genotypes.at(samples_it->second);
}

const GenotypeField& Variant::get_genotype(unsigned int index) const throw (VCFException) {
	try {
		return *genotypes.at(index);
	} catch (std::out_of_range &e) {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "No sample with such index.");
	}
}

}
