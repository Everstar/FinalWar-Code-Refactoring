#include "Boss.h"

Boss::Boss()
{
	flag = true;
	time = 0.0f;
	fullHP = 10000;
	currentHP = fullHP;
	atk = 100;
}

bool Boss::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	count = 0;
	this->scheduleUpdate(); //����update����
	return true;
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
	this->skill = filename;

	Vector<SpriteFrame *>loadVector;
	char name[20];

	//���ڲ��ű���ħ����
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

	return;
}

void Boss::Hurt(int atk, int bulletState) //Boss����
{
	if (getSprite() == NULL)
	{
		return;
	}
	this->HurtingAnimation(atk, bulletState);
	currentHP -= atk;
	if (currentHP < 0)
	{
		currentHP = 0;
	}

	return;
}

void Boss::Attack(int num, float scale) //Boss����
{
	Bullet* bullet = nullptr;

	for (int i = 0; i < num; i++)
	{
		//�����ӵ�
		bullet = Bullet::create();
		auto pic = Sprite::createWithSpriteFrameName(this->skill);
		pic->setScale(scale);
		bullet->BindSprite(pic);
		bullet->SetATK(atk);
		//bullet = Factory::GetInstance()->CreateBullet(BulletType::Ball, scale, this->atk);
		if (i & 1)
			bullet->setPosition(this->getPositionX(), this->getPositionY() + count);
		else
			bullet->setPosition(this->getPositionX(), this->getPositionY() - count);

		this->getParent()->addChild(bullet);

		bulletArray.pushBack(bullet);

	}

	return;
}

void Boss::Aim(float delta) //Boss�ӵ��Զ�׷��Ӣ��
{
	if (bulletArray.empty())
	{
		return;
	}

	for (cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin(); bullet != bulletArray.end(); bullet++)
	{
		if ((*bullet)->getPositionX() <= hero->getPositionX())
		{
			continue;
		}
		auto move = MoveTo::create(2.0f, hero->getPosition());
		(*bullet)->runAction(move);
	}
	return;
}

void Boss::update(float delta)
{
	if (!bulletArray.empty())
	{

		count = 0;
		cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin();
		while (bullet != bulletArray.end())
		{
			if (this->GetCurrentHP() >= this->GetFullHP() * 2 / 3) //BossѪ������һ��ʱ�ӵ���ͨ�����ƶ�
			{
				(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);
			}
			//Boss�ӵ���ʼ��Y���ƶ�
			else if ((*bullet)->getPositionX() <= hero->getPositionX() || (this->GetCurrentHP() >= this->GetFullHP() / 2))
			{
				(*bullet)->setPositionX((*bullet)->getPositionX() - 6 - count % 6);

				if (count % 2 == 0)
				{
					(*bullet)->setPositionY((*bullet)->getPositionY() + 4 + count % 5);
				}
				else if (count % 3 == 0)
				{
				}
				else
				{
					(*bullet)->setPositionY((*bullet)->getPositionY() - 4 - count % 5);
				}
			}

			if ((*bullet)->getPositionX() < 0)
			{
				(*bullet)->removeFromParentAndCleanup(true);
				bullet = bulletArray.erase(bullet);
			}
			else if (Entity::IsCollideWith(hero, (*bullet)))
			{
				hero->Hurt((*bullet)->GetATK());
				(*bullet)->removeFromParentAndCleanup(true);
				bullet = bulletArray.erase(bullet);
			}
			else
			{
				bullet++;
			}
			count++;
		}
	}

	if (this->GetCurrentHP() <= this->GetFullHP() / 2 && flag)
	{
		flag = false;
		this->schedule(schedule_selector(Boss::Aim), 2.2f);
	}
	return;
}

void Boss::HurtingAnimation(int atk, int bulletState)
{
	//�˺��������
	LabelTTF* hurt = LabelTTF::create(String::createWithFormat("Hit %d", atk)->getCString(), "arial", 56);
	hurt->setColor(Color3B(255, 165, 0));
	hurt->setPosition(visibleSize.width * 0.8f, 70);

	auto act = Sequence::create(Blink::create(0.8f, 1),
		CallFunc::create(([hurt](void){
		hurt->setVisible(false);
		hurt->removeFromParentAndCleanup(true);
	})), nullptr);

	this->getParent()->addChild(hurt);
	hurt->runAction(act);

	Vector<SpriteFrame *>loadVector;
	char name[16];

	auto sprite = Sprite::create();  //���ڲ��Ŷ����ľ���
	sprite->setPosition(this->getContentSize() / 2);
	sprite->setScale(5.0f);
	this->addChild(sprite);

	//����������Ϻ��ͷ��ڴ�
	auto callfun = CallFunc::create(([sprite](void){
		sprite->setVisible(false);
		sprite->removeFromParentAndCleanup(true);
	}));

	switch (bulletState)
	{
	case 1:
		for (int i = 1; i <= 8; i++)
		{
			sprintf(name, "red (%d).png", i);
			loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}
		break;
	case 2:
		for (int i = 1; i <= 4; i++)
		{
			sprintf(name, "blue (%d).png", i);
			loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}
		break;
	case 4:
		for (int i = 1; i <= 5; i++)
		{
			sprintf(name, "green (%d).png", i);
			loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}
		sprite->setScale(10.0f); //��Ϊͼ���С�Ĳ�һ�����ٴε�����С
		break;
	default:
		return;
	}
	sprite->runAction(Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 24.0f)),
		callfun, nullptr));
}