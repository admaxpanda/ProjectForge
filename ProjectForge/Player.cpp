#include "Player.h"
#include "State.h"
#include "conio.h"
int* Player::toWebMessage() {
	int l[11];
	l[PICTUREX] = state->picture.x;
	l[PICTUREY] = state->picture.y;
	l[DAMAGE] = state->damage;
	l[POSX] = state->pos.x;
	l[POSY] = state->pos.y;
	l[TOWARD] = state->toward;
	l[LENTH] = state->lenth;
	l[STATEID] = state->ID;
	l[HEALTH] = health;
	l[BODY] = body;
	l[RANGE] = state->range;
	return l;
}
void Player::stateCalculation(const int c[]) {
	//_cprintf("QAQ");
	state->player = this;
	//_cprintf("%d\n", state->ID);
	state->stateCalculation(c);
}
Player::Player() {
	//this->state = new Standing(this);
	//self = this;
	this->state = new Standing(this, 90);
	state->player = this;
	pos.x = pos.y = 400;
}
void Player::create(Player* p) {
	//this->state = new Standing(p, 0);
}
int Player::gettoward() {
	return state->toward;
}
CPoint Player::getpicutre() {
	return state->picture;
}