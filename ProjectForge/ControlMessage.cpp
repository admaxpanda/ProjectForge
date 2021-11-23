#include "ControlMessage.h"
ControlMessage::ControlMessage(int ID,double toward) {
	this->ID = ID;
	this->toward = r2a(toward);
}