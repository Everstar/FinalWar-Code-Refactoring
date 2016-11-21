#ifndef __BOSS_H__
#define __BOSS_H__

#include "BossState.h"
#include "Bullet.h"
#include "Factory.h"
#include "Observable.h"
USING_NS_CC;

class Bullet;
class Player;
class BossState;

class Boss : public Entity, public Observable
{
public:
	bool init();
	CREATE_FUNC(Boss);
public:
	~Boss();
	BossState* GetBossState();

	void BindHero(Player* phero);

	int GetCurrentHP();
	int GetFullHP();
	void SetSkill(const std::string &filename);

	void Hurt(int atk, int bulletState = 0);

	void Attack(int num);

	void HurtingAnimation(int atk, int bulletState);

	void Aim(float delta);
	void ReleaseBullets(float delta);
	void update(float delta);

	void SetBossState(BossState*);
public:
	Vector<Bullet* > bulletArray;
	Player* hero;
private:
	BossState* _bossState;
	bool flag;

	int currentHP;
	int fullHP;
	int atk;

	int count; //×Óµ¯¼ÆÊý
};





#endif