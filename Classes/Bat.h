#ifndef __BAT_H__
#define __BAT_H__

#include "Monster.h"
USING_NS_CC;

class Bat :public Monster
{
private:
	Bat();
	bool init();
public:
	static Bat* Instance;

	Monster* clone();
};



#endif