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
	void SetPower(int atk); //����Ӣ�۹�����
	void SetMonsterArray(ilist<Monster* >* Array); //���С������

	void Attack();
	void Hurt(int atk);
	void Move(short x, short y);

	void SetType(int num, int state, FigureType); //�����ӵ�����Դ�ļ� ����֡�� �ӵ�����
	void HurtingAnimation(int atk); //���˶���

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

	ilist<Bullet* > bulletArray; //�ӵ�����
	ilist<Monster* >* monsterArray; //С������
};





#endif