#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
USING_NS_CC;


class Entity :public Node
{
public:
	void BindSprite(Sprite* sprite);
	Sprite* getSprite();
	bool static IsCollideWith(Entity*, Entity*);
private:
	Sprite* pSprite;
};


#endif