#include "Factory.h"

Factory *Factory::instance = nullptr;

Factory::Factory()
{
	Monster::addAllPrototypes();
}

Factory::~Factory()
{
	if (instance)
		delete instance;
}

Player* Factory::CreatePlayer(FigureType type)
{
	Player* player = nullptr;
	player = Player::create();
	
	switch (type)
	{
	case Forset:
		player->BindSprite(Sprite::createWithSpriteFrameName("B_sensen.png"));
		player->SetBullet(5, 4);
		player->setScale(0.1f);
		player->SetPower(50);
		player->setPosition(80, 80);
		player->setAnchorPoint(Point(0, 0));
		player->setRotation(-30);
		break;
	case Star:
		player->BindSprite(Sprite::createWithSpriteFrameName("B_littlestar.png"));
		player->SetBullet(3, 2);
		player->setScale(0.1f);
		player->SetPower(40);
		player->setPosition(120, 85);
		player->setAnchorPoint(Point(0, 0));
		player->setRotation(-150);
		break;
	case Dragon:
		player->BindSprite(Sprite::createWithSpriteFrameName("B_huolong.png"));
		player->SetBullet(4, 1);
		player->setScale(0.1f);
		player->SetPower(60);
		player->setPosition(105, 120);
		player->setAnchorPoint(Point(0, 0));
		player->setRotation(90);
		break;
	case Boat:
		player->unscheduleUpdate(); //船不需要检测子弹
		player->BindSprite(Sprite::createWithSpriteFrameName("B_boat.png"));
		player->setScale(0.6f);
		player->setAnchorPoint(Point(0.5, 0.5));
		player->setRotation(35);
		break;
	default:
		break;
	}
	return player;
}

Boss* Factory::CreateBoss()
{
	Boss *boss = Boss::create();
	boss->BindSprite(Sprite::createWithSpriteFrameName("B_zijian.png"));
	boss->SetSkill("B_bossbullet.png");
	boss->setScale(0.12f);
	return boss;
}

Monster* Factory::CreateMonster(MonsterType type)
{
	return Monster::findAndClone(type);
}

Bullet* Factory::CreateBullet(BulletType type, int atk)
{
	Bullet *bullet = Bullet::create();
	Sprite* pic;
	switch (type)
	{
	case Light:
		pic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("bullet/bulletSize.png"));
		pic->setScale(1.0f);
		break;
	case Ball:
		pic = Sprite::createWithSpriteFrameName("B_bossbullet.png");
		pic->setScale(0.5f);
		break;
	default:
		break;
	}

	bullet->BindSprite(pic);
	bullet->SetATK(atk);
	return bullet;
}

void Factory::CreateHurtingAnimation(FigureType type, Sprite* &sprite, int bulletState)
{
	Vector<SpriteFrame *>loadVector;
	char name[16];

	sprite->setScale(5.0f);

	//动画播放完毕后释放内存
	auto callfun = CallFunc::create(([sprite](void){
		sprite->setVisible(false);
		sprite->removeFromParentAndCleanup(true);
	}));

	switch (type)
	{
	case Boat:
		for (int i = 1; i <= 6; i++)
		{
			sprintf(name, "hurt (%d).png", i);
			loadVector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
		}
		break;
	case BOSS:
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
			sprite->setScale(10.0f); //因为图像大小的不一致需再次调整大小
			break;
		default:
			return;
		}
		break;
	default:
		break;
	}

	sprite->runAction(Sequence::create(
		Animate::create(Animation::createWithSpriteFrames(loadVector, 1 / 24.0f)),
		callfun, nullptr));
}

LabelTTF* Factory::CreateBlinkNotification(FigureType type, int atk)
{
	LabelTTF* label;
	switch (type)
	{
	case Boat:
		label = LabelTTF::create(String::createWithFormat("-%d", atk)->getCString(), "arial", 56);
		label->setColor(Color3B(0xFF, 0, 0));
		label->setPosition(80, Director::getInstance()->getVisibleSize().height - 70);
		break;
	case BOSS:
		label = LabelTTF::create(String::createWithFormat("Hit %d", atk)->getCString(), "arial", 56);
		label->setColor(Color3B(255, 165, 0));
		label->setPosition(Director::getInstance()->getVisibleSize().width * 0.8f, 70);
		break;
	case MONSTER:
		label = LabelTTF::create(String::createWithFormat("Hit %d", atk)->getCString(), "arial", 36);
		label->setColor(Color3B(255, 0, 0));
		break;
	default:
		break;
	}

	auto act = Sequence::create(Blink::create(2.0f, 4),
		CallFunc::create(([label](void){
		label->setVisible(false);
		label->removeFromParentAndCleanup(true);
	})), nullptr);

	label->runAction(act);

	return label;
}