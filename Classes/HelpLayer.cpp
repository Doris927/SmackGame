#include"cocos2d.h"
#include"StartLayer.h"
#include "HelpLayer.h"
HelpLayer::HelpLayer(void)
{}
 
HelpLayer::~HelpLayer(void)
{}
CCScene* HelpLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelpLayer *layer = HelpLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool HelpLayer::init()
{
	bool bRet=false;
    do
    {
         CC_BREAK_IF(!CCLayer::init());
		 CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		 CCSprite* background=CCSprite::create("help_bg.png");
		 background->setAnchorPoint(ccp(0, 0));
         this->addChild( background,0);

		CCMenuItemImage * menuReturntemp = CCMenuItemImage::create("back.png", "back.png",this,menu_selector(HelpLayer::menuPauseCallback));
        CCMenu *menuReturn=CCMenu::create(menuReturntemp,NULL);//创建CCMenu，可以这么理解CCMenuItem是CCMenu的孩子  
	
		menuReturn->setPosition(winSize.width/20+menuReturntemp->getContentSize().width/2,winSize.height*19/20-menuReturntemp->getContentSize().height/2);  
        this->addChild(menuReturn,1);  


      bRet=true;
    } while (0);
	return bRet;
}
void HelpLayer::menuPauseCallback(CCObject* pSender)
{
	CCScene *pScene =StartLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}