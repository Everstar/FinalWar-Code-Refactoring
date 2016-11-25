#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include "Observer.h"
#include <vector>

class Observer;

class Observable
{
public:
	Observable();
	~Observable();
	void Attach(Observer*);
	void Detach(Observer*);
	void Notify();

	float ObservingData;
protected:
	std::vector<Observer*>* obs;
};

#endif