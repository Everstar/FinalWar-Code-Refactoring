#include "Entity.h"

void Entity::BindSprite(Sprite* sprite)
{
	pSprite = sprite;
	this->addChild(pSprite);

	Size spSize = pSprite->getContentSize();
	pSprite->setPosition(Point(spSize.width / 2, spSize.height / 2));
	this->setContentSize(spSize);

	return;
}

Sprite* Entity::getSprite()
{
	return pSprite;
}

bool Entity::IsCollideWith(Entity* one, Entity* other)
{
	Rect entityRect = one->getBoundingBox();

	return entityRect.containsPoint(other->getPosition());
}