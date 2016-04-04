#ifndef RESOURCES_SYNCHRONIZER_H
#define RESOURCES_SYNCHRONIZER_H

#include "resources.h"
#include <map>

class resources_synchronizer {
	private:
		std::map<uint16_t, resources*> sections_resources;
};

#endif
