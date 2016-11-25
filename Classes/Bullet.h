#ifndef __Bullet_H__
#define __Bullet_H__

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	CREATE_FUNC(Bullet);
	bool init();
public:
	void Play(int num, int state);
	void SetATK(int atk); //设置攻击力
	int GetATK(); //获取攻击力
private:
	int ATK; //攻击力
};





#endif