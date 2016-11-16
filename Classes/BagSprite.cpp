#include "BagSprite.h"

BagSprite::BagSprite()
{

}

bool BagSprite::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BAGSPRITE));
	this->setScale(0.18f);
	this->SetATK(20);
	this->SetHP(100);
	return true;
}