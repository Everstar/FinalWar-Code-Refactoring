#include "BoringBoss.h"
#include "ExcitedBoss.h"

BoringBoss::BoringBoss()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	updown = true;

	_state = BossStateType::Boring;
}

void BoringBoss::init()
{
	_context->schedule(schedule_selector(Boss::ReleaseBullets), 1.2f);
}

void BoringBoss::DetectState()
{
	if (_context->GetCurrentHP() < _context->GetFullHP() * 2 / 3)
		_context->SetBossState(new ExcitedBoss());
}

void BoringBoss::Move()
{
	if (updown == true) //设置Boss上下移动
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

void BoringBoss::Attack()
{
	byte count = 0;
	if (!_context->bulletArray.empty())
	{
		cocos2d::Vector<Bullet*>::iterator bullet = _context->bulletArray.begin();
		while (bullet != _context->bulletArray.end())
		{
			(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);

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