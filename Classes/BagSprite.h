#ifndef __BAGSPRITE_H__
#define __BAGSPRITE_H__

#include "Monster.h"

USING_NS_CC;

class BagSprite :public Monster
{
public:
	BagSprite();
	CREATE_FUNC(BagSprite);
	virtual bool init();
};



#endif