#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stdint.h>

template <class T>
class buffer {
	public:
		buffer(uint32_t size) {

		}

		uint32_t count() {
			return 0;
		}

		uint32_t get_capacity() {
			return 0;
		}
	private:
		uint32_t size;
};

#endif
