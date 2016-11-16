#ifndef __FACTORY_H__
#define __FACTORY_H__

#include "Boss.h"
#include "Player.h"
#include "Monster.h"
#include "Parameter.h"
#include "BagSprite.h"
USING_NS_CC;

class Boss;
class Player;
class Monster;

enum BulletType { Light, Ball };

enum MonsterType { BagSprite, Banana, Bat, ThunderBall, Donggua };

enum PlayerType { Forset, Star, Dragon, Boat };

class Factory
{
private:
	static Factory* instance;
	Factory();
	~Factory();

public:
	static Factory* GetInstance(){
		if (instance == nullptr) 
			instance = new Factory();
		return instance;
	}

	Player* CreatePlayer(PlayerType type);
	Boss* CreateBoss();
	Monster* CreateMonster(MonsterType type, float scale, int atk, int life);
	Bullet* CreateBullet(BulletType type, float scale, int atk);
};

#endif