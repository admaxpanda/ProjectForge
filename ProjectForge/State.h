#pragma once
#include "pch.h"
#include "Player.h"
class State
{
public:
	Player* player=NULL;
	//时间
	int stagecount=0;
	int stagenow = 0;
	int stagetick[10] = { 0 };
	int passtick = 0;
	//状态
	CPoint picture=CPoint(0,0);
	int damage=0;
	CPoint pos=CPoint(800,400);
	int toward= 90;
	int lenth=0;
	int range=0;
	//下一个
	State* next=NULL;
	int ID = 0;
	void virtual stateCalculation(const int[])=0;
	int virtual damageCalculation(const int[]) = 0;
	int IsOverlapBODY(const int[]);
	int IsOverlapBODY(CPoint);
	int IsOverlapATTACK(const int[]);
	void movestep(int, int);
	static double getPointsLenth(int x1,int y1,int x2,int y2);
	static int getAngle(int x1, int y1, int x2, int y2);
	static double heron(CPoint a,CPoint b,CPoint c);
	void deleteState();
	//void virtual messageReact() = 0;
	//int virtual isOverlap(CPoint,double,int) = 0;
	State(Player*,int);
	State();
	~State();
};
class Standing :public State {
public:
	int virtual damageCalculation(const int[]);
	void virtual stateCalculation(const int[]);
	Standing(Player*, int);
	Standing();
};
class Damaged :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Damaged(Player*, int);
	Damaged();
};
class Moving :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Moving(Player*, int);
	Moving();
};
class Steping :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Steping(Player*, int);
	Steping();
};
class AttackingMID :public Standing {
public:
	void virtual stateCalculation(const int[]);
	AttackingMID(Player*, int);
	AttackingMID();
};
class Defending :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Defending(Player*, int);
	Defending();
};
class Stocked :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Stocked(Player*, int);
	Stocked();
};
class Spiking :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Spiking(Player*, int);
	Spiking();
};
class Lookthrough :public Standing {
public:
	void virtual stateCalculation(const int[]);
	Lookthrough(Player*, int);
	Lookthrough();
};

class Jumping :public State {
public:
	int virtual damageCalculation(const int[]);
	void virtual stateCalculation(const int[]);
	Jumping(Player*, int);
	Jumping();
};
class AttackingUP :public Jumping {
public:
	void virtual stateCalculation(const int[]);
	AttackingUP(Player*, int);
	AttackingUP();
};

class Squating :public State {
public:
	int virtual damageCalculation(const int[]);
	void virtual stateCalculation(const int[]);
	Squating(Player*, int);
	Squating();
};
class AttackingDOWN :public Squating {
public:
	void virtual stateCalculation(const int[]);
	AttackingDOWN(Player*, int);
	AttackingDOWN();
};

class Dead :public State {
public:
	int virtual damageCalculation(const int[]);
	void virtual stateCalculation(const int[]);
	Dead(Player*, int);
	Dead();
};
