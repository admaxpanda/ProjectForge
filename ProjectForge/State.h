#pragma once
#include "pch.h"
#include "Player.h"
class State
{
public:
	Player* player;
	//时间
	int totTick=0;
	int startTick=0;
	int passTick=0;
	//状态
	CPoint picture;
	int damage;
	CPoint pos;
	double toward;
	int lenth;
	//下一个
	State* next;
	int ID;
	void virtual stateCalculation(const int[])=0;
	void virtual damageCalculation(int[]) = 0;
	void virtual messageReact() = 0;
	int virtual isOverlap(CPoint,double,int) = 0;
	State(Player*);
};
class Standing :public State {
	//void virtual damageCalculation(int[]);
};
class Movint :public Standing {

};
class Jumping :public State {
	//void virtual damageCalculation(int[]);
};
class squating :public State {
	//void virtual damageCalculation(int[]);
};
class dead :public State {
	//void virtual damageCalculation(int[]);
};
