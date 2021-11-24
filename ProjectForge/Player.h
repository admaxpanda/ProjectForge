#pragma once
#include "pch.h"
#include "ControlMessage.h"
class State;
class Player
{
public:
	State* state=0;
	State* stateToDelete=0;
	Player* self=0;
	CPoint pos;
	int health = 100;
	int body = 0;
	CPoint mousepos;
	queue<ControlMessage> messageQ;
	queue<int> damageQ;
	queue<int> attackQ;
	int stepCD = 0;
public:
	Player();
	void stateCalculation(const int[]);
	void create(Player*);
	int* toWebMessage();
	int gettoward();
	CPoint getpicutre();
};

