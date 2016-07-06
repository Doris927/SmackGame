//UnitSprite.h
#pragma once
 
#include "cocos2d.h"
USING_NS_CC;

class UnitSprite:public CCNode
{
private:
	CCSprite *m_sprite;
	int m_state;//0 °²È« 1Î£ÏÕ 

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