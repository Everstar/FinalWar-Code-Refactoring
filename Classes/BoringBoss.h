#ifndef __BORINGBOSS_H__
#define __BORINGBOSS_H__

#include "BossState.h"

class BoringBoss : public BossState
{
public:
	BoringBoss();
	void init();
	void DetectState();
	void Move();
	void Attack();
private:
	Size visibleSize;
	bool updown; //еп╤оBossиообрф╤╞
};

#endif