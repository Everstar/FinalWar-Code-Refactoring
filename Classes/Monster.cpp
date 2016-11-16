#include "Monster.h"

Monster::Monster()
{
	atk = 50;
	hp = 100;
}

Monster::~Monster()
{
}

bool Monster::init()
{
	return true;
}

void Monster::SetATK(int atk)
{
	this->atk = atk;
}

int Monster::GetATK()
{
	return this->atk;
}

void Monster::SetHP(int HP)
{
	this->hp = HP;
	return;
}

int Monster::GetHP()
{
	return this->hp;
}

void Monster::LoseLife(int atk)
{
	this->hp -= atk;
	if (hp < 0)
	{
		hp = 0;
	}

	//ÉËº¦Êä³ö·´À¡
	LabelTTF* hurt = LabelTTF::create(String::createWithFormat("Hit %d", atk)->getCString(), "arial", 36);
	hurt->setColor(Color3B(255, 0, 0));
	hurt->setPosition(this->getPositionX() + 50, this->getPositionY());

	auto act = Sequence::create(Blink::create(0.8f, 1),
		CallFunc::create(([hurt](void){
		hurt->setVisible(false);
		hurt->removeFromParentAndCleanup(true);
	})), nullptr);

	this->getParent()->addChild(hurt);
	hurt->runAction(act);

	return;
}

