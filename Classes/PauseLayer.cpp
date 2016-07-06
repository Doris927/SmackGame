#include"cocos2d.h"
#include"PauseLayer.h"
#include"StartLayer.h"
#include"GameLayer.h"
#include "SimpleAudioEngine.h"
#include "LevelLayer.h"
using namespace CocosDenshion;
PauseLayer::PauseLayer(void)
{}
 
PauseLayer::~PauseLayer(void)
{}
bool PauseLayer::init()
{
	bool bRet=false;
    do
    {
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		CCSprite* _background=CCSprite::create("pause_bg.png");
		_background->setAnchorPoint(ccp(0, 0));
        this->addChild( _background,0);

		

		CCMenuItemImage * _StartMenu1 = CCMenuItemImage::create("pause_home.png", "pause_home_down.png", this,menu_selector(PauseLayer::menuItem));
	    CCMenuItemImage * _StartMenu2 = CCMenuItemImage::create("pause_restart.png", "pause_restart_down.png", this,menu_selector(PauseLayer::restartItem));
		CCMenuItemImage * _StartMenu3 = CCMenuItemImage::create("pause_select.png", "pause_select_down.png", this,menu_selector(PauseLayer::selectItem));
		int heightItem =winSize.width*3/16;
	
		int xStart =winSize.width*21/64;
		int yStart =winSize.height-winSize.height*25/36;

		_StartMenu1->setPosition(ccp(0,0 ));
        _StartMenu2->setPosition(ccp(heightItem,0 ));
		_StartMenu3->setPosition(ccp(heightItem*2,0 ));
      
		
		CCMenu *menu = CCMenu::create(_StartMenu1, _StartMenu2,_StartMenu3,NULL);

        menu->setPosition(xStart, yStart);
        this->addChild(menu,0);



      bRet=true;
    } while (0);
	return bRet;
}
void   PauseLayer::menuItem(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCDirector::sharedDirector()->resume();
	CCScene *pScene =StartLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
void   PauseLayer::restartItem(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCDirector::sharedDirector()->resume();
	CCScene *pScene =GameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
void   PauseLayer::selectItem(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCDirector::sharedDirector()->resume();
	CCScene *pScene =LevelLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
