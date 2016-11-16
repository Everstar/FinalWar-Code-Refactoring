#ifndef __BOSS_H__
#define __BOSS_H__

#include "Bullet.h"
#include "Factory.h"
USING_NS_CC;

class Bullet;
class Player;

class Boss : public Entity
{
public:
	virtual bool init();
	CREATE_FUNC(Boss);
public:
	Boss();

	void BindHero(Player* phero);

	int GetCurrentHP();
	int GetFullHP();
	void SetSkill(const std::string &filename);

	void Hurt(int atk, int bulletState = 0);

	void Attack(int num, float scale);

	void HurtingAnimation(int atk, int bulletState);

	void Aim(float delta);
	void update(float delta);
private:
	Size visibleSize;
	float time;
	bool flag;

	Player* hero;

	std::string monster;
	std::string skill;
	int currentHP;
	int fullHP;
	int atk;

	int count; //×Óµ¯¼ÆÊý
	Vector<Bullet* > bulletArray;
};





#endif