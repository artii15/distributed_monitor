#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <stdint.h>
#include <stdlib.h>
#include <stdexcept>
#include <string.h>
#include "../resources_synchronizer/resources.h"

class buffer: public resources {
	public:
		buffer(uint32_t buf_size) {
			this->buf_size = buf_size;
			number_of_elements = 0;
			elements = (uint16_t*)calloc(buf_size, sizeof(uint16_t));
		}

		~buffer() {
			free(elements);
		}

		uint32_t count() {
			return number_of_elements;
		}

		uint32_t capacity() {
			return buf_size;
		}

		void remove_from(unsigned idx, uint16_t blank_element) {
			elements[idx] = blank_element;
			--number_of_elements;
		}

		void insert_at(unsigned idx, uint16_t element) {
			elements[idx] = element;
			++number_of_elements;
		}

		unsigned find_index_of(uint16_t element) {
			for(unsigned i = 0; i < buf_size; ++i) {
				if(elements[i] == element) {
					return i;
				}
			}
			throw std::logic_error("element not found!");
		}

		virtual void serialize_resources_members(uint8_t* buf) {
			uint8_t* seek = buf;

			uint32_t buf_size = htonl(this->buf_size);
			memcpy(seek, &buf_size, sizeof(buf_size));
			seek += sizeof(buf_size);

			uint32_t number_of_elements = htonl(number_of_elements);
			memcpy(seek, &number_of_elements, sizeof(number_of_elements));
			seek += sizeof(number_of_elements);

			for(unsigned i = 0; i < buf_size; ++i) {
				uint16_t element = htons(elements[i]);
				memcpy(seek, &element, sizeof(element));
				seek += sizeof(element);
			}
		}

		virtual void deserialize_resources_members(uint8_t* buf) {
			uint8_t* seek = buf;

			uint32_t buf_size;
			memcpy(&buf_size, seek, sizeof(buf_size));
			this->buf_size = ntohl(buf_size);
			seek += sizeof(buf_size);

			uint32_t number_of_elements;
			memcpy(&number_of_elements, seek, sizeof(number_of_elements));
			this->number_of_elements = ntohl(number_of_elements);
			seek += sizeof(number_of_elements);

			elements = (uint16_t*)realloc(elements, this->buf_size*sizeof(uint16_t));

			for(unsigned i = 0; i < this->buf_size; ++i) {
				uint16_t element;
				memcpy(&element, seek, sizeof(element));
				elements[i] = ntohs(element);
				seek += sizeof(uint16_t);
			}
		}

		virtual size_t calculate_resources_members_size() {
			return sizeof(buf_size) + sizeof(number_of_elements) + buf_size*sizeof(uint16_t);
		}

	private:
		uint32_t buf_size;
		uint32_t number_of_elements;
		uint16_t* elements;
};

#endif
