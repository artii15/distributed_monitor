#ifndef MESSAGES_TAGS_H
#define MESSAGES_TAGS_H

typedef struct MESSAGE_TAG {
	const static uint16_t LOCK_REQUEST = 1;
	const static uint16_t LOCK_RESPONSE = 2;
	const static uint16_t RELEASE_SIGNAL = 3;
	const static uint16_t WAIT_SIGNAL = 4;
	const static uint16_t WAKE_SIGNAL = 5;
	const static uint16_t RESOURCES_UPDATE = 6;
} MESSAGE_TAG;

#endif
