#ifndef SRC_FIELD_H_
#define SRC_FIELD_H_

#include <iostream>
#include <regex>
#include "VCFException.h"

using namespace std;

namespace sph_umich_edu {

class Field {
public:
	Field();
	virtual ~Field();

	Field(const Field& field) = delete;
	Field& operator=(const Field& field) = delete;
	Field(Field&& field) = delete;
	Field& operator=(Field&& field) = delete;

	virtual void parse(const csub_match& text) throw (VCFException) = 0;
	virtual void print() const = 0;
};

}

#endif
