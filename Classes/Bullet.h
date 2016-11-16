#ifndef __Bullet_H__
#define __Bullet_H__

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();
public:
	void Play(int num, int state);
	void SetATK(int atk); //���ù�����
	int GetATK(); //��ȡ������
private:
	int ATK; //������
};





#endif