#ifndef __DONGGUA_H__
#define __DONGGUA_H__

#include "Monster.h"
USING_NS_CC;

class Donggua :public Monster
{
public:
	Donggua();
	CREATE_FUNC(Donggua);
	virtual bool init();
};



#endif