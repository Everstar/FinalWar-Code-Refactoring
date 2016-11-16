#ifndef __FinalWar_H__
#define __FinalWar_H__

#include "cocos2d.h"
#include "Player.h"
#include "Boss.h"
#include "Monster.h"
#include "LabelLayer.h"
#include "Parameter.h"
#include "Factory.h"
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
	void BossAttack(float delta);
	void MonsterAttack(float delta);
	void ReleaseMonster(MonsterType type, float scale, int atk, int life);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize;
	LabelLayer* labellayer;

	Sprite* backgroundOne;
	Sprite* backgroundTwo;

	Boss* zijian;
	Vector<Monster* > monsterArray;
	Player* boat;
	Player* dragon;
	Player* forset;
	Player* star;

	short turned; //�����Ƿ���ת
	bool leftright; //�ж�Boss�����ƶ�
	bool updown; //�ж�Boss�����ƶ�

	float time;
	short state; //ս��״̬��Ӣ��
	void Move(short x, short y);
	void Rotate(float delta);

	std::string monsterFile[5]; //С��ͼƬ��Դ
	int monsterNum; //�ͷŵڼ���С��
};

#endif // __FinalWar_SCENE_H__
