#ifndef __EXCITEDBOSS_H__
#define __EXCITEDBOSS_H__

#include "BossState.h"

class ExcitedBoss : public BossState
{
public:
	ExcitedBoss();
	void init();
	void DetectState();
	void Move();
	void Attack();
private:
	Size visibleSize;
	bool updown;
	bool leftright;
};

#endif