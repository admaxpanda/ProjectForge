#include "State.h"
#include "conio.h"
State::State() {

}
State::State(Player* player,int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
}
State::~State()
{
	if(next)
		delete next;
}
void State::deleteState() {
	if (player->stateToDelete) {
		State* tmp = player->stateToDelete;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = this;
	}
	else
		player->stateToDelete = this;
}
void State::movestep(int x, int y) {
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
int State::IsOverlapBODY(CPoint pos) {
	CPoint a[4], b[4];
	a[0].x = a[1].x = pos.x - CHARACTERWIDTH / 4;
	a[2].x = a[3].x = pos.x + CHARACTERWIDTH / 4;
	a[0].y = a[3].y = pos.y - CHARACTERWIDTH / 8 * 3;
	a[1].y = a[2].y = pos.y + CHARACTERWIDTH / 8;

	b[0].x = this->pos.x; b[0].y = this->pos.y -CHARACTERWIDTH / 8;
	b[2].x = b[0].x + lenth * sin(a2r(toward));
	b[2].y = b[0].x + lenth * cos(a2r(toward));
	b[1].y = b[0].x + lenth * cos(a2r(toward - range));
	b[1].y = b[0].x + lenth * cos(a2r(toward - range));
	b[3].y = b[0].x + lenth * cos(a2r(toward + range));
	b[3].y = b[0].x + lenth * cos(a2r(toward + range));

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
Standing::Standing(Player*player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID |= DAMAGESTANDING|DISATTACKING;
}
Standing::Standing()
{
	ID |= DAMAGESTANDING | DISATTACKING;
}
int Standing::damageCalculation(const int enemy[]) {
	if (!(enemy[STATEID] & ATTACKSTATE ^ ATTACKING) &&
		!(enemy[STATEID] & STAGE ^ DAMAGE)
		) {
		if (IsOverlapBODY(enemy)) {
			double series = (enemy[LENTH]-getPointsLenth(enemy[POSX], enemy[POSY], pos.x, pos.y)) / enemy[LENTH];
			series = series < 0 ? 0.5 : (series+1)/2;
			player->health -= series * enemy[damage];
			player->body += series * enemy[damage];
			player->state = new Damaged(player, toward);
			deleteState();
			return 1;
		}
	}
	return 0;
}
void Standing::stateCalculation(const int enemy[]) {
	if(damageCalculation(enemy))return;
	/*if (this->player)
		_cprintf("???");*/
	//_cprintf("%d", (toward));
	if (!(player->messageQ.empty())) {
		ControlMessage tmp = player->messageQ.front();
		player->messageQ.pop();
		//_cprintf("%d %d\n", tmp.ID, tmp.toward);
		if (tmp.ID == MESSAGEMOVE)
			player->state = new Moving(player, tmp.toward);
		if (tmp.ID == MESSAGEATTACK)
			player->state = new AttackingMID(player, tmp.toward);
		if (tmp.ID == MESSAGEDEFEND)
			player->state = new Defending(player, tmp.toward);
		if (tmp.ID == MESSAGESPIKE)
			player->state = new Spiking(player, tmp.toward);
		/*if (tmp.ID == MESSAGEJUMP)
			player->state = new Jumping(player, tmp.toward);*/
		if (tmp.ID == MESSAGESTEP)
			player->state = new Steping(player, tmp.toward);
		/*if (tmp.ID == MESSAGESQUAT)
			player->state = new Squating(player, tmp.toward);*/
		deleteState();
		return;
	}

}

Damaged::Damaged(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	if (player->health < 0) {
		player->state = new Dead(player, toward);
		deleteState();
		return;
	}
	if (player->body > 100) {
		player->state = new Stocked(player, toward);
		deleteState();
		return;
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
	if(damageCalculation(enemy))return;
	passtick++;
	if (stagenow)
		if (!(player->messageQ.empty())) {
			ControlMessage tmp = player->messageQ.front();
			if (tmp.ID == MESSAGESTEP) {
				player->messageQ.pop();
				player->state = new Steping(player, tmp.toward);
				deleteState();
				return;
			}
		}
	if(passtick>stagetick[stagenow])
		if (stagenow) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			deleteState();
			return;
		}
		else {
			stagenow++;
			passtick = 0;
		}
}

Moving::Moving(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID |= METHODMOVING|STAGEACTING;
	stagecount = 2;
	stagetick[0] = stagetick[1] = 3;
	if (1.0 * (180 - toward) / (player->mousepos.x - pos.x) >= 0) {
		picture.x = 2;
		picture.y = 1;
	}
	else {
		picture.x = 0;
		picture.y = 1;
	}
	while (!player->attackQ.empty())
		player->attackQ.pop();
	while (!player->damageQ.empty())
		player->damageQ.pop();
}
void Moving::stateCalculation(const int enemy[]) {
	if(damageCalculation(enemy))return;
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
			deleteState();
			return;
		}
		else {
			picture.x++;
			passtick = 0;
			stagenow ++;
		}
	}
	if (!(player->messageQ.empty()))
		if (!(player->messageQ.front().ID == MESSAGEMOVE
			&& player->messageQ.front().toward == toward)) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			deleteState();
			return;
		}
}

Steping::Steping(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID |= METHODSTEP|STAGEPREING;
	stagecount = 3;
	stagetick[0] = 1;
	stagetick[1] = 2;
	stagetick[2] = 1;
	picture.x = 5;
	picture.y = 2;

	while (!player->attackQ.empty())
		player->attackQ.pop();
	while (!player->damageQ.empty())
		player->damageQ.pop();

}
void Steping::stateCalculation(const int enemy[]) {
	if (stagenow != 1 && passtick > 10)
		if(damageCalculation(enemy))return;
	passtick++;
	if (stagenow == 0) {
		if (!(enemy[STATEID] & ATTACKTYPE ^ ATTACKSPIKE)
			&& !(enemy[STATEID] & STAGE ^ STAGEACTING)) {
			player->state = new Lookthrough(player, toward);
			deleteState();
			return;
		}
		else if (!(player->messageQ.empty()))
			if (!(player->messageQ.front().ID == MESSAGESTEP
				&& player->messageQ.front().toward == toward)) {
				player->state = new Standing(player, toward);
				player->state->stateCalculation(enemy);
				deleteState();
				return;
			}
	}
	if (stagenow == 1) {
		if (toward == 0)
			movestep(0, -20);
		else if (toward == 45)
			movestep(14, -14);
		else if (toward == 90)
			movestep(20, 0);
		else if (toward == 135)
			movestep(14, 14);
		else if (toward == 180)
			movestep(0, 20);
		else if (toward == 225)
			movestep(-14, 14);
		else if (toward == 270)
			movestep(-20, 0);
		else if (toward == 315)
			movestep(-14, -14);
		else if (toward == 360)
			movestep(0, -20);
	}
	if(stagenow==2)
		if (!(player->messageQ.empty())) {
			player->state = new Standing(player, toward);
			player->state->stateCalculation(enemy);
			deleteState();
			return;
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
			deleteState();
			return;
		}
	}
}

void AttackingMID::stateCalculation(const int enemy[]){
	if (damageCalculation(enemy))return;
	passtick++;
	//_cprintf("%d:%d\n", stagenow, passtick);
	if (stagenow == 0 || stagenow == 3) {
		//_cprintf("TIP1\n");
		if (stagenow == 3);
			//_cprintf("%d\n",passtick);
		if (!player->messageQ.empty()) {
			if (player->messageQ.front().ID == MESSAGESTEP) {
				player->state = new Standing(player, toward);
				deleteState();
				return;
			}

		}
	}
	if (stagenow==2) {
		//_cprintf("TIP2\n");
		if (!(enemy[STATEID] & METHOD ^ METHODDEFENDING) &&
			!(enemy[STATEID] & STAGE ^ STAGEACTING)) {
			if (IsOverlapATTACK(enemy)) {
				passtick = 0;
				stagenow = 4;
				picture.x += 2;
				player->body += 8 * player->attackQ.size();
				if (player->body > 100) {
					player->state = new Stocked(player, toward);
					deleteState();
					return;
				}
				//stagetick[4] += 6 * player->attackQ.size();
				player->attackQ.push(1);
				ID += 2;
			}
			else if (IsOverlapBODY(CPoint(enemy[POSX], enemy[POSY]))) {
				passtick = 0;
				stagenow = 3;
				picture.x++;
				player->attackQ.push(1);
				ID++;
			}
		}
		else if (IsOverlapBODY(CPoint(enemy[POSX], enemy[POSY]))) {
			passtick = 0;
			stagenow = 3;
			picture.x++;
			player->attackQ.push(1);
			ID++;
		}
	}
	if (passtick > stagetick[stagenow]) {
		//_cprintf("TIP3\n");
		if (stagenow < 3) {
			passtick = 0;
			stagenow++;
			picture.x++;
			ID++;
		}
		else {
			//_cprintf("QAQ");
			player->state = new Standing(player, toward);
			deleteState();
			return;
		}
	}

}

AttackingMID::AttackingMID(Player* player, int toward) {
	_cprintf("\n");
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID = ID & ATTACKSTATEANY | ATTACKING | STAGEPREING | ATTACKMID;	
	stagecount = 5;
	stagetick[0] = 1;
	stagetick[1] = 2;
	stagetick[2] = 1;
	stagetick[3] = 1;
	stagetick[4] = 2;
	picture.x = 0;
	picture.y = 2;
	lenth = CHARACTERWIDTH / 4 * 3;
	range = 45;
	damage = 10;
}





Defending::Defending(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	stagecount = 4;
	ID |= METHODDEFENDING | STAGEPREING;
	stagetick[0] = 1;
	stagetick[1] = 2;
	stagetick[2] = 1;
	stagetick[3] = 2;
	picture.x = 4;
	picture.y = 1;
	lenth = CHARACTERWIDTH / 4 * 3;
	range = 60;
}

void Defending::stateCalculation(const int enemy[]) {
	passtick++;
	if (stagenow == 2||stagenow==0) {
		if (damageCalculation(enemy))return;
		if(!player->messageQ.empty())
			if (player->messageQ.front().ID == MESSAGESTEP)
			{
				player->state = new Standing(player, toward);
				deleteState();
				return;
			}
	}
	else if(stagenow==1){
		if(!(enemy[STATEID]&ATTACKSTATE^ATTACKING))
			if (!(enemy[STATEID] & STAGE ^ STAGEDAMAGING))
				if ((enemy[STATEID] & ATTACKTYPE ^ ATTACKDOWN))
					if (IsOverlapATTACK(enemy)) {
						player->body += enemy[damage] - (10 - passtick / 4);
						if (player->body > 100) {
							player->state = new Stocked(player, toward);
							deleteState();
							return;
						}
						stagenow = 3;
						//stagetick[3] -= 2 * player->damageQ.size();
						player->damageQ.push(1);
						passtick = 0;
						picture.x += 2;
						ID += 3;
					}
	}
	if (passtick > stagetick[stagenow]) {
		if (stagenow == 0) {
			passtick = 0;
			stagenow++;
			picture.x++;
			ID++;
		}
		else if (stagenow == 1) {
			passtick = 0;
			stagenow++;
			picture.x++;
			ID += 2;
		}
		else {
			player->state = new Standing(player, toward);
			deleteState();
			return;
		}
	}
}

Spiking::Spiking(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID = ATTACKING | ATTACKSPIKE | DAMAGESTANDING | STAGEPREING;
	stagecount = 6;
	stagetick[0] = 1;
	stagetick[1] = 1;
	stagetick[2] = 1;
	stagetick[3] = 1;
	stagetick[4] = 5;
	stagetick[5] = 1;
	picture.y = 3;
	picture.x = 0;
	range = 30;
	lenth = CHARACTERWIDTH / 2 * 3;
}
void Spiking::stateCalculation(const int enemy[]) {
	if (damageCalculation(enemy))return;
	passtick++;
	if (stagenow == 0 || stagenow == 3) {
		if (!player->messageQ.empty()) {
			if (player->messageQ.front().ID == MESSAGESTEP) {
				player->state = new Standing(player, toward);
				deleteState();
				return;
			}
		}
	}
	if((stagenow==0)&&(!player->messageQ.empty()))
		if (player->messageQ.front().ID == MESSAGESPIKE) {
			toward = player->messageQ.front().toward;
			passtick = 0;
			player->messageQ.pop();
		}
	if(stagenow==1)
		if(!(enemy[STATEID]&METHOD^METHODSTEP))
			if (!(enemy[STATEID] & STAGE ^ STAGEPREING))
			{
				player->body += 30;
				if (player->body > 100) {
					player->state = new Stocked(player, toward);
					deleteState();
					return;
				}
				ID += 4;
				stagenow = 4;
				passtick = 0;
				picture.x += 3;
			}
	if (stagenow == 2) {
		if (!(enemy[STATEID] & METHOD ^ METHODDEFENDING) &&
			!(enemy[STATEID] & STAGE ^ STAGEACTING) &&
			IsOverlapATTACK(enemy) ){
			passtick = 0;
				stagenow = 5;
				picture.x = 3;
				picture.y = 2;
				player->body += 8 * player->attackQ.size();
				if (player->body > 100) {
					player->state = new Stocked(player, toward);
						deleteState();
						return;
				}
			stagetick[5] += 6 * player->attackQ.size();
			player->attackQ.push(1);
			ID += 2;
		}
		else if (IsOverlapBODY(CPoint(enemy[POSX], enemy[POSY]))) {
			passtick = 0;
			stagenow = 3;
			picture.x++;
			player->attackQ.push(1);
			ID++;
		}
	}
	if (passtick > stagetick[stagenow]) {
		if (stagenow < 3) {
			passtick = 0;
			stagenow++;
			picture.x++;
			ID++;
		}
		else {
			player->state = new Standing(player, toward);
			deleteState();
			return;
		}
	}
		
}


Stocked::Stocked(Player* player, int toward) {
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID |= METHODSTOCKING;
	stagecount = 1;
	stagetick[0] = 60;
	picture.y = 0;
	picture.x = 3;
}
void Stocked::stateCalculation(const int enemy[]) {
	if (damageCalculation(enemy))return;
	passtick++;
	if (passtick > stagetick[stagenow]) {
		player->state = new Standing(player, toward);
		deleteState();
		return;
	}
}

Lookthrough::Lookthrough(Player* player,int toward){
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	ID |= METHODLOOKTHOUGH;
	stagecount = 1;
	stagetick[0] = 60;
	picture.x = 2;
	picture.y = 0;
}
void Lookthrough::stateCalculation(const int enemy[]) {
	if (damageCalculation(enemy))return;
	passtick++;
	if (passtick > stagetick[stagenow]) {
		player->state = new Standing(player, toward);
		deleteState();
		return;
	}
	if (!player->messageQ.empty()) {
		player->state = new Standing(player, toward);
		deleteState();
		return;
	}
}

int Jumping::damageCalculation(const int[])
{
	return 0;
}
void Jumping::stateCalculation(const int[])
{
}
Jumping::Jumping(Player* player, int toward)
{
	ID |= DAMAGEJUMPING;
}

int Squating::damageCalculation(const int[])
{
	return 0;
}

void Squating::stateCalculation(const int[])
{
}

Squating::Squating(Player* player, int toward)
{
	ID |= DAMAGESQUATING;
}

int Dead::damageCalculation(const int enemy[])
{
	return 0;
}

void Dead::stateCalculation(const int[])
{
	passtick++;
	if (passtick > stagetick[stagenow]) {
		player->health = 100;
		player->body = 0;
		player->state = new Standing(player, toward);
		deleteState();
		return;
	}
}

Dead::Dead(Player* player, int toward)
{
	ID |= DAMAGEDEAD;
	this->player = player;
	this->pos = player->pos;
	this->toward = toward;
	stagecount = 1;
	stagetick[0] = 30;
	picture.x = 1;
}
