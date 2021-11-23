#pragma once
#include "pch.h"
class ControlMessage
{
public:
	int ID;
	int toward;
	ControlMessage(int ID,double toward);
};

