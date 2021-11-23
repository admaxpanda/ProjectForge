#include "Player.h"
#include "State.h"
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
	state->stateCalculation(c);
}
Player::Player() {
	//this->state = new Standing(this);
	pos.x = pos.y = 400;
}
double Player::gettoward() {
	return state->toward;
}
CPoint Player::getpicutre() {
	return state->picture;
}