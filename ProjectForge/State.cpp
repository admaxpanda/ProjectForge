#include "State.h"
State::State() {
}
State::State(Player* player) {
	this->player = player;
	this->pos = player->pos;
}
Standing::Standing(Player* player) {
	picture.x = 0;
	picture.y = 0;
	pos.x = 800;
	pos.y = 400;
	toward = MATHPI/2*3;
}
void Standing::damageCalculation(int[]) {

}
void Standing::stateCalculation(const int[]) {

}