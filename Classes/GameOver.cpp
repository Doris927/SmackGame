#include"GameOver.h"
#include"cocos2d.h"
#include"Global.h"
#include"StartLayer.h"
#include"GameLayer.h"
#include "SimpleAudioEngine.h"
#include "LevelLayer.h"
using namespace CocosDenshion;
GameOver::GameOver(void)
{}
 
GameOver::~GameOver(void)
{}
CCScene* GameOver::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameOver *layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool GameOver::init()
{
	bool bRet=false;
    do
    {
         CC_BREAK_IF(!CCLayer::init());
		 CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		 CCSprite* background=CCSprite::create("end_bg.png");
		 background->setAnchorPoint(ccp(0, 0));
         this->addChild( background,0);

		 updateHighestHistorySorce();

		 CCLabelBMFont*   scoreItem=CCLabelBMFont::create("0","number.fnt");	
		 scoreItem->setAnchorPoint(ccp(0,1));  
		 scoreItem->setPosition(ccp(winSize.width*5/9,winSize.height*26/45)); //gai位置
		 this->addChild(scoreItem,1); 
		 CCString* strScore=CCString::createWithFormat("%d",Global::sharedGlobal()->score);//格式化为字符串  
         scoreItem->setString(strScore->m_sString.c_str());

		 
		 CCLabelBMFont*   levelItem=CCLabelBMFont::create("0","number.fnt");	
		 levelItem->setAnchorPoint(ccp(0,1));  
		 levelItem->setPosition(ccp(winSize.width*11/18,winSize.height*2/5)); //gai位置
		 this->addChild(levelItem,1); 
		 CCString* strLevel=CCString::createWithFormat("%d",Global::sharedGlobal()->level);//格式化为字符串  
         levelItem->setString(strLevel->m_sString.c_str());

		 CCLabelBMFont*   bestscoreItem=CCLabelBMFont::create("0","number.fnt");	
		 bestscoreItem->setAnchorPoint(ccp(0,1));  
		 bestscoreItem->setPosition(ccp(winSize.width*25/64,winSize.height*2/5)); 
		 this->addChild(bestscoreItem,1); 
		 CCString* strbestScore=CCString::createWithFormat("%d",Global::sharedGlobal()->highestscore);//格式化为字符串  
         bestscoreItem->setString(strbestScore->m_sString.c_str());


		CCSprite* normalAgain=CCSprite::create("restart.png");  
		CCSprite* pressedAgain=CCSprite::create("restart_down.png");  
		CCSprite* normalMenu=CCSprite::create("home.png");  
		CCSprite* pressedMenu=CCSprite::create("home_down.png");  
		CCSprite* normalSelect=CCSprite::create("select.png");  
		CCSprite* pressedSelect=CCSprite::create("select_down.png");  

        CCMenuItemImage * pAgainItem=CCMenuItemImage::create(); 
        CCMenuItemImage * pMenuItem=CCMenuItemImage::create(); 
		CCMenuItemImage * pSelectItem=CCMenuItemImage::create(); 

		pAgainItem->initWithNormalSprite(normalAgain,pressedAgain,NULL,this,menu_selector(GameOver::AgainCallback));//载入双态图和回调函数 
		pMenuItem->initWithNormalSprite(normalMenu,pressedMenu,NULL,this,menu_selector(GameOver::MenuCallback));
		pSelectItem->initWithNormalSprite(normalSelect,pressedSelect,NULL,this,menu_selector(GameOver::SelectCallback));

		int heightItem =winSize.width*3/16;
		int xStart =winSize.width*5/16;
		int yStart =winSize.height*23/100;

		pAgainItem->setPosition(ccp(0,0 ));
		pMenuItem->setPosition(ccp(heightItem,0 ));
	    pSelectItem->setPosition(ccp(heightItem*2,0 ));

		CCMenu *menu=CCMenu::create(pMenuItem,pAgainItem,pSelectItem,NULL);//创建CCMenu，可以这么理解CCMenuItem是CCMenu的孩子  
		//menuPause->setPosition(ccp(winSize.width/2,winSize.height));  
		menu->setPosition(ccp(xStart,yStart));  
        this->addChild(menu,1);  

		//updateHighestHistorySorce();

      bRet=true;
    } while (0);
	return bRet;
}
void GameOver::AgainCallback(CCObject* pSender)
{	
	Global::sharedGlobal()->score=0;
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCScene *pScene =GameLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
void GameOver::MenuCallback(CCObject* pSender)
{	
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCScene *pScene =StartLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}
void GameOver::SelectCallback(CCObject* pSender)
{	
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCScene *pScene =LevelLayer::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.5, pScene));
}

void GameOver::updateHighestHistorySorce()  
{  
         
		  if( Global::sharedGlobal()->score> Global::sharedGlobal()->highestscore)
		  {
			  Global::sharedGlobal()->highestscore= Global::sharedGlobal()->score;
			  CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestScore", Global::sharedGlobal()->highestscore);//修改存档  

		  } 
		  if( Global::sharedGlobal()->level> Global::sharedGlobal()->highestlevel)
		  {
			   Global::sharedGlobal()->highestlevel= Global::sharedGlobal()->level;
			   CCUserDefault::sharedUserDefault()->setIntegerForKey("HighestLevel", Global::sharedGlobal()->highestlevel);
		  }
}  