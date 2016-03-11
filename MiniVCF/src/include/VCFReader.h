#ifndef SRC_VCFREADER_H_
#define SRC_VCFREADER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <memory>

#include "../../../FileReader/src/include/ReaderFactory.h"
#include "VCFException.h"
#include "Meta.h"
#include "Variant.h"


using namespace std;

namespace sph_umich_edu {

class VCFReader {
private:
	regex meta_entry_regex;
	regex header_entry_regex;
	regex field_split_regex;

	unique_ptr<Reader> reader;

	string name;
	string format;

	vector<unique_ptr<Meta>> metas;
	Variant variant;

	void read_metas() throw (ReaderException, VCFException);

public:
	VCFReader();
	virtual ~VCFReader();

	VCFReader(const VCFReader& reader) = delete;
	VCFReader& operator=(const VCFReader& reader) = delete;
	VCFReader(VCFReader&& reader) = delete;
	VCFReader& operator=(VCFReader&& reader) = delete;

	void open(const string& name) throw (ReaderException, VCFException);
	void open(const char* name) throw (ReaderException, VCFException);

	bool read_next_variant() throw (ReaderException, VCFException);
	const Variant& get_variant();

	void close() throw (ReaderException);
};

}

#endif
