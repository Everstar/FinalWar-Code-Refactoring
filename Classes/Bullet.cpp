#include "Bullet.h"

Bullet::Bullet()
{
	ATK = 100;
}

bool Bullet::init()
{
	return true;
}

void Bullet::SetATK(int atk)
{
	this->ATK = atk;
	return;
}

int Bullet::GetATK()
{
	return ATK;
}

void Bullet::Play(int num ,int state)
{
	Vector<SpriteFrame *>loadVector;
	char name[14];

	for (int i = 1; i <= num; i++)
	{
		sprintf(name, "bullet_%d%d.png", state, i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	this->getSprite()->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 24.0f))));

	return;
}