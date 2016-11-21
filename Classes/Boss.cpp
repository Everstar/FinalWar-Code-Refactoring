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
	this->scheduleUpdate(); //����update����
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
}

void Boss::Hurt(int atk, int bulletState) //Boss����
{
	if (getSprite() == nullptr) return;

	this->HurtingAnimation(atk, bulletState);
	currentHP -= atk;
	if (currentHP < 0)
	{
		currentHP = 0;
	}

	this->ObservingData = (float)currentHP / (float)fullHP * 100.0f;
	this->Notify();
}

void Boss::Attack(int num) //Boss����
{
	Bullet* bullet = nullptr;

	for (int i = 0; i < num; i++)
	{
		//�����ӵ�
		bullet = Factory::GetInstance()->CreateBullet(BulletType::Ball, this->atk);
		if (i & 1)
			bullet->setPosition(this->getPositionX(), this->getPositionY() + count);
		else
			bullet->setPosition(this->getPositionX(), this->getPositionY() - count);

		this->getParent()->addChild(bullet);

		bulletArray.pushBack(bullet);

	}
}

void Boss::Aim(float delta) //Boss�ӵ��Զ�׷��Ӣ��
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

//��ʱ�ͷ��ӵ�����
void Boss::ReleaseBullets(float delta)
{
	this->Attack(_bossState->_state + 2);
}

void Boss::update(float delta)
{
	this->_bossState->DetectState();
	this->_bossState->Move();
	this->_bossState->Attack();
}

void Boss::HurtingAnimation(int atk, int bulletState)
{
	//�˺��������
	LabelTTF* hurt = Factory::GetInstance()->CreateBlinkNotification(FigureType::BOSS, atk);
	this->getParent()->addChild(hurt);

	auto sprite = Sprite::create();  //���ڲ��Ŷ����ľ���
	sprite->setPosition(this->getContentSize() / 2);
	this->addChild(sprite);

	Factory::GetInstance()->CreateHurtingAnimation(FigureType::BOSS, sprite, bulletState);
}