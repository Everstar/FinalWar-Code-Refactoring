#include "Bat.h"

Bat* Bat::Instance = new Bat();

Bat::Bat()
{
}

bool Bat::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BAT));
	this->setScale(0.18f);
	this->SetATK(60);
	this->SetHP(300);
	this->type = MonsterType::BAT;
	return true;
}

Monster* Bat::clone()
{
	Bat* self = new Bat();
	self->init();
	return self;
}