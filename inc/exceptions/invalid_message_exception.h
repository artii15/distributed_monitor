#ifndef INVALID_MESSAGE_EXCEPTION_H
#define INVALID_MESSAGE_EXCEPTION_H

#include <exception>

class invalid_message_exception: public std::exception {
	public:
		invalid_message_exception(const char* message);
		virtual const char* what() const throw();

	private:
		const char* message;
};

#endif
