#ifndef __Boss_Monster_H__
#define __Boss_Monster_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Boss_Hero.h"
USING_NS_CC;

class Boss_Hero;

class Boss_Monster :public Entity
{
public:
	Boss_Monster();
	~Boss_Monster();
	CREATE_FUNC(Boss_Monster);
	virtual bool init();
public:
	void SetATK(int atk);
	int GetATK();
	void SetHP(int HP);
	int GetHP();
	void LoseLife(int atk);
	bool IsCollideWithHero(Boss_Hero* phero);//�ж��Ƿ����ӵ���ײ
private:
	int atk; //������
	int hp; //����
};



#endif