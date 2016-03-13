#include "include/VCFReader.h"

namespace sph_umich_edu {

VCFReader::VCFReader() :
		meta_entry_regex("^#{2}.*$"),
		header_entry_regex("^#CHROM\\tPOS\\tID\\tREF\\tALT\\tQUAL\\tFILTER\\tINFO\\tFORMAT\\t((?:[[:graph:]]+)(?:\\t[[:graph:]]+)*)$"),
		field_split_regex("\\t"),
		reader(nullptr),
		name(""), format("")  {

}

VCFReader::~VCFReader() {

}

void VCFReader::open(const string& name) throw (ReaderException, VCFException) {
	if (reader == nullptr) {
		open(name.c_str());
	}
}

void VCFReader::open(const char* name) throw (ReaderException, VCFException) {
	if (reader == nullptr) {
		this->name = name;
		reader = ReaderFactory::create(ReaderFactory::is_gzip(this->name) == true ? ReaderFactory::READER_TYPE::GZIP : ReaderFactory::READER_TYPE::TEXT);
		reader->set_file_name(this->name);
		reader->open();
		read_metas();
	}
}

void VCFReader::close() throw (ReaderException) {
	if (reader != nullptr) {
		reader->close();
		reader.reset(nullptr);
		name = "";
		format = "";
		metas.clear();
	}
}

void VCFReader::read_metas() throw (ReaderException, VCFException) {
	char* line = nullptr;
	long int line_length = 0;
	cmatch matches;
	const cregex_token_iterator end;

	while ((line_length = reader->read_line()) >= 0) {
		line = reader->get_line();
		if (!regex_match(line, meta_entry_regex)) {
			break;
		}
		metas.emplace_back(new Meta());
		metas.back()->parse(line);
	}

	if (regex_match(line, matches, header_entry_regex)) {
		cregex_token_iterator samples_iter(matches[1].first, matches[1].second, field_split_regex, -1);
		while (samples_iter != end) {
			variant.add_sample(std::move(samples_iter->str()));
			++samples_iter;
		}
	} else {
		throw VCFException(__FILE__, __FUNCTION__, __LINE__, "No valid VCF header.");
	}

}

bool VCFReader::read_next_variant() throw (ReaderException, VCFException) {
	char* line = reader->get_line();
	long int line_length = 0;

	if ((line_length = reader->read_line()) >= 0) {
		variant.parse(line, line + line_length);
		return true;
	}

	return false;
}

const Variant& VCFReader::get_variant() {
	return variant;
}

}
