#include "HPBar.h"

HPBar::HPBar()
{
}

HPBar::HPBar(FigureType type)
{

}

bool HPBar::init()
{
	return true;
}

HPBar* HPBar::CreateWithInit(FigureType type)
{
	HPBar* bar = HPBar::create();
	Sprite* hpBar;
	switch (type)
	{
	case Boat:
		hpBar = Sprite::createWithSpriteFrameName(PATH_UI_PALYER_HPBAR); //������
		bar->hpBarblood = ProgressTimer::create(Sprite::createWithSpriteFrameName(PATH_UI_PALYER_HPBARBLOOD)); //Ѫ����
		hpBar->setPosition(210, Director::getInstance()->getVisibleSize().height - 46);
		break;
	case BOSS:
		hpBar = Sprite::createWithSpriteFrameName(PATH_UI_BOSS_HPBAR); //������
		bar->hpBarblood = ProgressTimer::create(Sprite::createWithSpriteFrameName(PATH_UI_BOSS_HPBARBLOOD)); //Ѫ����
		hpBar->setPosition(Director::getInstance()->getVisibleSize().width / 2, 46);
		break;
	default:
		break;
	}

	bar->addChild(hpBar, 1);

	bar->hpBarblood->setType(ProgressTimer::Type::BAR); //����ģʽ
	bar->hpBarblood->setMidpoint(Point(0, 0.5f)); //��������ʼλ��
	bar->hpBarblood->setBarChangeRate(Point(1, 0)); //��ʾ��X��仯
	bar->hpBarblood->setPercentage(100);
	bar->hpBarblood->setPosition(Point(0, 0));
	bar->hpBarblood->setAnchorPoint(Point(0, 0));

	hpBar->addChild(bar->hpBarblood);

	return bar;
}

void HPBar::SetType(FigureType type)
{
	_type = type;
}

FigureType HPBar::GetType()
{
	return _type;
}

void HPBar::Update(Observable* oba)
{
	hpBarblood->setPercentage(oba->ObservingData);
}