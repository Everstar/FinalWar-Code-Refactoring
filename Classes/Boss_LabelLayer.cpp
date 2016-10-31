#include "Boss_LabelLayer.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

bool Boss_LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	flagPause = true;
	flagResume = false;
	flagMusic = true;

	auto line = Sprite::create("SkullBarMain.png");  //�߿�
	line->setPosition(visibleSize / 2);
	this->addChild(line, 0);

	this->CreateHPLabel();

	// ������ͣ��������
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && flagPause)
		{
			flagPause = !flagPause;
			pauseScene();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

	this->scheduleUpdate();

	return true;
}

void Boss_LabelLayer::SetScore(float grade)
{
	this->score = grade;
	return;
}

float Boss_LabelLayer::GetScore()
{
	return score;
}

void Boss_LabelLayer::update(float delta)
{
	hpBarblood_H->setPercentage((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 100);

	hpBarblood_B->setPercentage((float)boss->GetCurrentHP() / (float)boss->GetFullHP() * 100);

	// �����ͣ���水ť�Ƿ�ɾ��
	if (flagResume)
	{
		removeChild(menu);
		flagResume = !flagResume;
	}

	return;
}

void Boss_LabelLayer::BindHero(Boss_Hero* phero)
{
	this->hero = phero;
	return;
}

void Boss_LabelLayer::BindBoss(Boss* pboss)
{
	this->boss = pboss;
	return;
}

void Boss_LabelLayer::initMusic() //�������ֲ˵�
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	musicOnLabel = MenuItemImage::create("B_musicOn.png", "B_musicOn.png", CC_CALLBACK_1(Boss_LabelLayer::MusicOn, this));
	musicOnLabel->setVisible(false);
	musicOnLabel->setEnabled(false);
	musicOnLabel->setScale(0.6f);

	musicOffLabel = MenuItemImage::create("B_musicOff.png", "B_musicOff.png", CC_CALLBACK_1(Boss_LabelLayer::MusicOff, this));
	musicOffLabel->setScale(0.6f);

	musicMenu = Menu::create(musicOnLabel, musicOffLabel, NULL);
	musicMenu->alignItemsHorizontallyWithPadding(-100.0f);
	musicMenu->setPosition(visibleSize.width * 0.88f, visibleSize.height * 0.10f);

	this->addChild(musicMenu, 1);

	return;
}

void Boss_LabelLayer::MusicOn(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
	musicOnLabel->setEnabled(false);
	musicOnLabel->setVisible(false);
	musicOffLabel->setEnabled(true);
	musicOffLabel->setVisible(true);
	return;
}

void Boss_LabelLayer::MusicOff(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
	musicOnLabel->setEnabled(true);
	musicOnLabel->setVisible(true);
	musicOffLabel->setEnabled(false);
	musicOffLabel->setVisible(false);
	return;
}

void Boss_LabelLayer::CreateHPLabel() //Ѫ����
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//Hero
	hpBar_H = Sprite::createWithSpriteFrameName("B_hpbar.png"); //������
	hpBar_H->setPosition(210, visibleSize.height - 46);
	this->addChild(hpBar_H, 1);

	hpBarblood_H = ProgressTimer::create(Sprite::createWithSpriteFrameName("B_hpbarblood.png")); //Ѫ����
	hpBarblood_H->setType(ProgressTimer::Type::BAR); //����ģʽ
	hpBarblood_H->setMidpoint(Point(0, 0.5f)); //��������ʼλ��
	hpBarblood_H->setBarChangeRate(Point(1,0)); //��ʾ��X��仯
	hpBarblood_H->setPercentage(100);
	hpBarblood_H->setPosition(Point(0, 0));
	hpBarblood_H->setAnchorPoint(Point(0, 0));

	hpBar_H->addChild(hpBarblood_H);

	//Boss zijian
	hpBar_B = Sprite::createWithSpriteFrameName("B_hpbar_Boss.png"); //������
	hpBar_B->setPosition(visibleSize.width / 2, 46);
	this->addChild(hpBar_B, 1);

	hpBarblood_B = ProgressTimer::create(Sprite::createWithSpriteFrameName("B_hpbarblood_Boss.png")); //Ѫ����
	hpBarblood_B->setType(ProgressTimer::Type::BAR); //����ģʽ
	hpBarblood_B->setMidpoint(Point(0, 0.5f)); //��������ʼλ��
	hpBarblood_B->setBarChangeRate(Point(1, 0)); //��ʾ��X��仯
	hpBarblood_B->setPercentage(100);
	hpBarblood_B->setPosition(Point(0, 0));
	hpBarblood_B->setAnchorPoint(Point(0, 0));

	hpBar_B->addChild(hpBarblood_B);

	return;
}

void Boss_LabelLayer::pauseScene()
{
	//������ͣ�˵�ģ������
	pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("F_pause.png"));
	pauseBackground->setPosition(visibleSize / 2);
	addChild(pauseBackground);

	// ������ͣ������UI
	pauseMainUI = Sprite::create("pause.png");
	pauseMainUI->setPosition(visibleSize / 2);
	addChild(pauseMainUI, 5);

	// ȫ����ͣ��������������
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(gamerlayer);

	// ESC������Ϸ
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
		{
			resumeScene();
		}
	};

	// ����������Ϸ��ť
	auto resumeSprite = Sprite::create("resume.png");
	auto resumeSprite2 = Sprite::create("resume.png");
	resumeSprite2->setScale(0.98f);
	resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
		resumeScene();
	});
	resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	// ��������Ϸ��ť
	auto newGameSprite = Sprite::create("newgame.png");
	auto newGameSprite2 = Sprite::create("newgame.png");
	newGameSprite2->setScale(0.9f);
	newGame = MenuItemSprite::create(newGameSprite, newGameSprite2, [=](Ref* pSender){
		resumeScene();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(1, FinalWar::createScene()));
	});
	newGame->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// ���������ֵİ�ť
	auto musicSprite = Sprite::create("music.png");
	auto musicSprite2 = Sprite::create("music.png");
	musicSprite2->setScale(0.9f);
	music = MenuItemSprite::create(musicSprite, musicSprite2, [=](Ref* pSender){
		if (flagMusic)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		flagMusic = !flagMusic;
	});
	music->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);

	menu = Menu::create(resume, music, newGame, nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 6);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);

	return;
}

void Boss_LabelLayer::resumeScene()
{
	flagResume = true;
	removeChild(pauseMainUI);
	removeChild(pauseBackground);
	removeChild(menu);
	flagPause = !flagPause;
	Director::getInstance()->resume();
	Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(gamerlayer);
	return;
}