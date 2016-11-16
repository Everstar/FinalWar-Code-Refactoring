#ifndef __Monster_H__
#define __Monster_H__

#include "Entity.h"
#include "Parameter.h"
USING_NS_CC;

class Player;

class Monster :public Entity
{
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();
public:
	Monster* prototypes;

	void SetATK(int atk);
	int GetATK();
	void SetHP(int HP);
	int GetHP();
	void LoseLife(int atk);
private:
	int atk; //¹¥»÷Á¦
	int hp; //ÉúÃü
};



#endif