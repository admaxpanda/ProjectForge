#include "WebMessage.h"
WebMessage::WebMessage(
	CPoint picture,
	int damage,
	CPoint pos,
	double toward,
	int lenth,
	int id,
	int helth,
	int body)
{
	this->picture = picture;
	this->damage = damage;
	this->pos = pos;
	this->toward = toward;
	this->lenth = lenth;
	this->id = id;
	this->health = health;
	this->body = body;
}