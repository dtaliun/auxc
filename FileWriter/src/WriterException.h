#ifndef SRC_WRITEREXCEPTION_H_
#define SRC_WRITEREXCEPTION_H_

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>

using namespace std;

namespace sph_umich_edu {

class WriterException : public std::exception {
protected:
	string source_file;
	string function;
	unsigned int line;
	string message;

public:
	WriterException(const char* source_file, const char* function, unsigned int line, const char* message);
	virtual ~WriterException();

	virtual const char* what() const noexcept;

	const string& get_source_file_name();
	const string& get_function_name();
	unsigned int get_line();
	const string& get_message();
};

}

#endif
