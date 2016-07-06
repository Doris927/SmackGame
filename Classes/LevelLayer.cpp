#include"cocos2d.h"
#include"GameLayer.h"
#include "Global.h"
#include "LevelLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
LevelLayer::LevelLayer():menu(NULL)
{
}
LevelLayer::  ~ LevelLayer()
{
 }
CCScene* LevelLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    LevelLayer *layer = LevelLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool LevelLayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());

	    CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* _Background=CCSprite::create("xuanguan_bg.png");
		_Background->setPosition(ccp(size.width/2,size.height/2));
        this->addChild( _Background,0);

	
		initlevel();

        // 四个tu 一个开始菜单 两个辅助菜单 
		/*CCMenuItemImage*_StartMenu1 = CCMenuItemImage::create("a1.png", "a1_down.png",  "a1_no.png",this,menu_selector(LevelLayer::setlevel));
	    CCMenuItemImage*_StartMenu2 = CCMenuItemImage::create("a2.png", "a2_down.png",  "a2_down.png",this,menu_selector(LevelLayer::setlevel));
		CCMenuItemImage*_StartMenu3 = CCMenuItemImage::create("a3.png", "a3_down.png",  "a3_down.png", this,menu_selector(LevelLayer::setlevel));
		CCMenuItemImage*_StartMenu4 = CCMenuItemImage::create("a4.png", "a4_down.png",  "a4_down.png",this,menu_selector(LevelLayer::setlevel4));
	    CCMenuItemImage*_StartMenu5 = CCMenuItemImage::create("a5.png", "a5_down.png",  "a5_down.png",this,menu_selector(LevelLayer::setlevel5));
		CCMenuItemImage*_StartMenu6 = CCMenuItemImage::create("a6.png", "a6_down.png",  "a6_down.png", this,menu_selector(LevelLayer::setlevel6));
		CCMenuItemImage*_StartMenu7 = CCMenuItemImage::create("a7.png", "a7_down.png",  "a7_down.png",this,menu_selector(LevelLayer::setlevel7));
	    CCMenuItemImage*_StartMenu8 = CCMenuItemImage::create("a8.png", "a8_down.png",  "a8_down.png",this,menu_selector(LevelLayer::setlevel8));
		CCMenuItemImage*_StartMenu9 = CCMenuItemImage::create("a9.png", "a9_down.png",  "a9_down.png", this,menu_selector(LevelLayer::setlevel9));
		CCMenuItemImage*_StartMenu10= CCMenuItemImage::create("a10.png", "a10_down.png",  "a10_down.png",this,menu_selector(LevelLayer::setlevel10));
	    CCMenuItemImage*_StartMenu11= CCMenuItemImage::create("a11.png", "a11_down.png",  "a11_down.png",this,menu_selector(LevelLayer::setlevel11));
		CCMenuItemImage*_StartMenu12= CCMenuItemImage::create("a12.png", "a12_down.png",  "a12_down.png", this,menu_selector(LevelLayer::setlevel12));
		CCMenuItemImage*_StartMenu13= CCMenuItemImage::create("a13.png", "a13_down.png",  "a13_down.png",this,menu_selector(LevelLayer::setlevel13));
	    CCMenuItemImage*_StartMenu14= CCMenuItemImage::create("a14.png", "a14_down.png",  "a14_down.png",this,menu_selector(LevelLayer::setlevel14));
		CCMenuItemImage*_StartMenu15= CCMenuItemImage::create("a15.png", "a15_down.png",  "a15_down.png", this,menu_selector(LevelLayer::setlevel5));
		CCMenuItemImage*_StartMenu16= CCMenuItemImage::create("a16.png", "a16_down.png",  "a16_down.png",this,menu_selector(LevelLayer::setlevel16));
	    CCMenuItemImage*_StartMenu17= CCMenuItemImage::create("a17.png", "a17_down.png",  "a17_down.png",this,menu_selector(LevelLayer::setlevel17));
		CCMenuItemImage*_StartMenu18= CCMenuItemImage::create("a18.png", "a18_down.png",  "a18_down.png", this,menu_selector(LevelLayer::setlevel8));
		CCMenuItemImage*_StartMenu19= CCMenuItemImage::create("a19.png", "a19_down.png",  "a19_down.png",this,menu_selector(LevelLayer::setlevel19));
	    CCMenuItemImage*_StartMenu20= CCMenuItemImage::create("a20.png", "a20_down.png",  "a20_down.png",this,menu_selector(LevelLayer::setlevel20));*/
	
        bRet=true;

    } while (0);
    return bRet;
}
void LevelLayer::initlevel()
{
	menu = CCMenu::create();
	//menumaneger=CCArray::createWithCapacity(20);
	char tmp1[50],tmp2[50],tmp3[50];
	for(int i=0;i<20;i++)
	{	
        sprintf(tmp1, "select/a%d-01.png", i+1);
		sprintf(tmp2, "select/a%d_no-01.png", i+1);
		sprintf(tmp3, "select/a%d_down-01.png",i+1 );
	    CCMenuItemImage * Menu = CCMenuItemImage::create(tmp1,tmp2,tmp3,this,menu_selector(LevelLayer::setlevel)); 
		Menu->setEnabled(false);  
		//menumaneger->addObject(Menu);
		menu->addChild(Menu,i,i);
	}
	int level=Global::sharedGlobal()->highestlevel;
	for(int i=0;i<level;i++)
	{
		CCMenuItemImage *temp=(CCMenuItemImage*)menu->getChildByTag(i);
		temp->setEnabled(true);
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize(); 
	menu->setPosition(ccp(winSize.width/2,winSize.height/2));
	menu->alignItemsInColumns(5, 5,5,5, NULL); 
    this->addChild(menu,1);
}
void LevelLayer::setlevel(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCMenuItemImage* pMenuItem = (CCMenuItemImage *)(pSender);
	Global::sharedGlobal()->level=pMenuItem->getZOrder()+1;
	CCScene *pScene =GameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
/*
void LevelLayer::setlevel2(CCObject* pSender)
{
	Global::sharedGlobal()->level=2;

}
void LevelLayer::setlevel3(CCObject* pSender)
{
	Global::sharedGlobal()->level=3;
}
void LevelLayer::setlevel4(CCObject* pSender)
{
	Global::sharedGlobal()->level=4;
}
void LevelLayer::setlevel5(CCObject* pSender)
{
	Global::sharedGlobal()->level=5;

}
void LevelLayer::setlevel6(CCObject* pSender)
{
	Global::sharedGlobal()->level=6;
}
void LevelLayer::setlevel7(CCObject* pSender)
{
	Global::sharedGlobal()->level=7;

}
void LevelLayer::setlevel8(CCObject* pSender)
{
	Global::sharedGlobal()->level=8;
}void LevelLayer::setlevel9(CCObject* pSender)
{
	Global::sharedGlobal()->level=9;
}
void LevelLayer::setlevel10(CCObject* pSender)
{
	Global::sharedGlobal()->level=10;

}
void LevelLayer::setlevel11(CCObject* pSender)
{
	Global::sharedGlobal()->level=11;
}void LevelLayer::setlevel12(CCObject* pSender)
{
	Global::sharedGlobal()->level=12;
}
void LevelLayer::setlevel13(CCObject* pSender)
{
	Global::sharedGlobal()->level=13;

}
void LevelLayer::setlevel14(CCObject* pSender)
{
	Global::sharedGlobal()->level=15;
}void LevelLayer::setlevel15(CCObject* pSender)
{
	Global::sharedGlobal()->level=15;
}
void LevelLayer::setlevel16(CCObject* pSender)
{
	Global::sharedGlobal()->level=16;

}
void LevelLayer::setlevel17(CCObject* pSender)
{
	Global::sharedGlobal()->level=17;
}
void LevelLayer::setlevel18(CCObject* pSender)
{
	Global::sharedGlobal()->level=18;
}void LevelLayer::setlevel19(CCObject* pSender)
{
	Global::sharedGlobal()->level=19;
}
void LevelLayer::setlevel20(CCObject* pSender)
{
	Global::sharedGlobal()->level=20;
}*/