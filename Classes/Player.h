#ifndef __Player_H__
#define __Player_H__

#include "Factory.h"
#include "Parameter.h"
#include "Observable.h"
#include "ilist.h"
USING_NS_CC;

class Monster;
class Boss;

class Player :public Entity, public Observable
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
	void SetMonsterArray(ilist<Monster* >* Array); //获得小怪数组

	void Attack();
	void Hurt(int atk);
	void Move(short x, short y);

	void SetType(int num, int state, FigureType); //设置子弹动画源文件 动画帧数 子弹种类
	void HurtingAnimation(int atk); //受伤动画

	void update(float delta);
private:
	FigureType _type;

	int fullHP;
	int currentHP;
	int power;

	Boss* pBoss;
	MoveBy* moveAction;
	int plistNum;
	int bulletState;

	ilist<Bullet* > bulletArray; //子弹数组
	ilist<Monster* >* monsterArray; //小怪数组
};





#endif