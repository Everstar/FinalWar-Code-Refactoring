#ifndef __LABELLAYER_H__
#define __LABELLAYER_H__

#include "cocos2d.h"
#include "HPBar.h"
USING_NS_CC;

class LabelLayer : public Layer
{
public:
	bool init();
	void pauseScene();
	void resumeScene();
	CREATE_FUNC(LabelLayer);
public:
	Layer* gamerlayer;

	void SetScore(float grade);
	float GetScore();

	void update(float delta);

	void MusicOn(Ref* ref);
	void MusicOff(Ref* ref);
	void initMusic();

	HPBar* hpPlayer;
	HPBar* hpBoss;
private:
	Size visibleSize;

	MenuItemImage* musicOnLabel;
	MenuItemImage* musicOffLabel;
	Menu* musicMenu;

	//Player* hero;
	//Boss* boss;

	float score; //����

	//Ѫ��
	ProgressTimer* hpBarblood_H;
	Sprite* hpBar_H;

	ProgressTimer* hpBarblood_B;
	Sprite* hpBar_B;

	void CreateHPLabel();

	bool flagPause;
	bool flagResume;
	bool flagMusic;

	Sprite* pauseMainUI;
	Sprite* pauseBackground;

	MenuItemSprite* resume;
	MenuItemSprite* music;
	MenuItemSprite* newGame;
	Menu* menu;
	EventListenerKeyboard* pauseListener;
};




#endif