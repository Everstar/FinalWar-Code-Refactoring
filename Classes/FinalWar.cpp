#include "FinalWar.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

#define MONSTER_NUM 7

LabelLayer* FinalWar::labellayer = nullptr;

FinalWar::FinalWar()
{
	monsterNum = -1;

	turned = 1;

	backgroundOne = nullptr;
	backgroundTwo = nullptr;

	zijian = nullptr;
	boat = nullptr;
	dragon = nullptr;
	forset = nullptr;
	star = nullptr;

	state = 0;
	time = 0.0f;
}

Scene* FinalWar::createScene()
{
    auto scene = Scene::create();
	auto labellayer = LabelLayer::create();
	scene->addChild(labellayer, 1);
	FinalWar::labellayer = labellayer;
    auto layer = FinalWar::create();
    scene->addChild(layer, 0);

	//分数层绑定游戏层 实现暂停操作
	layer->labellayer->gamerlayer = layer;

    return scene;
}

bool FinalWar::init()
{
    if ( !Layer::init() )
        return false;

    visibleSize = Director::getInstance()->getVisibleSize();

	this->initBG(); // 初始化地图

	this->initRole(); // 初始化角色

	this->setKeyboardEnabled(true); //开启键盘监听
	auto controller = EventListenerKeyboard::create();
	controller->onKeyPressed = CC_CALLBACK_2(FinalWar::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(controller, this);

	this->scheduleUpdate();

    return true;
}

void FinalWar::initBG()
{
	backgroundOne = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(PATH_BACKGROUND_FORMER));
	backgroundOne->setPosition(visibleSize / 2);
	this->addChild(backgroundOne, 0);

	backgroundTwo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(PATH_BACKGROUND_LATTER));
	backgroundTwo->setPosition(visibleSize.width * 3 / 2, visibleSize.height / 2);
	this->addChild(backgroundTwo, 0);

	SimpleAudioEngine::getInstance()->playBackgroundMusic(PATH_AUDIO_BACKGROUND, true);
}

void FinalWar::initRole()
{
	boat = Factory::GetInstance()->CreatePlayer(FigureType::Boat);
	boat->setPosition(visibleSize.width / 5, visibleSize.height / 2);
	this->addChild(boat, 1);

	star = Factory::GetInstance()->CreatePlayer(FigureType::Star);
	boat->addChild(star);

	dragon = Factory::GetInstance()->CreatePlayer(FigureType::Dragon);
	boat->addChild(dragon, 0);
	
	forset = Factory::GetInstance()->CreatePlayer(FigureType::Forset);
	boat->addChild(forset, 0);

	zijian = Factory::GetInstance()->CreateBoss();
	zijian->setPosition(visibleSize.width * 0.7f, visibleSize.height / 2);
	this->addChild(zijian, 1);

	star->BindBoss(zijian);
	dragon->BindBoss(zijian);
	forset->BindBoss(zijian);
	zijian->BindHero(boat);

	star->SetMonsterArray(&monsterArray);
	dragon->SetMonsterArray(&monsterArray);
	forset->SetMonsterArray(&monsterArray);

	boat->Attach(labellayer->hpPlayer);
	zijian->Attach(labellayer->hpBoss);

	this->schedule(schedule_selector(FinalWar::MonsterAttack), 10.2f);
	this->schedule(schedule_selector(FinalWar::Rotate), 8.0f);
}

void FinalWar::RollingBackground() {	//背景移动

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
}

void FinalWar::update(float delta)
{
	time += 0.001f;

	RollingBackground();

	//判断胜利或失败
	if (boat->GetCurrentHP() <= 0)
		this->GameOver(false);
	else if (zijian->GetCurrentHP() <= 0)
		this->GameOver(true);

	//限制英雄活动范围
	if (boat->getPositionX() > zijian->getPositionX())
	{
		this->Turn();
		boat->setPositionX(zijian->getPositionX() - 800);
	}
	else if (boat->getPositionX() <= 40)
		boat->setPositionX(40);
	if (boat->getPositionY() >= visibleSize.height - 80)
		boat->setPositionY(visibleSize.height - 80);
	else if (boat->getPositionY() <= 40)
		boat->setPositionY(40);

	if (!monsterArray.empty())
	{
		ilist<Monster* >::listIterator monster = monsterArray.begin();
		while (monster != monsterArray.end())
		{
			//判断小怪位置
			if ((*monster)->getPositionX() > 0) //小怪向左移动
				(*monster)->setPositionX((*monster)->getPositionX() - 1);
			
			if ((*monster)->GetHP() <= 0) //小怪生命值低于0
			{
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else if ((*monster)->getPositionX() <= 0) //小怪到达屏幕左边消失
			{
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else if (Entity::IsCollideWith(boat, (*monster))) //小怪撞到英雄
			{
				boat->Hurt((*monster)->GetATK());
				(*monster)->removeFromParentAndCleanup(true);
				monster = monsterArray.erase(monster);
			}
			else
				monster++;
		}
	}
}

void FinalWar::MonsterAttack(float delta)
{
	this->ReleaseMonster(MonsterType(++monsterNum));
	if (monsterNum >> 2)	monsterNum = -1;
}

void FinalWar::ReleaseMonster(MonsterType type) //释放小怪
{
	Monster* monster = nullptr;

	for (int i = 1; i <= MONSTER_NUM; i++)
	{
		//创建小怪
		monster = Factory::GetInstance()->CreateMonster(type);
		monster->setPosition(visibleSize.width + i * 120, CCRANDOM_0_1() * visibleSize.height);
		this->addChild(monster);
		monsterArray.pushBack(monster);
	}
}

//键盘监听
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
			forset->Attack();
		}break;
	case (EventKeyboard::KeyCode::KEY_L) :
		if (state == 2)
		{
			dragon->Attack();
		}break;
	case (EventKeyboard::KeyCode::KEY_K) :
		if (state == 1)
		{
			star->Attack();
		}break;

		//测试用================================Begin
	case (EventKeyboard::KeyCode::KEY_N) :
		boat->SetCurrentHP(0);
		break;
	case (EventKeyboard::KeyCode::KEY_M) :
		zijian->Hurt(1999, 1);
		break;
		//测试用================================End

	default:
		return;
	}
}

void FinalWar::Turn() //屏幕翻转
{
	auto turn = RotateBy::create(1.0f, 180);
	this->runAction(turn);
	turned = -turned;
}

void FinalWar::Move(short x, short y) //英雄移动
{
	auto moveAction = MoveBy::create(0.3f, Vec2(15 * x, y * 15));
	boat->runAction(moveAction);
}

void FinalWar::Rotate(float delta) //英雄轮换一个位置
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
}

void FinalWar::GameOver(bool win)
{
	//创建模糊背景
	auto pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("bg&ui/bg_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	this->addChild(pauseBackground, 9);

	zijian->setVisible(false);
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(labellayer);

	if (turned = -1)
	{
		this->setRotation(0);
	}

	auto background = Sprite::create(PATH_BACKGROUND_END);
	background->setPosition(visibleSize / 2);
	this->addChild(background, 10);

	auto againItem = Sprite::createWithSpriteFrameName("cagain.png");
	auto againItemOn = Sprite::createWithSpriteFrameName("cagainOn.png");
	auto restart = MenuItemSprite::create(againItem, againItemOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(1, FinalWar::createScene()));
	});

	auto backItem = Sprite::createWithSpriteFrameName("cmenu.png");
	auto backItemOn = Sprite::createWithSpriteFrameName("cmenuOn.png");
	auto back = MenuItemSprite::create(backItem, backItemOn, [=](Ref* pSender){
		Director::getInstance()->resume();
		this->removeFromParent();
		Director::getInstance()->replaceScene(TransitionMoveInB::create(1, FinalWar::createScene()));
	});

	auto menu = Menu::create(restart, back, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu, 10);

	if (win)
		Win();
	else
		Fail();
}

void FinalWar::Fail()
{
	int grade = (1 - ((float)zijian->GetCurrentHP() / (float)zijian->GetFullHP())) * 50;
	
	auto scoreLabel = LabelTTF::create("0000", "angryblue", 34);
	scoreLabel->setString(String::createWithFormat("%d", grade)->getCString());
	scoreLabel->setColor(Color3B(255, 255, 255));
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63);
	this->addChild(scoreLabel, 11);

	auto jian = Sprite::createWithSpriteFrameName("B_zijian_magic.png");
	jian->setScale(0.6f);
	jian->setPosition(visibleSize.width * 0.88f, visibleSize.height / 2);
	this->addChild(jian, 12);

	auto label = LabelTTF::create("23333", "arial", 62);
	label->setPosition(visibleSize.width * 0.79f, visibleSize.height * 0.85f);
	this->addChild(label, 12);
}

void FinalWar::Win()
{
	int grade = (float)boat->GetCurrentHP() / (float)boat->GetFullHP() * 50 + 50;

	auto scoreLabel = LabelTTF::create("0000", "angryblue", 34);
	scoreLabel->setString(String::createWithFormat("%d", grade)->getCString());
	scoreLabel->setColor(Color3B(255, 255, 255));
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.63f);

	this->addChild(scoreLabel, 11);
}