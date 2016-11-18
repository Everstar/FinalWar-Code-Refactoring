#ifndef __BANANA_H__
#define __BANANA_H__

#include "Monster.h"
USING_NS_CC;

class Banana :public Monster
{
private:
	Banana();
	bool init();
public:
	static Banana* Instance;

	Monster* clone();
};



#endif