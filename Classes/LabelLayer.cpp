#include "LabelLayer.h"
#include "FinalWar.h"
#include "Parameter.h"
#include "SimpleAudioEngine.h"
using CocosDenshion::SimpleAudioEngine;

bool LabelLayer::init()
{
	if (!Layer::init())
		return false;
	
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_HURTANIMATION_FIRE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_HURTANIMATION_LASER);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_HURTANIMATION_ICE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_HURTANIMATION_BOMB);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BOSSBACK_MAGICCIRCLE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BULLET_FIRE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BULLET_ICE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_BULLET_LASER);
	Director::getInstance()->getTextureCache()->addImage(PATH_BULLET_SIZE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_PLAYER_FIGURE);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_MONSTER_FIGURE);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_UI_HPLABEL);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PATH_UI_MENUITEM);
	Director::getInstance()->getTextureCache()->addImage(PATH_BACKGROUND_PAUSE);
	Director::getInstance()->getTextureCache()->addImage(PATH_BACKGROUND_FORMER);
	Director::getInstance()->getTextureCache()->addImage(PATH_BACKGROUND_LATTER);

	SimpleAudioEngine::getInstance()->preloadEffect(PATH_AUDIO_FIRE);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_AUDIO_ICE);
	SimpleAudioEngine::getInstance()->preloadEffect(PATH_AUDIO_LASER);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(PATH_AUDIO_BACKGROUND);

	visibleSize = Director::getInstance()->getVisibleSize();

	flagPause = true;
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
			flagPause = false;
			pauseScene();
		}
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);
	this->initMusic();

	return true;
}

void LabelLayer::SetScore(float grade)
{
	this->score = grade;
}

float LabelLayer::GetScore()
{
	return score;
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
}

void LabelLayer::MusicOn(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->resumeBackgroundMusic();
	musicOnLabel->setEnabled(false);
	musicOnLabel->setVisible(false);
	musicOffLabel->setEnabled(true);
	musicOffLabel->setVisible(true);
}

void LabelLayer::MusicOff(Ref* ref)
{
	auto engine = SimpleAudioEngine::getInstance();
	engine->pauseBackgroundMusic();
	musicOnLabel->setEnabled(true);
	musicOnLabel->setVisible(true);
	musicOffLabel->setEnabled(false);
	musicOffLabel->setVisible(false);
}

void LabelLayer::CreateHPLabel() //血量条
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	hpPlayer = HPBar::CreateWithInit(FigureType::Boat);
	this->addChild(hpPlayer, 1);

	hpBoss = HPBar::CreateWithInit(FigureType::BOSS);
	this->addChild(hpBoss, 1);
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
	pauseListener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event *e){
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE && !flagPause)
			resumeScene();
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
	music = MenuItemSprite::create(musicSprite, musicSprite2, [&](Ref* pSender){
		if (flagMusic)
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		else
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		flagMusic = !flagMusic;
	});
	music->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 150);

	menu = Menu::create(resume, music, newGame, nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 6);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pauseListener, this);
}

void LabelLayer::resumeScene()
{
	removeChild(pauseMainUI);
	removeChild(pauseBackground);
	removeChild(menu);
	flagPause = true;
	Director::getInstance()->resume();
	Director::getInstance()->getEventDispatcher()->removeEventListener(pauseListener);
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(gamerlayer);
}