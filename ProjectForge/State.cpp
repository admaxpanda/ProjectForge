#include "State.h"
WebMessage State::toWebMessage()
{
	return WebMessage(
		this->picture,
		this->damage,
		this->pos,
		this->toward,
		this->lenth,
		this->ID,
		this->player->health,
		this->player->body
	);
}