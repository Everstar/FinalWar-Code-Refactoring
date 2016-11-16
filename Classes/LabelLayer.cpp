#include "LabelLayer.h"
#include "Parameter.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

bool LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	flagPause = true;
	flagResume = false;
	flagMusic = true;

	auto line = Sprite::create(PATH_BACKGROUND_FRAME);  //边框
	line->setPosition(visibleSize / 2);
	this->addChild(line, 0);

	this->CreateHPLabel();

	// 创建暂停的侦听器
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && flagPause)
		{
			flagPause = !flagPause;
			pauseScene();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);
	this->initMusic();
	this->scheduleUpdate();

	return true;
}

void LabelLayer::SetScore(float grade)
{
	this->score = grade;
	return;
}

float LabelLayer::GetScore()
{
	return score;
}

void LabelLayer::update(float delta)
{
	hpBarblood_H->setPercentage((float)hero->GetCurrentHP() / (float)hero->GetFullHP() * 100);

	hpBarblood_B->setPercentage((float)boss->GetCurrentHP() / (float)boss->GetFullHP() * 100);

	// 检查暂停界面按钮是否删除
	if (flagResume)
	{
		removeChild(menu);
		flagResume = !flagResume;
	}

	return;
}

void LabelLayer::BindHero(Player* phero)
{
	this->hero = phero;
	return;
}

void LabelLayer::BindBoss(Boss* pboss)
{
	this->boss = pboss;
	return;
}

void LabelLayer::initMusic() //设置音乐菜单
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	musicOnLabel = MenuItemImage::create(PATH_UI_MUSIC_ON, PATH_UI_MUSIC_ON, CC_CALLBACK_1(LabelLayer::MusicOn, this));
	musicOnLabel->setVisible(false);
	musicOnLabel->setEnabled(false);
	musicOnLabel->setScale(0.6f);

	musicOffLabel = MenuItemImage::create(PATH_UI_MUSIC_OFF, PATH_UI_MUSIC_OFF, CC_CALLBACK_1(LabelLayer::MusicOff, this));
	musicOffLabel->setScale(0.6f);

	musicMenu = Menu::create(musicOnLabel, musicOffLabel, NULL);
	musicMenu->alignItemsHorizontallyWithPadding(-100.0f);
	musicMenu->setPosition(visibleSize.width * 0.88f, visibleSize.height * 0.10f);

	this->addChild(musicMenu, 1);

	return;
}

void LabelLayer::MusicOn(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
	musicOnLabel->setEnabled(false);
	musicOnLabel->setVisible(false);
	musicOffLabel->setEnabled(true);
	musicOffLabel->setVisible(true);
	return;
}

void LabelLayer::MusicOff(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
	musicOnLabel->setEnabled(true);
	musicOnLabel->setVisible(true);
	musicOffLabel->setEnabled(false);
	musicOffLabel->setVisible(false);
	return;
}

void LabelLayer::CreateHPLabel() //血量条
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//Hero
	hpBar_H = Sprite::createWithSpriteFrameName(PATH_UI_PALYER_HPBAR); //背景框
	hpBar_H->setPosition(210, visibleSize.height - 46);
	this->addChild(hpBar_H, 1);

	hpBarblood_H = ProgressTimer::create(Sprite::createWithSpriteFrameName(PATH_UI_PALYER_HPBARBLOOD)); //血量条
	hpBarblood_H->setType(ProgressTimer::Type::BAR); //条形模式
	hpBarblood_H->setMidpoint(Point(0, 0.5f)); //进度条起始位置
	hpBarblood_H->setBarChangeRate(Point(1,0)); //表示沿X轴变化
	hpBarblood_H->setPercentage(100);
	hpBarblood_H->setPosition(Point(0, 0));
	hpBarblood_H->setAnchorPoint(Point(0, 0));

	hpBar_H->addChild(hpBarblood_H);

	//Boss zijian
	hpBar_B = Sprite::createWithSpriteFrameName(PATH_UI_BOSS_HPBAR); //背景框
	hpBar_B->setPosition(visibleSize.width / 2, 46);
	this->addChild(hpBar_B, 1);

	hpBarblood_B = ProgressTimer::create(Sprite::createWithSpriteFrameName(PATH_UI_BOSS_HPBARBLOOD)); //血量条
	hpBarblood_B->setType(ProgressTimer::Type::BAR); //条形模式
	hpBarblood_B->setMidpoint(Point(0, 0.5f)); //进度条起始位置
	hpBarblood_B->setBarChangeRate(Point(1, 0)); //表示沿X轴变化
	hpBarblood_B->setPercentage(100);
	hpBarblood_B->setPosition(Point(0, 0));
	hpBarblood_B->setAnchorPoint(Point(0, 0));

	hpBar_B->addChild(hpBarblood_B);

	return;
}

void LabelLayer::pauseScene()
{
	//创建暂停菜单模糊背景
	pauseBackground = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(PATH_BACKGROUND_PAUSE));
	pauseBackground->setPosition(visibleSize / 2);
	addChild(pauseBackground);

	// 创建暂停界面主UI
	pauseMainUI = Sprite::create(PATH_BACKGROUND_DIALOG_PAUSE);
	pauseMainUI->setPosition(visibleSize / 2);
	addChild(pauseMainUI, 5);

	// 全体暂停，侦听器不处理
	Director::getInstance()->pause();
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(gamerlayer);

	// ESC返回游戏
	pauseListener = EventListenerKeyboard::create();
	pauseListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
		{
			resumeScene();
		}
	};

	// 创建返回游戏按钮
	auto resumeSprite = Sprite::create(PATH_UI_RESUME);
	auto resumeSprite2 = Sprite::create(PATH_UI_RESUME);
	resumeSprite2->setScale(0.98f);
	resume = MenuItemSprite::create(resumeSprite, resumeSprite2, [=](Ref* pSender){
		resumeScene();
	});
	resume->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 80);

	// 创建新游戏按钮
	auto newGameSprite = Sprite::create(PATH_UI_NEW);
	auto newGameSprite2 = Sprite::create(PATH_UI_NEW);
	newGameSprite2->setScale(0.9f);
	newGame = MenuItemSprite::create(newGameSprite, newGameSprite2, [=](Ref* pSender){
		resumeScene();
		Director::getInstance()->replaceScene(TransitionMoveInT::create(1, FinalWar::createScene()));
	});
	newGame->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// 创建调音乐的按钮
	auto musicSprite = Sprite::create(PATH_UI_MUSIC_ON);
	auto musicSprite2 = Sprite::create(PATH_UI_MUSIC_ON);
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

void LabelLayer::resumeScene()
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