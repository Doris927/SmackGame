#include "HelloWorldScene.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    HelloWorld *layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,origin.y + pCloseItem->getContentSize().height/2));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello Gulang", "Arial", 24);
    
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(pSprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
