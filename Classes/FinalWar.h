#ifndef __FinalWar_H__
#define __FinalWar_H__

#include "cocos2d.h"
#include "Boss_Hero.h"
#include "Boss.h"
#include "Boss_Monster.h"
#include "Boss_LabelLayer.h"
USING_NS_CC;

class Boss_LabelLayer;

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
	void Fail();
	void Win();
	void Turn();
	void update(float delta);
	void BossAttack(float delta);
	void MonsterAttack(float delta);
	void ReleaseMonster(const std::string &filename, float scale, int atk, int life);
	void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
private:
	Size visibleSize;
	Boss_LabelLayer* labellayer;

	Sprite* backgroundOne;
	Sprite* backgroundTwo;

	Boss* zijian;
	Vector<Boss_Monster* > monsterArray;
	Boss_Hero* boat;
	Boss_Hero* huolong;
	Boss_Hero* sensen;
	Boss_Hero* littlestar;

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
