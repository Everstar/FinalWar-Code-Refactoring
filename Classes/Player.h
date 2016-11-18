#ifndef __Player_H__
#define __Player_H__

#include "Factory.h"
USING_NS_CC;

class Monster;
class Boss;

class Player :public Entity
{
public:
	~Player();
	virtual bool init();
	CREATE_FUNC(Player);

	void BindBoss(Boss* boss);
	int GetCurrentHP();
	int GetFullHP();
	void SetCurrentHP(int hp);
	void SetPower(int atk); //设置英雄攻击力
	void SetMonsterArray(Vector<Monster* >* Array); //获得小怪数组

	void Attack();
	void Hurt(int atk);
	void Move(short x, short y);

	void SetBullet(int num, int state); //设置子弹动画源文件 动画帧数 子弹种类
	void HurtingAnimation(int atk); //受伤动画

	void update(float delta);
private:
	int fullHP;
	int currentHP;
	int power;

	Boss* pBoss;
	MoveBy* moveAction;
	int plistNum;
	int bulletState;

	Vector<Bullet* > bulletArray; //子弹数组
	Vector<Monster* >* monsterArray; //小怪数组
};





#endif