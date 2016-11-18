#ifndef __THUNDERBALL_H__
#define __THUNDERBALL_H__

#include "Monster.h"
USING_NS_CC;

class ThunderBall :public Monster
{
private:
	ThunderBall();
	bool init();
public:
	static ThunderBall* Instance;

	Monster* clone();
};



#endif