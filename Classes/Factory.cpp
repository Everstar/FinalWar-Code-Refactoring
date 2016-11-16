#include "Factory.h"

Factory *Factory::instance = nullptr;

Factory::Factory()
{

}

Factory::~Factory()
{
	if (instance)
		delete instance;
}

Player* Factory::CreatePlayer(PlayerType type)
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

Monster* Factory::CreateMonster(MonsterType type, float scale, int atk, int life)
{
	if (type == MonsterType::BagSprite)
	{
		return BagSprite::create();
	}

	Monster *monster = Monster::create();

	switch (type)
	{
	case BagSprite:
		monster->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BAGSPRITE));
		break;
	case Banana:
		monster->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BANANA));
		break;
	case Bat:
		monster->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BAT));
		break;
	case ThunderBall:
		monster->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_THUNDERBALL));
		break;
	case Donggua:
		monster->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_DONGGUA));
		break;
	default:
		break;
	}

	monster->setScale(scale);
	monster->SetATK(atk);
	monster->SetHP(life);
	return monster;
}

Bullet* Factory::CreateBullet(BulletType type, float scale, int atk)
{
	Bullet *bullet = Bullet::create();
	Sprite* pic;
	switch (type)
	{
	case Light:
		pic = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("bullet/bulletSize.png"));
		break;
	case Ball:
		pic = Sprite::createWithSpriteFrameName("B_bossbullet.png");
		break;
	default:
		break;
	}

	
	pic->setScale(scale);
	bullet->BindSprite(pic);
	bullet->SetATK(atk);
	return bullet;
}