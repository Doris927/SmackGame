#pragma once
 
#include "cocos2d.h"
USING_NS_CC;
 
class HelpLayer :public CCLayer
{
public:
     
    HelpLayer(void);
 
    ~HelpLayer(void);
 
    CREATE_FUNC(HelpLayer);
 
    virtual bool init();

    static cocos2d::CCScene* scene();

	void menuPauseCallback(CCObject* pSender);
};