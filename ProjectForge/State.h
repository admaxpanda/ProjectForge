#pragma once
#include "pch.h"
#include "Player.h"
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
	void virtual stateCalculation(int[]);
	void virtual damageCalculation(int[]);
	void virtual messageReact();
	int virtual isOverlap(CPoint,double,int);
	int * toWebMessage();
	State();
};
class Stand :public State {

};

