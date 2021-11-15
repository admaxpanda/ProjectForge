#pragma once
#include "pch.h"
#include "Player.h"
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
	void virtual stateCalculation(int[]);
	void virtual damageCalculation(int[]);
	void virtual messageReact();
	int virtual isOverlap(CPoint,double,int);
	int * toWebMessage();
	State();
};
class Stand :public State {

};

