#include "FinalWar.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
#define MONSTER_NUM 7

FinalWar::FinalWar()
{
	monsterFile[0] = "F_BagSprite.png";
	monsterFile[1] = "F_Banana.png";
	monsterFile[2] = "F_Bat.png";
	monsterFile[3] = "F_ThunderBall.png";
	monsterFile[4] = "F_Donggua.png";
	monsterNum = 0;

	labellayer = nullptr;

	turned = 1;

	backgroundOne = nullptr;
	backgroundTwo = nullptr;

	zijian = nullptr;
	boat = nullptr;
	huolong = nullptr;
	sensen = nullptr;
	littlestar = nullptr;

	updown = true;
	leftright = true;
	state = 0;
	time = 0.0f;
}

Scene* FinalWar::createScene()
{
    auto scene = Scene::create();
    auto layer = FinalWar::create();
	layer->labellayer = Boss_LabelLayer::create();
    scene->addChild(layer);
	scene->addChild(layer->labellayer);

	//����������� ��ȡ������Ϣ��
	layer->labellayer->BindHero(layer->boat);
	layer->labellayer->BindBoss(layer->zijian);
	layer->labellayer->gamerlayer = layer;

    return scene;
}

bool FinalWar::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Red.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Green.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Blue.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hit.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MagicCircle.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet1.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet2.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("bullet4.plist");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_hplabel.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_MenuItem.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("B_Figure.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FD_Monster.plist");
	Director::getInstance()->getTextureCache()->addImage("B_bg1.png");
	Director::getInstance()->getTextureCache()->addImage("B_bg2.png");
	Director::getInstance()->getTextureCache()->addImage("bulletSize.png");
	Director::getInstance()->getTextureCache()->addImage("F_pause.png");

    visibleSize = Director::getInstance()->getVisibleSize();

	this->initBG(); // ��ʼ����ͼ

	this->initRole(); // ��ʼ����ɫ

	this->setKeyboardEnabled(true); //�������̼���
	auto controller = EventListenerKeyboard::create();
	controller->onKeyPressed = CC_CALLBACK_2(FinalWar::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controller, this);

	this->scheduleUpdate();

    return true;
}

void FinalWar::initBG()
{
	backgroundOne = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("B_bg1.png"));
	backgroundOne->setPosition(visibleSize / 2);
	this->addChild(backgroundOne, 0);

	backgroundTwo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("B_bg2.png"));
	backgroundTwo->setPosition(visibleSize.width * 3 / 2, visibleSize.height / 2);
	this->addChild(backgroundTwo, 0);

	return;
}

void FinalWar::initRole()
{
	boat = Boss_Hero::create();
	boat->unscheduleUpdate(); //������Ҫ����ӵ�
	boat->BindSprite(Sprite::createWithSpriteFrameName("B_boat.png"));
	boat->setScale(0.6f);
	boat->setAnchorPoint(Point(0.5, 0.5));
	boat->setRotation(35);
	boat->setPosition(visibleSize.width / 5, visibleSize.height / 2);
	this->addChild(boat, 1);

	littlestar = Boss_Hero::create();
	littlestar->BindSprite(Sprite::createWithSpriteFrameName("B_littlestar.png"));
	littlestar->SetBullet(3, 2);
	littlestar->setScale(0.1f);
	littlestar->SetPower(40);
	littlestar->setPosition(120, 85);
	littlestar->setAnchorPoint(Point(0, 0));
	littlestar->setRotation(-150);
	boat->addChild(littlestar);

	huolong = Boss_Hero::create();
	huolong->BindSprite(Sprite::createWithSpriteFrameName("B_huolong.png"));
	huolong->SetBullet(4, 1);
	huolong->setScale(0.1f);
	huolong->SetPower(60);
	huolong->setPosition(105, 120);
	huolong->setAnchorPoint(Point(0, 0));
	huolong->setRotation(90);
	boat->addChild(huolong, 0);
	
	sensen = Boss_Hero::create();
	sensen->BindSprite(Sprite::createWithSpriteFrameName("B_sensen.png"));
	sensen->SetBullet(5, 4);
	sensen->setScale(0.1f);
	sensen->SetPower(50);
	sensen->setPosition(80,80);
	sensen->setAnchorPoint(Point(0, 0));
	sensen->setRotation(-30);
	boat->addChild(sensen, 0);

	zijian = Boss::create();
	zijian->BindSprite(Sprite::createWithSpriteFrameName("B_zijian.png"));
	zijian->SetSkill("B_bossbullet.png");
	zijian->setScale(0.12f);
	zijian->setPosition(visibleSize.width * 0.7f, visibleSize.height / 2);
	this->addChild(zijian, 1);

	littlestar->BindBoss(zijian);
	huolong->BindBoss(zijian);
	sensen->BindBoss(zijian);
	zijian->BindHero(boat);

	littlestar->SetMonsterArray(&monsterArray);
	huolong->SetMonsterArray(&monsterArray);
	sensen->SetMonsterArray(&monsterArray);

	this->schedule(schedule_selector(FinalWar::BossAttack), 1.2f);
	this->schedule(schedule_selector(FinalWar::MonsterAttack), 10.2f);
	this->schedule(schedule_selector(FinalWar::Rotate), 8.0f);

	return;
}

void FinalWar::update(float delta)
{
	time += 0.001f;

	//�����ƶ�
	backgroundOne->setPositionX(backgroundOne->getPositionX() - 2);
	backgroundTwo->setPositionX(backgroundTwo->getPositionX() - 2);
	
	if (backgroundOne->getPositionX() <= -visibleSize.width / 2)
	{
		backgroundOne->setPositionX(visibleSize.width * 3 / 2);
	}
	if (backgroundTwo->getPositionX() <= -visibleSize.width / 2)
	{
		backgroundTwo->setPositionX(visibleSize.width * 3 / 2);
	}

	//�ж�ʤ����ʧ��
	if (boat->GetCurrentHP() <= 0)
	{
		this->Fail();
	}
	else if (zijian->GetCurrentHP() <= 0)
	{
		this->Win();
	}

	//����Ӣ�ۻ��Χ
	if (boat->getPositionX() > zijian->getPositionX())
	{
		this->Turn();
		boat->setPositionX(zijian->getPositionX() - 800);
	}
	else if (boat->getPositionX() <= 40)
	{
		boat->setPositionX(40);
	}
	if (boat->getPositionY() >= visibleSize.height - 80)
	{
		boat->setPositionY(visibleSize.height - 80);
	}
	else if (boat->getPositionY() <= 40)
	{
		boat->setPositionY(40);
	}

	if (zijian->GetCurrentHP() <= (zijian->GetFullHP() / 2)) //����Boss�����ƶ�
	{
		if (leftright == true)
		{
			if (zijian->getPositionX() <= visibleSize.width * 0.88f)
			{
				zijian->setPositionX(zijian->getPositionX() + 3);
			}
			else
			{
				leftright = false;
			}
		}
		else
		{
			if (zijian->getPositionX() >= visibleSize.width * 0.66f)
			{
				zijian->setPositionX(zijian->getPositionX() - 3);
			}
			else
			{
				leftright = true;
			}
		}
	}

	if (updown == true) //����Boss�����ƶ�
	{
		if (zijian->getPositionY() <= visibleSize.height - 100)
		{
			zijian->setPositionY(zijian->getPositionY() + 3 + (int)time % 8);
		}
		else
		{
			updown = false;
		}
	}
	else
	{
		if (zijian->getPositionY() >= 0)
		{
			zijian->setPositionY(zijian->getPositionY() - 3 - (int)time % 8);
		}
		else
		{
			updown = true;
		}
	}

	if (!monsterArray.empty())
	{
		cocos2d::Vector<Boss_Monster* >::iterator monster = monsterArray.begin();
		while (monster != monsterArray.end())
		{
			//�ж�С��λ��
			if ((*monster)->getPositionX() > 0) //С�������ƶ�
			{
				(*monster)->setPositionX((*monster)->getPositionX() - 1);
			}
			
			if ((*monster)->GetHP() <= 0) //С������ֵ����0
			{
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else if ((*monster)->getPositionX() <= 0) //С�ֵ�����Ļ�����ʧ
			{
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else if ((*monster)->IsCollideWithHero(boat)) //С��ײ��Ӣ��
			{
				boat->Hurt((*monster)->GetATK());
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else
			{
				monster++;
			}
		}
	}

	return;
}

void FinalWar::BossAttack(float delta)
{
	int num = 2;
	if (zijian->GetCurrentHP() <= (zijian->GetFullHP() / 2))
	{
		num = 3;
	}
	else if (zijian->GetCurrentHP() <= (zijian->GetFullHP() / 4))
	{
		num = 4;
	}
	zijian->Attack(num, 0.5f, 100);
	return;
}

void FinalWar::MonsterAttack(float delta)
{
	this->ReleaseMonster(monsterFile[monsterNum++], 0.18f, 20 * (monsterNum + 1), 100 * monsterNum);
	if (monsterNum > 4)
	{
		monsterNum = 0;
	}
	return;
}

void FinalWar::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case (EventKeyboard::KeyCode::KEY_W) :
		Move(0, turned * 3); break;
	case (EventKeyboard::KeyCode::KEY_S) :
		Move(0, turned * (-3)); break;
	case (EventKeyboard::KeyCode::KEY_D) :
		Move(turned * 3, 0); break;
	case (EventKeyboard::KeyCode::KEY_A) :
		Move(turned * (-3), 0); break;
	case (EventKeyboard::KeyCode::KEY_UP_ARROW) :
		Move(0, turned * 3); break;
	case (EventKeyboard::KeyCode::KEY_DOWN_ARROW) :
		Move(0, turned * (-3)); break;
	case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW) :
		Move(turned * 3, 0); break;
	case (EventKeyboard::KeyCode::KEY_LEFT_ARROW) :
		Move(turned * (-3), 0); break;
	case (EventKeyboard::KeyCode::KEY_J) :
		if (state == 0)
		{
			sensen->Attack(1.0f);
		}break;
	case (EventKeyboard::KeyCode::KEY_L) :
		if (state == 2)
		{
			huolong->Attack(1.0f);
		}break;
	case (EventKeyboard::KeyCode::KEY_K) :
		if (state == 1)
		{
			littlestar->Attack(1.0f);
		}break;
	default:
		return;
	}
	return;
}

void FinalWar::Turn() //��Ļ��ת
{
	auto turn = RotateBy::create(1.0f, 180);
	this->runAction(turn);
	turned = -turned;
	return;
}

void FinalWar::Move(short x, short y) //Ӣ���ƶ�
{
	auto moveAction = MoveBy::create(0.3f, Vec2(15 * x, y * 15));
	boat->runAction(moveAction);
	return;
}

void FinalWar::Rotate(float delta) //Ӣ���ֻ�һ��λ��
{
	state += 1;
	state = state % 3;
	
	auto box = Sprite::createWithSpriteFrameName("B_dailog_box.png");
	box->setPosition(visibleSize.width / 2, visibleSize.height * 0.7f);
	this->addChild(box);
	
	auto label = LabelTTF::create("Spin", "arial", 56);
	label->setPosition(box->getContentSize() / 2);
	box->addChild(label);

	auto callfun = CallFunc::create(([box](void){
		box->removeAllChildren();
		box->setVisible(false);
		box->removeFromParentAndCleanup(true);
	}));

	box->runAction(Sequence::create(DelayTime::create(3.0f), callfun, nullptr));

	auto rotate = RotateTo::create(1.2f, boat->getRotation() + 120);
	boat->runAction(rotate);
	return;
}

void FinalWar::ReleaseMonster(const std::string &filename, float scale, int atk, int life) //�ͷ�С��
{
	Boss_Monster* monster = NULL;

	for (int i = 1; i <= MONSTER_NUM; i++)
	{
		//����С��
		monster = Boss_Monster::create();
		monster->BindSprite(Sprite::createWithSpriteFrameName(filename));
		monster->setScale(scale);
		monster->SetATK(atk);
		monster->SetHP(life);
		monster->setPosition(visibleSize.width + i * 120, CCRANDOM_0_1() * visibleSize.height);    //, visibleSize.height / 8 * i - 120);
		this->addChild(monster);
		monsterArray.pushBack(monster);
	}

	return;
}

void FinalWar::Fail()
{
	//����ģ������
	auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	this->addChild(pauseBackground, 9);

	zijian->setVisible(false);
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(labellayer);
	
	if (turned = -1)
	{
		this->setRotation(0);
	}
	
	auto background = Sprite::create("F_End.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 10);

	auto again = Sprite::createWithSpriteFrameName("F_cagain.png");
	auto againOn = Sprite::createWithSpriteFrameName("F_cagainOn.png");
	auto restart = MenuItemSprite::create(again, againOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(1, FinalWar::createScene()));
	});

	auto backMenu = Sprite::createWithSpriteFrameName("F_cmenu.png");
	auto backMenuOn = Sprite::createWithSpriteFrameName("F_cmenuOn.png");
	auto back = MenuItemSprite::create(backMenu, backMenuOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		//Director::getInstance()->replaceScene(TransitionMoveInB::create(1, FinalWar::createScene()));
	});

	auto menu = Menu::create(restart, back, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu, 10);

	int grade = (1 - ((float)zijian->GetCurrentHP() / (float)zijian->GetFullHP())) * 50;
	
	auto scoreLabel = LabelTTF::create("0000", "angryblue", 34);
	scoreLabel->setString(String::createWithFormat("%d", grade)->getCString());
	scoreLabel->setColor(Color3B(255, 255, 255));
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63);
	this->addChild(scoreLabel, 11);

	auto jian = Sprite::create("B_zijian_magic.png");
	jian->setScale(0.6f);
	jian->setPosition(visibleSize.width * 0.88f, visibleSize.height / 2);
	this->addChild(jian, 12);

	auto label = LabelTTF::create("23333", "arial", 62);
	label->setPosition(visibleSize.width * 0.79f, visibleSize.height * 0.85f);
	this->addChild(label, 12);

	return;
}

void FinalWar::Win()
{
	//����ģ������
	auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	this->addChild(pauseBackground, 9);

	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(labellayer);
	
	if (turned = -1)
	{
		this->setRotation(0);
	}
	
	auto background = Sprite::create("F_End.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background, 10);

	auto nextItem = Sprite::createWithSpriteFrameName("F_cnext.png");
	auto nextItemOn = Sprite::createWithSpriteFrameName("F_cnextOn.png");
	auto next = MenuItemSprite::create(nextItem, nextItemOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();

	});

	auto againItem = Sprite::createWithSpriteFrameName("F_cagain.png");
	auto againItemOn = Sprite::createWithSpriteFrameName("F_cagainOn.png");
	auto restart = MenuItemSprite::create(againItem, againItemOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(1, FinalWar::createScene()));
	});

	auto backItem = Sprite::createWithSpriteFrameName("F_cmenu.png");
	auto backItemOn = Sprite::createWithSpriteFrameName("F_cmenuOn.png");
	auto back = MenuItemSprite::create(backItem, backItemOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionMoveInB::create(1, FinalWar::createScene()));
	});

	auto menu = Menu::create(next, restart, back, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
	menu->alignItemsVerticallyWithPadding(2);
	this->addChild(menu, 11);

	int grade = (float)boat->GetCurrentHP() / (float)boat->GetFullHP() * 50 + 50;

	auto scoreLabel = LabelTTF::create("0000", "angryblue", 34);
	scoreLabel->setString(String::createWithFormat("%d", grade)->getCString());
	scoreLabel->setColor(Color3B(255, 255, 255));
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63f);

	this->addChild(scoreLabel, 11);

	return;
}