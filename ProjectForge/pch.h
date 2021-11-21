#pragma once
#include <afxwin.h>
#include "resource.h"
#include <map>
#include <queue>
#include <thread>
#include <winsock2.h>
#include <afxdialogex.h>
#include <string>
#include <afxpriv.h>
#include <cmath>

#define PICTUREX 0
#define PICTUREY 1
#define DAMAGE 2
#define POSX 3
#define POSY 4
#define TOWARD 5
#define LENTH 6
#define STATEID 7
#define HEALTH 8
#define BODY 9
#define RANGE 10
using std::string;
using std::map;
using std::queue;

#define STEPCD 60
#define TICK 17
#define MATHPI 3.14159265458

#define MESSAGE 0x7
#define MESSAGEMOVE 0x1
#define MESSAGEATTACK 0x2
#define MESSAGEDEFEND 0x3
#define MESSAGESPIKE 0x4
#define MESSAGEJUMP 0x5
#define MESSAGESTEP 0x6
#define MESSAGESQUAT 0x7

#define TICK1 17

#define CHARACTERWIDTH 128
#define r2a(A) A/MATHPI*180
#define a2r(A) A/180*MATHPI