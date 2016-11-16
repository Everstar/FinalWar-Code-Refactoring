#include "Player.h"

Player::Player()
{
	fullHP = 3000;
	currentHP = fullHP;
	power = 50;
	pBoss = nullptr;
	moveAction = nullptr;
	bulletLife = false;
}

Player::~Player()
{
}

bool Player::init()
{
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

void Player::Attack(float scale)
{
	Bullet *bullet = Factory::GetInstance()->CreateBullet(BulletType::Light, scale, this->power);
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

	//检测子弹
	Size visibleSize = Director::getInstance()->getVisibleSize();
	cocos2d::Vector<Bullet*>::iterator bullet = bulletArray.begin();
	while (bullet != bulletArray.end())
	{
		if ((*bullet) == nullptr)
		{
			continue;
		}

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

		if (!bulletLife)
		{
			return;
		}
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
		{
			bullet++;
		}
	}
	return;
}

void Player::HurtingAnimation(int atk)
{
	LabelTTF* hurt = LabelTTF::create(String::createWithFormat("-%d", atk)->getCString(), "arial", 56);
	hurt->setColor(Color3B(0xFF, 0, 0));
	hurt->setPosition(80, Director::getInstance()->getVisibleSize().height - 70);

	auto act = Sequence::create(Blink::create(1.0f, 3),
		CallFunc::create(([hurt](void){
		hurt->setVisible(false);
		hurt->removeFromParentAndCleanup(true);
	})), nullptr);

	this->getParent()->addChild(hurt);
	hurt->runAction(act);

	Vector<SpriteFrame *>loadVector;
	char name[16];

	auto sprite = Sprite::create();
	sprite->setPosition(this->getContentSize() / 2);
	sprite->setScale(5.0f);
	this->addChild(sprite); //用于播放动画的精灵

	auto callfun = CallFunc::create(([sprite](void){
		sprite->setVisible(false);
		sprite->removeFromParentAndCleanup(true);
	}));

	for (int i = 1; i <= 6; i++)
	{
		sprintf(name, "hurt (%d).png", i);
		loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	sprite->runAction(Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 24.0f)),
		callfun, nullptr));

	return;
}