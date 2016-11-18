#include "Monster.h"
#include "Factory.h"
#include "BagSprite.h"
#include "Banana.h"
#include "Bat.h"
#include "ThunderBall.h"
#include "Donggua.h"

Monster** Monster::prototypes = new Monster*[5];
byte Monster::prototypeCount = 0;

Monster::Monster()
{
	init();
}

bool Monster::init()
{
	atk = 100;
	hp = 100;
	type = MonsterType::Abstract;
	return true;
}

void Monster::addPrototype(Monster* monster)
{
	if (prototypeCount > 4) return;
	Monster::prototypes[prototypeCount++] = monster;
}

Monster* Monster::findAndClone(MonsterType type)
{
	return prototypes[type]->clone();
}

Monster* Monster::clone()
{
	return new Monster();
}

MonsterType Monster::GetMonsterType()
{
	return type;
}

void Monster::addAllPrototypes()
{
	//添加小怪原型
	Monster::addPrototype(BagSprite::Instance->clone());
	Monster::addPrototype(Banana::Instance->clone());
	Monster::addPrototype(Bat::Instance->clone());
	Monster::addPrototype(ThunderBall::Instance->clone());
	Monster::addPrototype(Donggua::Instance->clone());
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

	//伤害输出反馈
	LabelTTF* label = Factory::GetInstance()->CreateBlinkNotification(FigureType::MONSTER, atk);
	label->setPosition(this->getPositionX() + 50, this->getPositionY());

	this->getParent()->addChild(label);
}

