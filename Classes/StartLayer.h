//StartScene.h
#pragma once
 
#include "cocos2d.h"
USING_NS_CC;
 
class StartLayer : public CCLayer
{
public:
     
    StartLayer();
    ~ StartLayer();
    CREATE_FUNC(StartLayer);
    virtual bool init();
    static cocos2d::CCScene* scene();
	void newgame(CCObject* pSender);
	void help(CCObject* pSender);
	bool isHaveSaveFile();
	void getHighestHistory();
};