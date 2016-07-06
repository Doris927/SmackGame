//UnitSprite.h
#pragma once
 
#include "cocos2d.h"
USING_NS_CC;

class UnitSprite:public CCNode
{
private:
	CCSprite *m_sprite;
	int m_state;//0 ��ȫ 1Σ�� 

public:
    UnitSprite();
    ~UnitSprite(); 
	static UnitSprite * create();
	void bindSprite(CCSprite *sprite,int state);
	CCSprite* getSprite();
	int getState();
	void changeState();
	CCRect getBoundingBox();

};