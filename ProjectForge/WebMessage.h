#pragma once
#include "pch.h"
class WebMessage
{
public:
	CPoint picture;
	int damage;
	CPoint pos;
	double toward;
	int lenth;

	int id;//stateID

	int health;
	int body;
	WebMessage(CPoint, int, CPoint, double, int, int, int, int);
};

