#ifndef RESOURCES_H
#define RESOURCES_H

#include "../serializable.h"

class resources: public serializable {
	public:
		uint32_t version;
		void update(uint8_t* raw_resource, uint32_t version) = 0;
};

#endif
