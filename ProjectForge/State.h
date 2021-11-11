#pragma once
#include "pch.h"
#include "Player.h"
#include "WebMessage.h"
class State
{
public:
	Player* player;
	//ʱ��
	int totTick;
	int startTick;
	int passTick;
	//״̬
	CPoint picture;
	int damage;
	CPoint pos;
	double toward;
	int lenth;
	//��һ��
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

