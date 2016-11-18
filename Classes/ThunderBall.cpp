#include "ThunderBall.h"

ThunderBall* ThunderBall::Instance = new ThunderBall();

ThunderBall::ThunderBall()
{
}

bool ThunderBall::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_THUNDERBALL));
	this->setScale(0.18f);
	this->SetATK(80);
	this->SetHP(400);
	this->type = MonsterType::THUNDERBALL;
	return true;
}

Monster* ThunderBall::clone()
{
	ThunderBall* self = new ThunderBall();
	self->init();
	return self;
}