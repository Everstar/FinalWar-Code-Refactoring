#ifndef __DONGGUA_H__
#define __DONGGUA_H__

#include "Monster.h"
USING_NS_CC;

class Donggua :public Monster
{
private:
	Donggua();
	bool init();
public:
	static Donggua* Instance;

	Monster* clone();
};



#endif