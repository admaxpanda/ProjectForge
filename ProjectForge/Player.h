#pragma once
#include "pch.h"
#include "Message.h"
class State;
class Player
{
public:
	State* state;
	CPoint pos;
	int health;
	int body;
	CPoint mousepos;
	queue<Message> messageQ;
	queue<int> damageQ;
	queue<int> attackQ;
	int stepCD;
};

