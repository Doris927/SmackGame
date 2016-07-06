#pragma once
 
#include "cocos2d.h"
USING_NS_CC;
 
class GameOver :public CCLayer
{
public:
     
    GameOver(void);
 
    ~GameOver(void);
 
    CREATE_FUNC(GameOver);
 
    virtual bool init();
   
	void updateHighestHistorySorce();
    static cocos2d::CCScene* scene();
	void AgainCallback(CCObject* pSender);
	void MenuCallback(CCObject* pSender);
	void SelectCallback(CCObject* pSender);
};
