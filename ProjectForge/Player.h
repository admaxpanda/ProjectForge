#pragma once
#include "pch.h"
#include "ControlMessage.h"
class State;
class Player
{
public:
	State* state=null;
	CPoint pos;
	int health;
	int body;
	CPoint mousepos;
	queue<ControlMessage> messageQ;
	queue<int> damageQ;
	queue<int> attackQ;
	int stepCD;
public:
	Player();
	void stateCalculation(const int []);
	int* toWebMessage();
};

