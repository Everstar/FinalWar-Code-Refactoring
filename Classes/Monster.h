#ifndef __Monster_H__
#define __Monster_H__

#include "Entity.h"
#include "Parameter.h"
USING_NS_CC;

class Monster :public Entity
{
public:
	Monster();
	CREATE_FUNC(Monster);
	bool init();

protected:
	virtual Monster* clone();

	int atk; //������
	int hp; //����
	MonsterType type;//С������
public:
	static void addAllPrototypes();
	static void addPrototype(Monster*);
	static Monster* findAndClone(MonsterType);

private:
	static byte prototypeCount;
	static Monster** prototypes;

public:
	void SetATK(int atk);
	int GetATK();
	void SetHP(int HP);
	int GetHP();
	void LoseLife(int atk);
	MonsterType GetMonsterType();
};



#endif