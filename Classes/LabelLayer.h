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

	float score; //·ÖÊý

	void CreateHPLabel();

	bool flagPause;
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