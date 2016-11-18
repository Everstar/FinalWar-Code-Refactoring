#ifndef __BAGSPRITE_H__
#define __BAGSPRITE_H__

#include "Monster.h"
USING_NS_CC;

class BagSprite :public Monster
{
private:
	BagSprite();
	bool init();
public:
	static BagSprite* Instance;

	Monster* clone();
};



#endif