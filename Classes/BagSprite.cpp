#include "BagSprite.h"

BagSprite* BagSprite::Instance = new BagSprite();

BagSprite::BagSprite()
{
}

bool BagSprite::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BAGSPRITE));
	this->setScale(0.18f);
	this->atk = 20;
	this->hp = 100;
	this->type = MonsterType::BAGSPRITE;
	return true;
}

Monster* BagSprite::clone()
{
	BagSprite* self = new BagSprite();
	self->init();
	return self;
}