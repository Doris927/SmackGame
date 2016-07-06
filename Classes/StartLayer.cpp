//StartLayer.cpp
#include"cocos2d.h"
#include"StartLayer.h"
#include"GameLayer.h"
#include "Global.h"
#include "SimpleAudioEngine.h"
#include "HelpLayer.h"
#include "LevelLayer.h"
using namespace CocosDenshion;
StartLayer::StartLayer()
{
}
StartLayer::  ~ StartLayer()
{
 }
CCScene* StartLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartLayer *layer = StartLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool StartLayer::init()
{
    bool bRet=false;
    do
    {
        CC_BREAK_IF(!CCLayer::init());
		//_Level=1;
        //初始动画 进入开始菜单界面
		//firstanimation();
		//包括一张背景 
	    CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* _Background=CCSprite::create("start_bg.png");
		_Background->setPosition(ccp(size.width/2,size.height/2));
        this->addChild( _Background,0);

		getHighestHistory();
        // 四个tu 一个开始菜单 两个辅助菜单 
		CCMenuItemImage * _StartMenu4 = CCMenuItemImage::create("bt.png", "bt_down.png", this,menu_selector(StartLayer::newgame));
		CCMenuItemImage * _StartMenu5 = CCMenuItemImage::create("blank.png", "blank.png", this,menu_selector(StartLayer::help));



		CCMenu *menu = CCMenu::create( _StartMenu4,NULL);
		CCMenu *menu2 = CCMenu::create(_StartMenu5,NULL);

        menu->setPosition(size.width*51/64-_StartMenu4->getContentSize().width/2,size.height*5/18-_StartMenu4->getContentSize().height/3);
        this->addChild(menu,1);
		menu2->setPosition(ccp(size.width-_StartMenu5->getContentSize().width/2,_StartMenu5->getContentSize().height/2));
		this->addChild(menu2,1);



		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/go.wav");  
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/life.wav");  
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/over.wav");  
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/start.wav");    
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/anniu.wav");  
		SimpleAudioEngine::sharedEngine()->preloadEffect("sound/down.wav");  
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/ground.wav");  
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/ground.wav",true);
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.1);

		
        bRet=true;

    } while (0);
    return bRet;
}
void StartLayer::newgame(CCObject* pSender)
{
	//切换到游戏场景
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCScene *pScene =LevelLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}

void StartLayer::help(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCScene *pScene =HelpLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
 bool StartLayer::isHaveSaveFile()//判断存档是否存在  
{  
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("isHaveSaveFileXml"))//通过设置的bool型标志位判断，如果不存在  
    {  
        CCUserDefault::sharedUserDefault()->setBoolForKey("isHaveSaveFileXml", true);//写入bool判断位  
        CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore",0);//写入初始分数0  
		CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestLevel",1);
        CCUserDefault::sharedUserDefault()->flush();//设置完一定要调用flush，才能从缓冲写入io  
        return false;  
    }  
    else  
    {  
        return true;  
    }  
}  
 void StartLayer::getHighestHistory()  
{  
    if (isHaveSaveFile())//如果存在存档  
    {  
		Global::sharedGlobal()->highestscore =CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestScore",0);
		Global::sharedGlobal()->highestlevel =CCUserDefault::sharedUserDefault()->getIntegerForKey("HighestLevel",0);//读取历史最高分
    }  
}  
