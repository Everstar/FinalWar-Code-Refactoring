#include "Player.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

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
}

void Player::SetType(int num, int state, FigureType type)
{
	plistNum = num;
	bulletState = state;
	_type = type;
	return;
}

void Player::SetMonsterArray(ilist<Monster* >* Array)
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

	switch (_type)
	{
	case Forset:
		SimpleAudioEngine::getInstance()->playEffect(PATH_AUDIO_LASER);
		break;
	case Star:
		SimpleAudioEngine::getInstance()->playEffect(PATH_AUDIO_ICE);
		break;
	case Dragon:
		SimpleAudioEngine::getInstance()->playEffect(PATH_AUDIO_FIRE);
		break;
	default:
		break;
	}
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

	this->ObservingData = (float)currentHP / (float)fullHP * 100.0f;
	this->Notify();
}

void Player::update(float delta)
{
	if (bulletArray.empty()) return;

	//检测子弹
	Size visibleSize = Director::getInstance()->getVisibleSize();
	ilist<Bullet* >::listIterator bullet = bulletArray.begin();
	bool bulletLife = false;//子弹是否存活
	while (bullet != bulletArray.end())
	{
		if ((*bullet) == nullptr) continue;

		bulletLife = true;
		(*bullet)->setPositionX((*bullet)->getPositionX() + 8);

		ilist<Monster* >::listIterator monster = monsterArray->begin();
		for (; monster != monsterArray->end(); monster++)
		{
			if ((*bullet)->getBoundingBox().intersectsRect((*monster)->getBoundingBox()))
			{
				(*monster)->LoseLife(power);
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
}

void Player::HurtingAnimation(int atk)
{
	LabelTTF* hurt = Factory::GetInstance()->CreateBlinkNotification(FigureType::Boat, atk);
	this->getParent()->addChild(hurt);

	auto sprite = Sprite::create();
	sprite->setPosition(this->getContentSize() / 2);
	this->addChild(sprite); //用于播放动画的精灵

	Factory::GetInstance()->CreateHurtingAnimation(FigureType::Boat, sprite);
}