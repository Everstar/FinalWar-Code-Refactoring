#ifndef __INSANEBOSS_H__
#define __INSANEBOSS_H__

#include "BossState.h"

class InsaneBoss : public BossState
{
public:
	InsaneBoss();
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