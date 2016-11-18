#include "ExcitedBoss.h"
#include "InsaneBoss.h"

ExcitedBoss::ExcitedBoss()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	updown = true;
	leftright = true;
}

void ExcitedBoss::DetectState()
{
	if (_context->GetCurrentHP() < _context->GetFullHP() / 2)
		_context->SetBossState(new InsaneBoss());
}

void ExcitedBoss::Move()
{
	if (leftright) //设置Boss左右移动
	{
		if (_context->getPositionX() <= visibleSize.width * 0.88f)
			_context->setPositionX(_context->getPositionX() + 3);
		else
			leftright = false;
	}
	else
	{
		if (_context->getPositionX() >= visibleSize.width * 0.66f)
			_context->setPositionX(_context->getPositionX() - 3);
		else
			leftright = true;
	}

	if (updown) //设置Boss上下移动
	{
		if (_context->getPositionY() <= visibleSize.height - 100)
			_context->setPositionY(_context->getPositionY() + 3 + (int)time % 8);
		else
			updown = false;
	}
	else
	{
		if (_context->getPositionY() >= 0)
			_context->setPositionY(_context->getPositionY() - 3 - (int)time % 8);
		else
			updown = true;
	}
}

void ExcitedBoss::Attack()
{
	byte count = 0;
	if (!_context->bulletArray.empty())
	{
		cocos2d::Vector<Bullet*>::iterator bullet = _context->bulletArray.begin();
		while (bullet != _context->bulletArray.end())
		{

			(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);

			if (count % 2 == 0)
				(*bullet)->setPositionY((*bullet)->getPositionY() + 4 + count % 5);
			else if (count % 3 != 0)
				(*bullet)->setPositionY((*bullet)->getPositionY() - 4 - count % 5);

			if ((*bullet)->getPositionX() < 0)
			{
				(*bullet)->removeFromParentAndCleanup(true);
				bullet = _context->bulletArray.erase(bullet);
			}
			else if (Entity::IsCollideWith(_context->hero, (*bullet)))
			{
				_context->hero->Hurt((*bullet)->GetATK());
				(*bullet)->removeFromParentAndCleanup(true);
				bullet = _context->bulletArray.erase(bullet);
			}
			else
				bullet++;
			count++;
		}
	}
}