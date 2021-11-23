#include "State.h"
State::State() {
}
State::State(Player* player,int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
}
State::~State()
{
	;
}
double State::getPointsLenth(int x1, int y1, int x2, int y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
int State::getAngle(int x1, int y1, int x2, int y2) {
	if (x2 > x1)
		if (y2 > y1)
			return atan(1.0 * (x2 - x1) / (y2 - y1));
		else if (y2 < y1)
			return atan(1.0 * (y1 - y2) / (x2 - x1)) + 90;
		else
			return 90;
	if (x2 < x1)
		if (y2 > y1)
			return atan(1.0 * (y2 - y1) / (x1 - x2)) + 270;
		else if (y2 < y1)
			return atan(1.0 * (x1 - x2) / (y1 - y2)) + 180;
		else
			return 270;
	else
		if (y2 < y1)
			return 180;
		else
			return 0;
}
double State::heron(CPoint a, CPoint b, CPoint c) {
	double x = getPointsLenth(a.x, a.y, b.x, b.y);
	double y = getPointsLenth(a.x, a.y, c.x, c.y);
	double z = getPointsLenth(b.x, b.y, c.x, c.y);
	double p = (x + y + z) / 2;
	return sqrt(p * (p - x) * (p - y) * (p - z));
}
int State::IsOverlapBODY(const int enemy[]) {
	CPoint a[4],b[4];
	a[0].x = a[1].x = pos.x - CHARACTERWIDTH / 4;
	a[2].x = a[3].x = pos.x + CHARACTERWIDTH / 4;
	a[0].y = a[3].y = pos.y - CHARACTERWIDTH / 8 * 3;
	a[1].y = a[2].y = pos.y + CHARACTERWIDTH / 8;
	
	b[0].x = enemy[POSX]; b[0].y = enemy[POSY] - CHARACTERWIDTH / 8;
	b[2].x = b[0].x + enemy[LENTH] * sin(a2r(enemy[TOWARD]));
	b[2].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD]));
	b[1].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD] - enemy[RANGE]));
	b[1].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD] - enemy[RANGE]));
	b[3].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD] + enemy[RANGE]));
	b[3].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD] + enemy[RANGE]));
	
	for (int i = 0; i < 3; i++)
		if (b[i].x > a[0].x && b[i].x<a[2].x && b[i].y>a[0].y && b[i].y < a[1].y)
			return 1;
	return 0;
}
int State::IsOverlapATTACK(const int enemy[]) {
	CPoint a[4], b[4];
	a[0].x = pos.x; a[0].y = pos.y - CHARACTERWIDTH / 8;
	a[2].x = a[0].x + lenth * sin(a2r(toward));
	a[2].y = a[0].x + lenth * cos(a2r(toward));
	a[1].x = a[0].x + lenth * sin(a2r((toward - range)));
	a[1].y = a[0].x + lenth * cos(a2r((toward - range)));
	a[3].x = a[0].x + lenth * sin(a2r((toward + range)));
	a[3].y = a[0].x + lenth * cos(a2r((toward + range)));

	b[0].x = enemy[POSX]; b[0].y = enemy[POSY] - CHARACTERWIDTH / 8;
	b[2].x = b[0].x + enemy[LENTH] * sin(a2r(enemy[TOWARD]));
	b[2].y = b[0].x + enemy[LENTH] * cos(a2r(enemy[TOWARD]));
	b[1].x = b[0].x + enemy[LENTH] * sin(a2r((enemy[TOWARD] - enemy[RANGE])));
	b[1].y = b[0].x + enemy[LENTH] * cos(a2r((enemy[TOWARD] - enemy[RANGE])));
	b[3].x = b[0].x + enemy[LENTH] * sin(a2r((enemy[TOWARD] + enemy[RANGE])));
	b[3].y = b[0].x + enemy[LENTH] * cos(a2r((enemy[TOWARD] + enemy[RANGE])));

	double sq = heron(a[0], a[1], a[2]) + heron(a[0], a[2], a[3]);
	for (int i = 0; i < 4; i++) {
		double tmp = 0;
		for (int k = 0; k < 4; k++)
			tmp += k < 3 ? heron(b[i], a[k], a[k + 1]) : heron(b[i], a[3], a[0]);
		if (tmp > sq)
			if (tmp - sq < 10)
				return 1;
			else;
		else
			if (sq - tmp < 10)
				return 1;
	}
	return 0;
}
Standing::Standing(Player* player, int toward) {
	ID |= DAMAGESTANDING|DISATTACKING;
}
void Standing::damageCalculation(const int enemy[]) {
	if (!(enemy[STATEID] & ATTACKSTATE ^ ATTACKING) &&
		!(enemy[STATEID] & STAGE ^ DAMAGE)
		) {
		if (IsOverlapBODY(enemy)) {
			double series = (enemy[LENTH]-getPointsLenth(enemy[POSX], enemy[POSY], pos.x, pos.y)) / enemy[LENTH];
			series = series < 0 ? 0.5 : (series+1)/2;
			player->health -= series * enemy[damage];
			player->body += series * enemy[damage];
			player->state = new Damaged(player, toward);
			delete this;
		}
	}
}
void Standing::stateCalculation(const int enemy[]) {
	damageCalculation(enemy);
	if (!(player->messageQ.empty())) {
		ControlMessage tmp = player->messageQ.front();
		player->messageQ.pop();
		if (tmp.ID == MESSAGEMOVE)
			player->state = new Moving(player, tmp.toward);
		if (tmp.ID == MESSAGEATTACK)
			player->state = new AttackingMID(player, tmp.toward);
		if (tmp.ID == MESSAGEDEFEND)
			player->state = new Defending(player, tmp.toward);
		if (tmp.ID == MESSAGESPIKE)
			player->state = new Spiking(player, tmp.toward);
		if (tmp.ID == MESSAGEJUMP)
			player->state = new Jumping(player, tmp.toward);
		if (tmp.ID == MESSAGESTEP)
			player->state = new Steping(player, tmp.toward);
		if (tmp.ID == MESSAGESQUAT)
			player->state = new Squating(player, tmp.toward);
		delete this;
	}
}

Damaged::Damaged(Player* player, int toward) {
	if (player->health < 0) {
		player->state = new Dead(player, toward);
		delete this;
	}
	if (player->body > 100) {
		player->state = new Stocked(player, toward);
		delete this;
	}
	ID |= METHODDAMAGE;
	picture.x = 4;
	picture.y = 0;
	passtick = 0;
	stagecount = 2;
	stagetick[0] = 12;
	stagetick[1] = 20 - 4 * player->damageQ.size();
	player->damageQ.push(1);
}
void Damaged::stateCalculation(const int enemy[])
{
	damageCalculation(enemy);
	passtick++;
	if (stagenow)
		if (!(player->messageQ.empty())) {
			ControlMessage tmp = player->messageQ.front();
			if (tmp.ID == MESSAGESTEP) {
				player->messageQ.pop();
				player->state = new Steping(player, tmp.toward);
				delete this;
			}
		}
	if(passtick>stagetick[stagenow])
		if (stagenow) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			delete this;
		}
		else {
			stagenow++;
			passtick = 0;
		}
}

Moving::Moving(Player* player, int toward) {
	ID |= METHODMOVING|STAGEACTING;
	stagecount = 2;
	stagetick[0] = stagetick[1] = 20;
	if (1.0 * (180 - toward) / (player->mousepos.x - pos.x) > 0) {
		picture.x = 2;
		picture.y = 1;
	}
	else {
		picture.x = 0;
		picture.y = 1;
	}
}
void Moving::movestep(int x,int y) {
	if (x > 0)
		if (pos.x < 1366 - CHARACTERWIDTH / 2 - x)
			player->pos.x = pos.x = pos.x + x;
		else
			player->pos.x = pos.x = 1366 - CHARACTERWIDTH / 2;
	if (x < 0)
		if (pos.x > CHARACTERWIDTH / 2 - x)
			player->pos.x = pos.x = pos.x + x;
		else
			player->pos.x = pos.x = CHARACTERWIDTH / 2;
	if (y > 0)
		if (pos.y < 768 - CHARACTERWIDTH / 8 - y)
			player->pos.y = pos.y = pos.y + y;
		else
			player->pos.y = pos.y = 768 - CHARACTERWIDTH / 8;
	if (y < 0)
		if (pos.y > CHARACTERWIDTH - y)
			player->pos.y = pos.y = pos.y + y;
		else
			player->pos.y = pos.y = CHARACTERWIDTH;

}
void Moving::stateCalculation(const int enemy[]) {
	damageCalculation(enemy);
	passtick++;
	if (toward == 0)
		movestep(0, -10);
	else if (toward == 45)
		movestep(7, -7);
	else if (toward == 90)
		movestep(10, 0);
	else if (toward == 135)
		movestep(7, 7);
	else if (toward == 180)
		movestep(0, 10);
	else if (toward == 225)
		movestep(-7, 7);
	else if (toward == 270)
		movestep(-10, 0);
	else if (toward == 315)
		movestep(-7, -7);
	else if (toward == 360)
		movestep(0, -10);
	if (passtick > stagetick[stagenow]) {
		if (stagenow) {
			player->state = new Standing(player, toward);
			delete this;
		}
		else {
			pos.x++;
			passtick = 0;
			stagenow ++;
		}
	}
	if (!(player->messageQ.empty()))
		if (!(player->messageQ.front().ID == MESSAGEMOVE
			&& player->messageQ.front().toward == toward)) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			delete this;
		}
}

Steping::Steping(Player*, int) {
	ID |= METHODSTEP|STAGEPREING;
	stagecount = 3;
	stagetick[0] = 5;
	stagetick[1] = 30;
	stagetick[2] = 5;
	picture.x = 5;
	picture.y = 2;
}
void Steping::stateCalculation(const int enemy[]) {
	if (stagenow != 1 && passtick > 10)
		damageCalculation(enemy);
	passtick++;
	if(!stagenow)
		if (!(player->messageQ.empty()))
			if (!(player->messageQ.front().ID == MESSAGESTEP
				&& player->messageQ.front().toward == toward)) {
				player->state = new Standing(player, toward);
				player->state->stateCalculation(enemy);
				delete this;
			}
	if(stagenow==2)
		if (!(player->messageQ.empty())) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			delete this;
		}
	if (passtick > stagetick[stagenow]) {
		if (stagenow < 2) {
			if (stagenow)
				ID = ID & STAGEANY | STAGEACTING;
			else
				ID = ID & STAGEANY | STAGEENDING;
			stagenow++;
			passtick = 0;
			picture.x++;
		}
		else {
			player->state = new Standing(player, toward);
			delete this;
		}
	}
}


void Jumping::damageCalculation(const int[])
{

}
Jumping::Jumping(Player* player, int toward)
{
	ID |= DAMAGEJUMPING;
}

void Squating::damageCalculation(const int[])
{
	
}

Squating::Squating(Player* player, int toward)
{
	ID |= DAMAGESQUATING;
}

void Dead::damageCalculation(const int enemy[])
{
}

Dead::Dead(Player* player, int toward)
{
	ID |= DAMAGEDEAD;
}
