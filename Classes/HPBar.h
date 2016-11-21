#ifndef __HPBAR_H__
#define __HPBAR_H__

#include "Observer.h"
#include "Parameter.h"
#include "cocos2d.h"
USING_NS_CC;

class HPBar : public Sprite, public Observer
{
public:
	HPBar();
	HPBar(FigureType);
	static HPBar* CreateWithInit(FigureType);
	CREATE_FUNC(HPBar);
	bool init();
	FigureType GetType();
	void SetType(FigureType);
	void Update(Observable*);
private:
	FigureType _type;
	ProgressTimer* hpBarblood;
};


#endif