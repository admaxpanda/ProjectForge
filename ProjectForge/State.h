#pragma once
#include "pch.h"
#include "Player.h"
#include "WebMessage.h"
class State
{
public:
	Player* player;
	//时间
	int totTick;
	int startTick;
	int passTick;
	//状态
	CPoint picture;
	int damage;
	CPoint pos;
	double toward;
	int lenth;
	//下一个
	State* next;
	int ID;
	void virtual stateCalculation(WebMessage);
	void virtual damageCalculation(WebMessage);
	void virtual messageReact();
	int virtual isOverlap(CPoint,double,int);
	WebMessage toWebMessage();
	State();
};
class Stand :public State {

};

