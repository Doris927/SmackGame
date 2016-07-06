#pragma once
 
#include "cocos2d.h"
USING_NS_CC;
 
class PauseLayer :public CCLayer
{
public:
     
    PauseLayer(void);
 
    ~PauseLayer(void);
 
    CREATE_FUNC(PauseLayer);
 
    virtual bool init();
	void  menuItem(CCObject* pSender);
    void  restartItem(CCObject* pSender);
	void selectItem(CCObject* pSender);
};
