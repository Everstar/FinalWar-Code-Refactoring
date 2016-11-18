#include "Boss.h"
#include "BoringBoss.h"

Boss::~Boss()
{
	bulletArray.clear();
}

bool Boss::init()
{
	flag = true;
	fullHP = 10000;
	currentHP = fullHP;
	atk = 100;

	count = 0;
	this->SetBossState(new BoringBoss());
	this->scheduleUpdate(); //开启update函数
	return true;
}

BossState* Boss::GetBossState()
{
	return this->_bossState;
}

void Boss::SetBossState(BossState* state)
{
	this->_bossState = state;
	this->_bossState->SetContext(this);
}

void Boss::BindHero(Player* phero)
{
	this->hero = phero;
}

int Boss::GetCurrentHP()
{
	return currentHP;
}

int Boss::GetFullHP()
{
	return fullHP;
}

void Boss::SetSkill(const std::string &filename)
{
	Vector<SpriteFrame *>loadVector;
	char name[20];

	//用于播放背景魔法阵
	auto sprite = Sprite::create();
	sprite->setPosition(this->getContentSize() / 2);
	sprite->setScale(3.0f);
	this->addChild(sprite, -1);

	for (int i = 1; i <= 12; i++)
	{
		sprintf(name, "magiccircle_%d.png", i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	sprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 12.0f))));
}

void Boss::Hurt(int atk, int bulletState) //Boss受伤
{
	if (getSprite() == nullptr) return;

	this->HurtingAnimation(atk, bulletState);
	currentHP -= atk;
	if (currentHP < 0)
	{
		currentHP = 0;
	}

	return;
}

void Boss::Attack(int num) //Boss攻击
{
	Bullet* bullet = nullptr;

	for (int i = 0; i < num; i++)
	{
		//创建子弹
		bullet = Factory::GetInstance()->CreateBullet(BulletType::Ball, this->atk);
		if (i & 1)
			bullet->setPosition(this->getPositionX(), this->getPositionY() + count);
		else
			bullet->setPosition(this->getPositionX(), this->getPositionY() - count);

		this->getParent()->addChild(bullet);

		bulletArray.pushBack(bullet);

	}
}

void Boss::Aim(float delta) //Boss子弹自动追踪英雄
{
	if (bulletArray.empty()) return;

	for (cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin(); bullet != bulletArray.end(); bullet++)
	{
		if ((*bullet)->getPositionX() <= hero->getPositionX())
			continue;

		auto move = MoveTo::create(2.0f, hero->getPosition());
		(*bullet)->runAction(move);
	}
}

void Boss::update(float delta)
{
	this->_bossState->DetectState();
	this->_bossState->Move();
	this->_bossState->Attack();

	//if (!bulletArray.empty())
	//{
	//	count = 0;
	//	cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin();
	//	while (bullet != bulletArray.end())
	//	{
	//		if (this->GetCurrentHP() >= this->GetFullHP() * 2 / 3) //Boss血量大于一半时子弹普通向右移动
	//		{
	//			(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);
	//		}
	//		//Boss子弹开始在Y轴移动
	//		else if ((*bullet)->getPositionX() <= hero->getPositionX() || (this->GetCurrentHP() >= this->GetFullHP() / 2))
	//		{
	//			(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);

	//			if (count % 2 == 0)
	//			{
	//				(*bullet)->setPositionY((*bullet)->getPositionY() + 4 + count % 5);
	//			}
	//			else if (count % 3 != 0)
	//			{
	//				(*bullet)->setPositionY((*bullet)->getPositionY() - 4 - count % 5);
	//			}
	//		}

	//		if ((*bullet)->getPositionX() < 0)
	//		{
	//			(*bullet)->removeFromParentAndCleanup(true);
	//			bullet = bulletArray.erase(bullet);
	//		}
	//		else if (Entity::IsCollideWith(hero, (*bullet)))
	//		{
	//			hero->Hurt((*bullet)->GetATK());
	//			(*bullet)->removeFromParentAndCleanup(true);
	//			bullet = bulletArray.erase(bullet);
	//		}
	//		else
	//			bullet++;
	//		count++;
	//	}
	//}

	//if (this->GetCurrentHP() <= this->GetFullHP() / 2 && flag)
	//{
	//	flag = false;
	//	this->schedule(schedule_selector(Boss::Aim), 2.2f);
	//}
}

void Boss::HurtingAnimation(int atk, int bulletState)
{
	//伤害输出反馈
	LabelTTF* hurt = Factory::GetInstance()->CreateBlinkNotification(FigureType::BOSS, atk);
	this->getParent()->addChild(hurt);

	auto sprite = Sprite::create();  //用于播放动画的精灵
	sprite->setPosition(this->getContentSize() / 2);
	this->addChild(sprite);

	Factory::GetInstance()->CreateHurtingAnimation(FigureType::BOSS, sprite, bulletState);
}