//GameLayer.cpp
#include"cocos2d.h"
#include"GameLayer.h"
#include"UnitSprite.h"
#include"Global.h"

#include "GameOver.h"
#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
/*GameLayer::GameLayer():m_score(0),m_hp(5),m_level(1),m_lbScore(NULL),m_lifeCount(NULL),m_allGreen(NULL),m_allOrange(NULL)
{   
}*/
CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
GameLayer::GameLayer(): scoreItem(NULL),m_score( Global::sharedGlobal()->score),m_life(3),m_level( Global::sharedGlobal()->level),cache(NULL),pPauseItem(NULL),m_allOrgreen(NULL),m_allGreen(NULL),m_allOrange(NULL),m_allBlue(NULL),m_allYellow(NULL),m_allBY(NULL),m_allDirty(NULL),m_tempscore(0)
{   
}

GameLayer::~GameLayer()
{
    
    m_allOrange->release();
    m_allGreen->release();
    m_allYellow->release();
    m_allBlue->release();  
	m_allDirty->release();
	m_allOrgreen->release();
	m_allBY->release();

	m_allOrange=NULL;
	m_allGreen=NULL;
    m_allYellow=NULL;
    m_allBlue=NULL;
	m_allDirty=NULL;
	m_allOrgreen=NULL;
    m_allBY=NULL;
   
}

bool GameLayer::init()
{
	
    bool bRet=false;
    do
    {
         CC_BREAK_IF(!CCLayer::init());

         this->setTouchEnabled(true);

		 cc_timeval psv;
         CCTime::gettimeofdayCocos2d(&psv, NULL);
         unsigned long int seed = psv.tv_sec*1000 + psv.tv_usec/1000;
         srand(seed);
		
		

		 m_allOrange=CCArray::create();
		 m_allOrange->retain();
		 m_allGreen=CCArray::create();
		 m_allGreen->retain();
	     m_allYellow=CCArray::create();
		 m_allYellow->retain();
		 m_allBlue=CCArray::create();
		 m_allBlue->retain();
		 m_allDirty=CCArray::create();
		 m_allDirty->retain();
		 m_allOrgreen=CCArray::create();
		 m_allOrgreen->retain();
		 m_allBY=CCArray::create();
	     m_allBY->retain();

		 cache = CCSpriteFrameCache::sharedSpriteFrameCache();
         cache->addSpriteFramesWithFile("final.plist","final.png"); 
		 cache->addSpriteFramesWithFile("level.plist","level.png"); 
    
		 initBackground();

         bRet=true;
    } while (0);
	 return bRet;
}
void GameLayer::registerWithTouchDispatcher()  
{  
    CCDirector *pDirector=CCDirector::sharedDirector();  
    pDirector->getTouchDispatcher()->addTargetedDelegate(this,0,true);  
}  
bool GameLayer::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
	CCPoint point=this->convertTouchToNodeSpace(touch);
    CCObject* obj;  
	CCARRAY_FOREACH(m_allBY,obj)  
    {  
		   UnitSprite* by=(UnitSprite*)obj;  
	       CCRect  rect=by->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		      bybetouched(by);
			  return true;
		   }  
     }	
    CCARRAY_FOREACH(m_allOrange,obj)  
    {  
		   UnitSprite* orange=(UnitSprite*)obj;  
	       CCRect  rect=orange->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		      orangebetouched(orange);
			  return true;
		   }  
     }	
	   CCARRAY_FOREACH(m_allGreen,obj)  
       {  
		   UnitSprite* green=(UnitSprite*)obj;  
	       CCRect  rect=green->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		      greenbetouched(green);
			  return true;
		   }  
       }	
	  CCARRAY_FOREACH(m_allDirty,obj)  
       {  
		   UnitSprite* dirty=(UnitSprite*)obj;  
	       CCRect  rect=dirty->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		      dirtybetouched(dirty);
			  return true;
		   }  
        }	
	   CCARRAY_FOREACH(m_allOrgreen,obj)  
     {  
		   UnitSprite* orgreen=(UnitSprite*)obj;  
	       CCRect  rect=orgreen->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		     orgreenbetouched(orgreen);
			  return true;
		   }  
      }	
	 CCARRAY_FOREACH(m_allBlue,obj)  
    {  
		   UnitSprite* blue=(UnitSprite*)obj;  
	       CCRect  rect=blue->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		      bluebetouched(blue);
			  return true;
		   }  
     }	
	 	 CCARRAY_FOREACH(m_allYellow,obj)  
    {  
		   UnitSprite* yellow=(UnitSprite*)obj;  
	       CCRect  rect=yellow->getBoundingBox();
	       if(rect.containsPoint(point)==true) 
	       {
		     yellowbetouched(yellow);
			  return true;
		   }  
     }	

	return true;
}  
void GameLayer::greenbetouched(void * data)
{
	 UnitSprite* green=(UnitSprite*)data;  
     if (green!=NULL)  
	 {
		
	    SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		green->getSprite()->stopAllActions();
		CCArray *frames_go =CCArray::create();
		char tmp[50];
		int j=CCRANDOM_0_1()*2+1;
            sprintf(tmp, "green_smack%d.png", j);
			CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			frames_go->addObject(frame);
		CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		CCAnimate *animate_go = CCAnimate::create(animation_go);

        CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeGreen),(void *)green),NULL);
		green->getSprite()->runAction(_Seq);
		updateScore();
	 }
}
void GameLayer::orangebetouched(void * data)
{
	 UnitSprite* orange=(UnitSprite*)data;  
     if (orange!=NULL)  
	 {
	
		SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		orange->getSprite()->stopAllActions();
		CCArray *frames_go =CCArray::create();
		char tmp[50];
		int j=CCRANDOM_0_1()*3+1;
		    sprintf(tmp, "org_smack%d.png",j);
			CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			frames_go->addObject(frame);
		
		CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		CCAnimate *animate_go = CCAnimate::create(animation_go);

		CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeOrange),(void *)orange),NULL);
		orange->getSprite()->runAction(_Seq); 
	    updateScore();
	 }
}
void GameLayer::dirtybetouched(void * data)   
{ 
	 UnitSprite* dirty=(UnitSprite*)data;  
     if (dirty!=NULL)  
	 {
		updateLife();
		dirty->getSprite()->stopAllActions();
		CCArray *frames_go =CCArray::create();
		char tmp[50];
		int j=CCRANDOM_0_1()*3+1;
			sprintf(tmp, "spot_smack%d.png",j);
			CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			frames_go->addObject(frame);
		
		CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		CCAnimate *animate_go = CCAnimate::create(animation_go);
	    CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeDirty),(void *)dirty),NULL);
		dirty->getSprite()->runAction(_Seq);
	 }
}
void GameLayer::bluebetouched(void *data)
{
	 UnitSprite* blue=(UnitSprite*)data;  
     if (blue!=NULL)  
	 {
		
		  SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		blue->getSprite()->stopAllActions();
		CCArray *frames_go =CCArray::create();
		char tmp[50];
		int j=CCRANDOM_0_1()*2+1;

			sprintf(tmp, "blue_smack%d.png",j);
			CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			frames_go->addObject(frame);
		
		CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		CCAnimate *animate_go = CCAnimate::create(animation_go);

        CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeBlue),(void *)blue),NULL);
		blue->getSprite()->runAction(_Seq);
		updateScore();
	 }
}
void GameLayer::yellowbetouched(void *data)
{
	 UnitSprite* yellow=(UnitSprite*)data;  
     if (yellow!=NULL)  
	 {
		
		  SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		yellow->getSprite()->stopAllActions();
		CCArray *frames_go =CCArray::create();
		char tmp[50];
		int j=CCRANDOM_0_1()*2+1;
			sprintf(tmp, "yel_smack%d.png",j);
			CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			frames_go->addObject(frame);
		
		CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		CCAnimate *animate_go = CCAnimate::create(animation_go);

        CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeYellow),(void *)yellow),NULL);
		yellow->getSprite()->runAction(_Seq);
		updateScore();
	 }

}
void GameLayer::bybetouched(void *data)
{
	 UnitSprite* by=(UnitSprite*)data;  
     if (by!=NULL)  
	 {
		SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		by->getSprite()->stopAllActions();
		CCPoint point=by->getPosition();
		addBlue(point);
		addYellow(point);
        removeBY(NULL,by);
		this->removeChild(by,true);
	 }
} 
void GameLayer::orgreenbetouched(void *data)
{
	 UnitSprite* orgreen=(UnitSprite*)data;  
     if (orgreen!=NULL)  
	 {
		 if(orgreen->getState()==0)
		 {
		
			   SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
		     orgreen->getSprite()->stopAllActions();
		     CCArray *frames_go =CCArray::create();
		     char tmp[50];
		     int j=CCRANDOM_0_1()*2+1;
			      sprintf(tmp, "orgreen_smack%d.png",j);
			      CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
			      frames_go->addObject(frame);
		
		    CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
		    CCAnimate *animate_go = CCAnimate::create(animation_go);

            CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::removeOrgreen),(void *)orgreen),NULL);
		    orgreen->getSprite()->runAction(_Seq);
				 updateScore();
		 }
		 else
		 {
			  orgreen->changeState();
			  orgreen->getSprite()->stopAllActions();
			    SimpleAudioEngine::sharedEngine()->playEffect("sound/over.wav",false);
			  char tmp[50];
		   CCArray *frames_go =CCArray::create();
           sprintf(tmp, "orgre1.png");
           CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
           frames_go->addObject(frame);
         
	      CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.1f);
	      CCAnimate *animate_go = CCAnimate::create(animation_go);
			
		 	 orgreen->getSprite()->runAction(animate_go);
			 CCSequence *_Seq = CCSequence::create(CCDelayTime::create(2.0f),CCCallFuncND::create(this, callfuncND_selector(GameLayer::resumeOrgreen),(void *)orgreen),NULL);
			 orgreen->getSprite()->runAction(_Seq);
		 }
	 }
}

void GameLayer::resumeOrgreen(CCNode* pTarget, void* data)
{
	 UnitSprite* orgreen=(UnitSprite*)data;  
     if (orgreen!=NULL)  
	 {
		  orgreen->changeState();
		  CCArray *frames_go =CCArray::create();
		  char tmp[50];
		  for (int j = 1; j < 12; j++)
         {
           sprintf(tmp, "orgre%d.png", j);
           CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
           frames_go->addObject(frame);
         }
	     CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	     CCAnimate *animate_go = CCAnimate::create(animation_go);

	     CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::orgreenuntouched),(void *)orgreen),NULL);
	     orgreen->getSprite()->runAction(_Seq);
	 }
}
void GameLayer::setgame(float dt)
{
	int gailv= CCRANDOM_0_1()*9+1;
    switch(m_level)
	{	
		case 1:
		    addGreen();
			break;
		case 2:
			switch(gailv)
				{
				case 1: case 2: case 3:case 7:case 8:case 6: case 4:
				    addGreen();
				    break;
			    case 10:case 9:case 5: 
				    addDirty();
                    break;
				}
		break;
		case 3:
				switch(gailv)
				{
			    case 1: case 2: case 8: case 10:case 9:case 5:case 7:
				    addGreen();
				    break;
			    case 6: case 4:case 3:
				    addOrange();
                    break;
				}
		break;
		case 4:
				switch(gailv)
				{
			    case 1: case 2: case 8:  case 10:
				    addGreen();
				    break; 
				case 3:case 7:case 5:case 9: 
					 addOrange();
					break;
				case 4:case 6:
					addDirty();
					break;
				}
		break;
		case 5:
				switch(gailv)
				{
			    case 1: case 2: case 8:  case 10:case 5:case 3:case 7:
				    addGreen();
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				}
		break;
		case 6:
			switch(gailv)
				{
			    case 1: case 2: case 8:  case 10:case 7:
				    addGreen();
				    break;
			    case 4:case 9:
					addDirty();
					break;
				case 6:case 5:case 3:
					addOrgreen();
					break;
				}
		break;
		case 7:
			switch(gailv)
				{
			    case 1: case 2: case 8:  case 4:case 9: case 10:case 3:
				    addGreen();
				    break;
				case 6:case 5:case 7:
					addBY();
					break;
				}
		break;
		case 8:
			switch(gailv)
				{
			    case 1: case 2: case 8: case 6:case 5:
				    addGreen();
				    break;
			    case 4:case 9: case 10:
					addBY();
					break;
				case 3:case 7:
					addDirty();
					break;
				}
		break;
		case 9:
			switch(gailv)
				{
			    case 1: case 2: case 8: case 5:
				    addGreen();
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 3:case 7:	case 10:
					addOrgreen();
					break;
				}
		break;
		case 10:
			switch(gailv)
				{
			    case 1: case 2: case 8: 
				    addGreen();
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 3:case 7:	
					addOrgreen();
					break;
				case 5:case 10:
					addDirty();
					break;
				}
		break;
		case 11:
			switch(gailv)
				{
			    case 1: case 2: case 8: 
				    addGreen();
				    break;
			    case 4:case 9:case 6:case 7:	
					addOrange();
					break;
				case 3:
					addOrgreen();
					break;
				case 5:case 10:
					addBY();
					break;
				}
		break;
		case 12:
			switch(gailv)
				{
			    case 1: case 2: 
				    addGreen();
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 3:
					addOrgreen();
					break;
				case 5:case 10:
					addBY();
					break;
				case 7:	case 8: 
					addDirty();
					break;
				}
		break;
		case 13:
			switch(gailv)
				{
			    case 1: case 2: case 3:
				    addGreen();
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 5:case 10:
					addBY();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
				}
		break;
		case 14:
			switch(gailv)
				{
			    case 1: case 2:
				    addGreen();
				    break;
			    case 4:case 9:
					addOrange();
					break;
				case 5:case 10:
					addBY();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
				case 6:	case 3:
					addDirty();
					break;
				}
		break;
		case 15:
			switch(gailv)
			{
			    case 1: case 2: case 3:
				    addGreen();	
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 5:case 10:
					addBY();addDirty();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
			}
	  break;
	  case 16:
			switch(gailv)
				{
			    case 1: case 2:
				    addGreen();addDirty();
				    break;
			    case 4:case 9:
					addOrange();
					break;
				case 5:case 10:
					addBY();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
				case 6:	case 3:
					addDirty();
					break;
				}
	  break;
	  case 17:
			switch(gailv)
			{
			    case 1: case 2: case 3:
				    addGreen();	
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 5:case 10:
					addBY(); addGreen();	
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
			}
	  break;
	  case 18:
			switch(gailv)
				{
			    case 1: case 2:
				    addGreen();addDirty();
				    break;
			    case 4:case 9:
					addOrange();
					break;
				case 5:case 10:
					addBY();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
				case 6:	case 3:
					addDirty(); addGreen();
					break;
				}
	  break;
	  case 19:
			switch(gailv)
			{
			    case 1: case 2: case 3:
				    addGreen();	
				    break;
			    case 4:case 9:case 6:
					addOrange();
					break;
				case 5:case 10:
					addBY(); 	
					break;
				case 7:	case 8: 
				    addOrgreen();addOrange();
					break;
			
			}
	  break;
	  case 20:
			switch(gailv)
				{
			    case 1: case 2:
				    addGreen();
				    break;
			    case 4:case 9:
					addOrange();
					break;
				case 5:case 10:
					addBY(); addGreen();
					break;
				case 7:	case 8: 
				    addOrgreen();
					break;
				case 6:	case 3:
					addDirty();addOrange();
					break;
				}
	  break;
	}	

}
void GameLayer::startgame(CCNode *pSender,void * data)
{	 
	     CCNode *child=(CCNode *)data;
	     this->removeChild(child,true);
		 if(m_level%2==1)
	     {
			float temp=8.0f+m_level-1;
			float g=8.0/temp;
			this->schedule(schedule_selector(GameLayer::setgame),g,kCCRepeatForever,0.0f); 
		 }
		 else
		 {
			float temp=12.0f+(m_level-1);
			float g=8.0/temp;
			this->schedule(schedule_selector(GameLayer::setgame),g,kCCRepeatForever,0.0f); 
		 }
}
void GameLayer::gameover()
{
	//removeAllUnitSprite();
	this->removeAllChildrenWithCleanup(true);
	this->unschedule(schedule_selector(GameLayer::setgame)); 
	//this->unschedule(schedule_selector(GameLayer::addGreen)); 
	//this->unschedule(schedule_selector(GameLayer::addDirty)); 
	Global::sharedGlobal()->score=m_score;
	Global::sharedGlobal()->level=m_level;
	//切到结束场景
	CCScene *pScene =GameOver::scene();

    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInB::create(0.2, pScene));
}
void GameLayer::levelup()
{
	
	cleanup();
	this->removeAllChildrenWithCleanup(true);
	removeAllUnitSprite();
	m_level++;
	m_life=3;
	m_tempscore=0;
	initBackground();

}
/* GameLayer::frequp()
{
	m_freq++;

    this->unschedule(schedule_selector(GameLayer::setgame)); 
	float temp=10.0f+(m_level-1)+(m_freq-1);
    float g=10/temp;

	this->schedule(schedule_selector(GameLayer::setgame),g,kCCRepeatForever,0.0f);

}*/
void GameLayer::initBackground()
{
		 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		 //背景
		 CCSprite* _background=CCSprite::create("game_bg.png");
		 _background->setAnchorPoint(ccp(0, 0));
         this->addChild( _background,0);

		 //score
		 
		 scoreItem=CCLabelBMFont::create("0","number.fnt");//scoreItem是CCLabelBMFont*型成员变量，这里采用了自定义的字体，相关资源在第一篇有给出了  
    
         scoreItem->setAnchorPoint(ccp(0,1));  
		 scoreItem->setPosition(ccp(winSize.width*23/32,winSize.height*15/16));  

         this->addChild(scoreItem,1); 
		 CCString* strScore=CCString::createWithFormat("%d",m_score);//格式化为字符串  
         scoreItem->setString(strScore->m_sString.c_str());//从CCString中获得char*,更新分数 

		 //level
		 levelItem=CCLabelBMFont::create("0","number.fnt");//scoreItem是CCLabelBMFont*型成员变量，这里采用了自定义的字体，相关资源在第一篇有给出了  

         levelItem->setAnchorPoint(ccp(0,1));  
		 levelItem->setPosition(ccp(winSize.width*1/2,winSize.height*15/16));  
         this->addChild(levelItem,1); 
		 CCString* strLevel=CCString::createWithFormat("%d",m_level);//格式化为字符串  
         levelItem->setString(strLevel->m_sString.c_str());//从CCString中获得char*,更新分数 

		 
		//暂停菜单

		CCSprite* normalPause=CCSprite::create("game_bt_stop.png");  
		CCSprite* pressedPause=CCSprite::create("game_bt_start.png");  
        pPauseItem=CCMenuItemImage::create(); 
		pPauseItem->initWithNormalSprite(normalPause,pressedPause,NULL,this,menu_selector(GameLayer::menuPauseCallback));//载入双态图和回调函数  
		pPauseItem->setPosition(ccp(winSize.width-normalPause->getContentSize().width*3/4,winSize.height*11/12));  
        CCMenu *menuPause=CCMenu::create(pPauseItem,NULL);//创建CCMenu，可以这么理解CCMenuItem是CCMenu的孩子  
		//menuPause->setPosition(ccp(winSize.width/2,winSize.height));  
		menuPause->setPosition(CCPointZero);  
        this->addChild(menuPause,0);  

		CCSprite *levelup=CCSprite::create();

	levelup->setPosition(ccp(winSize.width/2,winSize.height/2));  
	this->addChild(levelup,2); 

	CCArray *frames_go =CCArray::create();
	char tmp[50];
	sprintf(tmp, "level%d.png", m_level);
	CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
    frames_go->addObject(frame);
  
    for (int j = 1; j < 4; j++)
    {
        sprintf(tmp, "levelgo%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.35f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
	

	CCSequence *_Seq = CCSequence::create(CCDelayTime::create(2.0f),animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::startgame),(void *)levelup), NULL);
	levelup->runAction(_Seq);
	CCSequence *_Seq2 = CCSequence::create(CCDelayTime::create(2.0f),CCCallFuncN::create(this, callfuncN_selector(GameLayer::playmusic)), NULL);
	runAction(_Seq2);


}
void GameLayer::playmusic(CCNode* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/start.wav",false);
}
void GameLayer::menuPauseCallback(CCObject* pSender)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/anniu.wav",false);
	CCSprite *nomal=CCSprite::create("game_bt_stop.png");
    CCSprite *select=CCSprite::create("game_bt_start.png");
	if(!CCDirector::sharedDirector()->isPaused())//如果游戏处于正常状态  
    {  
        //更改为恢复按钮的双态  
  		pPauseItem->setNormalImage(select);  
		pPauseItem->setSelectedImage(nomal);
		this->setTouchEnabled(false);
		this->pauselayer=PauseLayer::create();
		this->addChild(pauselayer,3);
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		updateHighestHistorySorce();
		CCDirector::sharedDirector()->pause();//暂停游戏，这是导演控制的  
		
    }  
    else//否则  
    {  
        //更改为暂停按钮的双态 
		this->setTouchEnabled(true);
		pPauseItem->setNormalImage(nomal);  
		pPauseItem->setSelectedImage(select);  
		CCDirector::sharedDirector()->resume();//开麦拉！
        this->removeChild(pauselayer);
		SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
    }

}
void GameLayer::updateLife()
{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *life=CCSprite::create("life.png");
		life->setPosition(ccp(winSize.width*3/64+(m_life-1)*70,winSize.height*11/12));  
        this->addChild(life,1);
	    m_life--;
		  SimpleAudioEngine::sharedEngine()->playEffect("sound/life.wav",false);
		if(m_life==0)
		{	
			gameover();
		}
	
}
void GameLayer::updateScore()  
{  
	m_score++;
	m_tempscore++;
    if (m_score>=0 && m_score<=10000000)//设置一个最大值20亿  
    {  
		CCString* strScore=CCString::createWithFormat("%d",m_score);//格式化为字符串  
        scoreItem->setString(strScore->m_sString.c_str());//从CCString中获得char*,更新分数  
        int temp=(m_level+1)/2;
		if(m_level<11)
		{
			if(m_level%2==1)
			{
				if(m_tempscore>=(3+temp*(temp-1)/2)*5)
				{
					levelup();
				
				}
			}
			else
			{
				if(m_tempscore>=(3+temp*(temp-1)/2)*5)
				{
					levelup();
				
				}
			}
		}
		else
		{
		     if(m_tempscore>=65)
			{
				levelup();
				
			}
		}
    }  
}  

void GameLayer::updateHighestHistorySorce()  
{  
	     Global::sharedGlobal()->score=m_score;
         Global::sharedGlobal()->level=m_level;
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

void GameLayer::addDirty()
{
	UnitSprite *dirty=UnitSprite::create();
	dirty->bindSprite(	CCSprite::create("spot1.png"),0);
	
	//随机初始位置
    CCSize dirtySize=dirty->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

	int x=  CCRANDOM_0_1()*8+1;
    int y=  CCRANDOM_0_1()*5+1;
	dirty->setAnchorPoint(ccp(0,0));
    dirty->setPosition(ccp(160*(x-1)+80,120*(y-1)+60));  

    this->addChild(dirty);  
    this->m_allDirty->addObject(dirty);  
   SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
 
	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 17; j++)
    {
        sprintf(tmp, "spot%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
    
	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::dirtyuntouched),(void *)dirty),NULL);
	dirty->getSprite()->runAction(_Seq); 
 
}
void GameLayer::addBY()
{
    UnitSprite *by=UnitSprite::create();
	by->bindSprite(	CCSprite::create("by1.png"),0);
	
	//随机初始位置
    CCSize bySize=by->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

    int x=  CCRANDOM_0_1()*8+1;
    int y=  CCRANDOM_0_1()*5+1;
	by->setAnchorPoint(ccp(0,0));
    by->setPosition(ccp(160*(x-1)+80,120*(y-1)+60));  
    this->addChild(by);  
    this->m_allBY->addObject(by);  
    SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
 
	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 28; j++)
    {
        sprintf(tmp, "by%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.18f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
    
	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::byuntouched),(void *)by),NULL);
	by->getSprite()->runAction(_Seq); 
 
}
void GameLayer::addBlue(CCPoint point)
{ 
    UnitSprite *blue=UnitSprite::create();
	blue->bindSprite(CCSprite::create("blue1.png"),0);
	
	//随机初始位置
    CCSize blueSize=blue->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

	blue->setAnchorPoint(ccp(0,0));
	CCPoint reallypoint=ccp(point.x-160,point.y);
	if(reallypoint.x<0)
	{
		reallypoint.x=80;
	}
	blue->setPosition(reallypoint);    ;  
    this->addChild(blue);  
    this->m_allBlue->addObject(blue);  
    SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
 
	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 21; j++)
    {
        sprintf(tmp, "blue%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.18f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
    
	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::blueuntouched),(void *)blue),NULL);
	blue->getSprite()->runAction(_Seq); 
    
}
void GameLayer::addYellow(CCPoint point)
{ 
    UnitSprite *yellow=UnitSprite::create();
	yellow->bindSprite(CCSprite::create("yel1.png"),0);
	
	//随机初始位置
    CCSize yellowSize=yellow->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

	yellow->setAnchorPoint(ccp(0,0));

	CCPoint reallypoint=ccp(point.x,point.y-120);
	if(reallypoint.y<0)
	{
		reallypoint.y=60;
	}
    yellow->setPosition(reallypoint);    
    this->addChild(yellow);  
    this->m_allYellow->addObject(yellow);  
    SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
 
	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 21; j++)
    {
        sprintf(tmp, "yel%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
    
	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::yellowuntouched),(void *)yellow),NULL);
	yellow->getSprite()->runAction(_Seq); 
    
}
void GameLayer::addOrgreen()
{
	UnitSprite *orgreen=UnitSprite::create();
	orgreen->bindSprite(CCSprite::create("orgreen1.png"),1);
	
	//随机初始位置
    CCSize greenSize=orgreen->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

    int x=  CCRANDOM_0_1()*8+1;
    int y=  CCRANDOM_0_1()*5+1;
	orgreen->setAnchorPoint(ccp(0,0));
    orgreen->setPosition(ccp(160*(x-1)+80,120*(y-1)+60));  

    this->addChild(orgreen,0);  
    this->m_allOrgreen->addObject(orgreen);  
    SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);

	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 18; j++)
    {
        sprintf(tmp, "orgreen%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);

	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::orgreenuntouched),(void *)orgreen),NULL);
	orgreen->getSprite()->runAction(_Seq); 
    
}
void GameLayer::addOrange()
{  
	//绑定orange
	UnitSprite *orange=UnitSprite::create();
	orange->bindSprite(	CCSprite::create("org1.png") ,0);
	//随机初始位置
    CCSize orangeSize=orange->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  
    int x=  CCRANDOM_0_1()*8+1;
    int y=  CCRANDOM_0_1()*5+1;
	orange->setAnchorPoint(ccp(0,0));
    orange->setPosition(ccp(160*(x-1)+80,120*(y-1)+60));  

	this->addChild(orange); 
	SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
    this->m_allOrange->addObject(orange);  

	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 12; j++)
    {
        sprintf(tmp, "org%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);
	
	
	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::orangeuntouched),(void *)orange),NULL);
	orange->getSprite()->runAction(_Seq);
	
}
void GameLayer::addGreen()
{
	UnitSprite *green=UnitSprite::create();
	green->bindSprite(CCSprite::create("green1.png"),0);
	
	//随机初始位置
    CCSize greenSize=green->getSprite()->getContentSize();  
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();  

    int x=  CCRANDOM_0_1()*8+1;
    int y=  CCRANDOM_0_1()*5+1;
	green->setAnchorPoint(ccp(0,0));
    green->setPosition(ccp(160*(x-1)+80,120*(y-1)+60));  

    this->addChild(green); 
	SimpleAudioEngine::sharedEngine()->playEffect("sound/go.wav",false);
    this->m_allGreen->addObject(green);  
  

	CCArray *frames_go =CCArray::create();
    char tmp[50];
    for (int j = 1; j < 18; j++)
    {
        sprintf(tmp, "green%d.png", j);
        CCSpriteFrame *frame = cache->spriteFrameByName(tmp);
        frames_go->addObject(frame);
    }
	CCAnimation *animation_go = CCAnimation::createWithSpriteFrames(frames_go, 0.2f);
	CCAnimate *animate_go = CCAnimate::create(animation_go);

	CCSequence *_Seq = CCSequence::create(animate_go,CCCallFuncND::create(this, callfuncND_selector(GameLayer::greenuntouched),(void *)green),NULL);
	green->getSprite()->runAction(_Seq); 
    
}

void GameLayer::dirtyuntouched(CCNode* pSender,void* data)
{removeDirty(pSender,data);this->removeChild((CCNode *)data,true);
}
void GameLayer::orgreenuntouched(CCNode* pSender,void* data)
{
	removeOrgreen(pSender,data);
	updateLife();
}
void GameLayer::blueuntouched(CCNode* pSender,void* data)
{  
    removeBlue(pSender,data);
	updateLife();
}
void GameLayer::yellowuntouched(CCNode* pSender,void* data)
{
    removeYellow(pSender,data);
	updateLife();
}
void GameLayer::byuntouched(CCNode* pSender,void* data)
{
    removeBY(pSender,data);
	updateLife();
}
void GameLayer::orangeuntouched(CCNode* pSender,void* data)
{
	removeOrange(pSender,data);
	updateLife();
}
void GameLayer::greenuntouched(CCNode* pSender,void* data)
{removeGreen(pSender,data);updateLife();}


void GameLayer::removeBY(CCNode* pTarget, void* data)
{
	 UnitSprite* by=(UnitSprite*)data;  
    if (by!=NULL)  
    {  
        m_allBY->removeObject(by);  
    }  
}
void GameLayer::removeDirty(CCNode* pTarget, void* data)  
{  
    UnitSprite* dirty=(UnitSprite*)data;  
    if (dirty!=NULL)  
    {  
        m_allDirty->removeObject(dirty);  
       // this->removeChild(orange,true);  
    }  
}  
void GameLayer::removeYellow(CCNode* pTarget, void* data)
{
	UnitSprite* yellow=(UnitSprite*)data;  
    if (yellow!=NULL)  
    {  
        m_allYellow->removeObject(yellow);  
    }  
}
void GameLayer::removeBlue(CCNode* pTarget, void* data)
{
	UnitSprite* blue=(UnitSprite*)data;  
    if (blue!=NULL)  
    {  
        m_allBlue->removeObject(blue); 
    }  
}
void GameLayer::removeOrgreen(CCNode* pTarget, void* data)
{
	UnitSprite* orgreen=(UnitSprite*)data;  
    if (orgreen!=NULL)  
    {  
        m_allOrgreen->removeObject(orgreen);  
       // this->removeChild(green,true);  
    }  
}
void GameLayer::removeGreen(CCNode* pTarget, void* data)  
{  
    UnitSprite* green=(UnitSprite*)data;  
    if (green!=NULL)  
    {  
        m_allGreen->removeObject(green);  
       // this->removeChild(green,true);  
    }  
}  

void GameLayer::removeAllOrgreen()
{
	CCObject* obj;  
    CCARRAY_FOREACH(m_allOrgreen,obj)  
    {  
       UnitSprite* orgreen=(UnitSprite*)obj;  
       removeOrgreen(NULL,orgreen);
    }
}
void GameLayer::removeAllYellow()
{
    CCObject* obj;  
    CCARRAY_FOREACH(m_allYellow,obj)  
    {  
       UnitSprite* yellow=(UnitSprite*)obj;  
       removeYellow(NULL,yellow);
    }
}
void GameLayer::removeAllBlue()
{ 
    CCObject* obj;  
    CCARRAY_FOREACH(m_allBlue,obj)  
    {  
       UnitSprite* blue=(UnitSprite*)obj;  
       removeBlue(NULL,blue);
    }
}
void GameLayer::removeAllBY()
{
    CCObject* obj;  
    CCARRAY_FOREACH(m_allBY,obj)  
    {  
       UnitSprite* by=(UnitSprite*)obj;  
       removeBY(NULL,by);
    }
}
void GameLayer::removeAllDirty()  
{  
    CCObject* obj;  
    CCARRAY_FOREACH(m_allDirty,obj)  
    {  
       UnitSprite* dirty=(UnitSprite*)obj;  
       removeDirty(NULL,dirty);         
     }  
}  
void GameLayer::removeAllGreen()  
{  
    CCObject* obj;  
    CCARRAY_FOREACH(m_allGreen,obj)  
    {  
       UnitSprite* green=(UnitSprite*)obj;  
       removeGreen(NULL,green);
    }  
} 
void GameLayer::removeOrange(CCNode* pTarget, void* data)  
{  
    UnitSprite* orange=(UnitSprite*)data;  
    if (orange!=NULL)  
    {  
        m_allOrange->removeObject(orange);  
       // this->removeChild(orange,true);  
    }  
}  
void GameLayer::removeAllOrange()  
{  
    CCObject* obj;  
    CCARRAY_FOREACH(m_allOrange,obj)  
    {  
       UnitSprite* orange=(UnitSprite*)obj;  
       removeOrange(NULL,orange);
           
     }  
} 
void GameLayer::removeAllUnitSprite() 
{
	removeAllOrange();
	removeAllGreen();
	removeAllDirty();
	removeAllOrgreen();
	removeAllBlue();
	removeAllYellow();
	removeAllBY();
}

