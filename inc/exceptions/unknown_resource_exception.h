#ifndef UNKNOWN_RESOURCE_EXCEPTION_H
#define UNKNOWN_RESOURCE_EXCEPTION_H

#include <exception>

class unknown_resource_exception: public std::exception {
	public:
		unknown_resource_exception(const char* message);
		virtual const char* what() const throw();

	private:
		const char* message;
};

#endif
