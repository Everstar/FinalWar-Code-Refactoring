#include "Player.h"

Player::~Player()
{
	bulletArray.clear();
}

bool Player::init()
{
	fullHP = 3000;
	currentHP = fullHP;
	power = 50;
	pBoss = nullptr;
	moveAction = nullptr;
	this->scheduleUpdate();
	return true;
}

void Player::BindBoss(Boss* boss)
{
	this->pBoss = boss;
}

int Player::GetCurrentHP()
{
	return currentHP;
}

int Player::GetFullHP()
{
	return fullHP;
}

void Player::SetCurrentHP(int hp)
{
	this->currentHP = hp;
}

void Player::SetPower(int atk)
{
	this->power = atk;
}

void Player::Move(short x, short y)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (this->getPositionY() >= visibleSize.height && y > 0)
	{
		return;
	}
	else if (this->getPositionY() <= 0 && y < 0)
	{
		return;
	}

	moveAction = MoveBy::create(0.3f, Vec2(15 * x, y * 15));
	this->runAction(RepeatForever::create(moveAction));

	return;
}

void Player::SetBullet(int num, int state)
{
	plistNum = num;
	bulletState = state;
	return;
}

void Player::SetMonsterArray(Vector<Monster* >* Array)
{
	this->monsterArray = Array;
}

void Player::Attack()
{
	Bullet *bullet = Factory::GetInstance()->CreateBullet(BulletType::Light, this->power);
	bullet->setPosition(this->getParent()->getPosition());
	this->getParent()->getParent()->addChild(bullet);
	bulletArray.pushBack(bullet);

	bullet->Play(plistNum, bulletState);

	return;
}

void Player::Hurt(int atk)
{
	if (getSprite() == nullptr) return;
	this->HurtingAnimation(atk);
	currentHP -= atk;
	if (currentHP < 0)
	{
		currentHP = 0;
	}
	if (currentHP > fullHP)
	{
		currentHP = fullHP;
	}

	return;
}

void Player::update(float delta)
{
	if (bulletArray.empty())
	{
		return;
	}

	//����ӵ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin();
	bool bulletLife = false;//�ӵ��Ƿ���
	while (bullet != bulletArray.end())
	{
		if ((*bullet) == nullptr) continue;

		bulletLife = true;
		(*bullet)->setPositionX((*bullet)->getPositionX() + 8);

		for (int i = 0; i < monsterArray->size(); i++)
		{
			if ((*bullet)->getBoundingBox().intersectsRect(monsterArray->at(i)->getBoundingBox()))
			{
				monsterArray->at(i)->LoseLife(power);
				(*bullet)->removeFromParentAndCleanup(true);
				bullet = bulletArray.erase(bullet);
				bulletLife = false;
				break;
			}
		}

		if (!bulletLife) return;
		if ((*bullet)->getPositionX() > visibleSize.width)
		{
			(*bullet)->removeFromParentAndCleanup(true);
			bullet = bulletArray.erase(bullet);
		}
		else if (Entity::IsCollideWith(pBoss, (*bullet)))
		{
			pBoss->Hurt((*bullet)->GetATK(), bulletState);
			(*bullet)->removeFromParentAndCleanup(true);
			bullet = bulletArray.erase(bullet);
		}
		else
			bullet++;
	}
	return;
}

void Player::HurtingAnimation(int atk)
{
	LabelTTF* hurt = Factory::GetInstance()->CreateBlinkNotification(FigureType::Boat, atk);
	this->getParent()->addChild(hurt);

	auto sprite = Sprite::create();
	sprite->setPosition(this->getContentSize() / 2);
	this->addChild(sprite); //���ڲ��Ŷ����ľ���

	Factory::GetInstance()->CreateHurtingAnimation(FigureType::Boat, sprite);
}