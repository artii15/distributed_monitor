#include "../../inc/example/producer_action.h"

producer_action::producer_action(buffer<uint8_t>* buf) {
	this->buf = buf;
}

void producer_action::perform(monitor* mon) {

}
