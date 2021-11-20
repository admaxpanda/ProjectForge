#include "State.h"
State::State(Player* player) {
	this->player = player;
	this->pos = player->pos;
}