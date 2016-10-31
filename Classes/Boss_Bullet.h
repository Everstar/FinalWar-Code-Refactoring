#ifndef __Boss_BULLET_H__
#define __Boss_BULLET_H__

#include "Entity.h"
#include "Boss_Hero.h"
#include "Boss.h"

class Boss;
class Boss_Hero;

class Boss_Bullet : public Entity
{
public:
	Boss_Bullet();
	CREATE_FUNC(Boss_Bullet);
	virtual bool init();
public:
	void Play(int num, int state);
	void SetATK(int atk); //���ù�����
	int GetATK(); //��ȡ������

	bool IsCollideWithHero(Boss_Hero* hero);//�ж��Ƿ���Ӣ����ײ
	bool IsCollideWithBoss(Boss* boss);//�ж��Ƿ���Ӣ����ײ
private:
	int ATK; //������
};





#endif