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
#define TICK 70
#define MATHPI 3.14159265458
#define CHARACTERWIDTH 128

#define MESSAGE			0xF
#define MESSAGEMOVE		0x1
#define MESSAGEATTACK	0x2
#define MESSAGEDEFEND	0x3
#define MESSAGESPIKE	0x4
#define MESSAGEJUMP		0x5
#define MESSAGESTEP		0x6
#define MESSAGESQUAT	0x7

#define TICK1 42


#define r2a(A) (A)/MATHPI*180
#define a2r(A) (A)*MATHPI/180

#define ATTACKSTATEANY	0x0FFFF
#define ATTACKSTATE		0xF0000
#define ATTACKING		0x20000
#define DISATTACKING	0x10000

#define ATTACKTYPEANY	0xF0FFF
#define ATTACKTYPE		0x0F000
#define ATTACKMID		0x01000
#define ATTACKUP		0x02000
#define ATTACKDOWN		0x03000
#define ATTACKSPIKE		0x04000

#define DAMAGETYPEANY	0xFF0FF
#define DAMAGETYPE		0x00F00
#define DAMAGESTANDING	0x00100
#define DAMAGEJUMPING	0x00200
#define DAMAGESQUATING	0x00300
#define DAMAGEDEAD		0x00400

#define METHODANY		0xFFF0F
#define METHOD			0x000F0
#define METHODSTEP		0x00010
#define METHODDEFENDING	0x00020
#define METHODMOVING	0x00030
#define METHODDAMAGE	0x00040
#define METHODSTOCKING	0x00050
#define METHODDEAD		0x00060
#define METHODLOOKTHOUGH 0x00070

#define STAGEANY		0xFFFF0
#define STAGE			0x0000F
#define STAGEPREING		0x00001
#define STAGEACTING		0x00002
#define STAGEDAMAGING	0x00003
#define STAGEENDING		0x00004
#define STAGEREBOUNDING	0x00005
#define STAGEREBOUNDING_S 0x00006
