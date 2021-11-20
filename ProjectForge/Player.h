#pragma once
#include "pch.h"
class State;
class ControlMessage;
class Player
{
public:
	State* state;
	CPoint pos;
	int health;
	int body;
	CPoint mousepos;
	//queue<ControlMessage> messageQ;
	queue<int> damageQ;
	queue<int> attackQ;
	int stepCD;
public:
	Player();
	int* toWebMessage();
};

