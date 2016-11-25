#ifndef __FinalWar_H__
#define __FinalWar_H__

#include "cocos2d.h"
#include "Player.h"
#include "Boss.h"
#include "Monster.h"
#include "LabelLayer.h"
#include "Parameter.h"
#include "Factory.h"
#include "Observable.h"
#include "ilist.h"
USING_NS_CC;

class LabelLayer;

class FinalWar : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FinalWar);
public:
	FinalWar();

	void initBG();
	void initRole();
	void RollingBackground();
	void GameOver(bool win);
	void Fail();
	void Win();
	void Turn();
	void update(float delta);
	void MonsterAttack(float delta);
	void ReleaseMonster(MonsterType type);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize;
	static LabelLayer* labellayer;

	Sprite* backgroundOne;
	Sprite* backgroundTwo;

	Boss* zijian;
	Player* boat;
	ilist<Monster* > monsterArray;
	Player* dragon;
	Player* forset;
	Player* star;

	short turned; //画面是否旋转

	float time;
	short state; //战斗状态的英雄
	void Move(short x, short y);
	void Rotate(float delta);

	int monsterNum; //释放第几批小怪
};

#endif // __FinalWar_SCENE_H__
