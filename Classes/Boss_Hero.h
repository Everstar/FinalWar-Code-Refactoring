#ifndef __Boss_Hero_H__
#define __Boss_Hero_H__

#include "Entity.h"
#include "Boss.h"
#include "Boss_Bullet.h"
#include "Boss_Monster.h"
USING_NS_CC;

class Boss_Monster;

class Boss_Hero :public Entity
{
public:
	Boss_Hero();
	~Boss_Hero();
	virtual bool init();
	CREATE_FUNC(Boss_Hero);

	void BindBoss(Boss* boss);
	int GetCurrentHP();
	int GetFullHP();
	void SetCurrentHP(int hp);
	void SetPower(int atk); //����Ӣ�۹�����
	void SetMonsterArray(Vector<Boss_Monster* >* Array); //���С������

	void Attack(float scale);
	void Hurt(int ATK);
	void Move(short x, short y);

	void SetBullet(int num, int state); //�����ӵ�����Դ�ļ� ����֡�� �ӵ�����
	void HurtingAnimation(int atk); //���˶���

	void update(float delta);
private:
	int fullHP;
	int currentHP;
	int power;

	Boss* pBoss;
	MoveBy* moveAction;
	int plistNum;
	int bulletState;
	bool bulletLife; //�ӵ��Ƿ���

	Vector<Boss_Bullet* > bulletArray; //�ӵ�����
	Vector<Boss_Monster* >* monsterArray; //С������
};





#endif