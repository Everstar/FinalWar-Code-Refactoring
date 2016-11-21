#ifndef __BOSSSTATE_H__
#define __BOSSSTATE_H__

#include "Boss.h"
#include "Parameter.h"

class Boss;

class BossState
{
protected:
	Boss* _context;
public:
	BossStateType _state;

	void SetContext(Boss* context);
	virtual void init() = 0;
	virtual void DetectState() = 0;
	virtual void Move() = 0;
	virtual void Attack() = 0;
};

#endif