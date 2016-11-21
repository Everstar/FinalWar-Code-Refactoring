#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "Observable.h"

class Observable;

class Observer
{
public:
	virtual void Update(Observable*) = 0;
};


#endif