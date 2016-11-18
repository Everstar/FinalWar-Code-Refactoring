#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "Boss.h"
#include "Player.h"
#include "Monster.h"
#include "Parameter.h"
USING_NS_CC;

class Boss;
class Player;
class Monster;

class Factory
{
private:
	static Factory* instance;
	Factory();
	~Factory();

	Monster* monsterPrototype;

public:
	static Factory* GetInstance(){
		if (instance == nullptr) 
			instance = new Factory();
		return instance;
	}

	Player* CreatePlayer(FigureType);
	Boss* CreateBoss();
	Monster* CreateMonster(MonsterType);
	Bullet* CreateBullet(BulletType, int);

	void CreateHurtingAnimation(FigureType, Sprite*&, int = 0);
	LabelTTF* CreateBlinkNotification(FigureType, int);
};

#endif