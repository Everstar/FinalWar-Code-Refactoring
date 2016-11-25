#include "Observable.h"

Observable::Observable()
{
	obs = new std::vector<Observer*>();
	ObservingData = 0.0f;
}

Observable::~Observable()
{
	obs->clear();
}

void Observable::Attach(Observer* ob)
{
	obs->push_back(ob);
}

void Observable::Detach(Observer* ob)
{
	std::vector<Observer*>::iterator it = obs->begin();
	while (it != obs->end())
	{
		if ((*it) == ob)
			obs->erase(it);
		else
			it++;
	}
}

void Observable::Notify()
{
	std::vector<Observer*>::iterator it = obs->begin();
	while (it != obs->end())
		(*it++)->Update(this);
}