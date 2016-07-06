#pragma once
 
#include "cocos2d.h"
USING_NS_CC;
 
class LevelLayer : public CCLayer
{
private:
    CCMenu *menu;
   // CCArray * menumaneger;
public: 
	LevelLayer();
    ~ LevelLayer();
    CREATE_FUNC(LevelLayer);
    virtual bool init();
	
	void initlevel();
    static cocos2d::CCScene* scene();
	void setlevel(CCObject* pSender);
	/*void setlevel2(CCObject* pSender);
	void setlevel3(CCObject* pSender);
	void setlevel4(CCObject* pSender);
	void setlevel5(CCObject* pSender);
	void setlevel6(CCObject* pSender);
	void setlevel7(CCObject* pSender);
	void setlevel8(CCObject* pSender);
	void setlevel9(CCObject* pSender);
	void setlevel10(CCObject* pSender);
	void setlevel11(CCObject* pSender);
	void setlevel12(CCObject* pSender);
	void setlevel13(CCObject* pSender);
	void setlevel14(CCObject* pSender);
	void setlevel15(CCObject* pSender);
	void setlevel16(CCObject* pSender);
	void setlevel17(CCObject* pSender);
	void setlevel18(CCObject* pSender);
	void setlevel19(CCObject* pSender);
	void setlevel20(CCObject* pSender);*/



};