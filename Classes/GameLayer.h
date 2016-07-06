//GameLayer.h
#pragma once
#include "PauseLayer.h"
#include "cocos2d.h"
USING_NS_CC;
 
class GameLayer : public CCLayer
{
private:
	int m_score;//分数
	int m_tempscore;
	int m_life;//机会 生命值
	//int m_state;//playing  over pause rest
	//int m_freq;
	int m_level;
    CCLabelBMFont*   scoreItem;
    CCLabelBMFont*   levelItem;
	CCMenuItemImage * pPauseItem;
	CCArray *m_allOrange;
	CCArray *m_allGreen;
	CCArray *m_allYellow;
	CCArray *m_allBlue;
	CCArray *m_allDirty;
	CCArray *m_allOrgreen;
	CCArray *m_allBY;
	CCSpriteFrameCache *cache ;
	PauseLayer* pauselayer;

public:
     
    GameLayer(void);
 
    ~GameLayer(void);
 
    CREATE_FUNC(GameLayer);
 
    virtual bool init();
    static cocos2d::CCScene* scene();
	void  initBackground();

	void updateScore() ;
	void updateLife();
	
	void  startgame(CCNode *pSender,void* data);
	void  playmusic(CCNode* pSender);
	void  levelup();
	//void  frequp();
	void  gameover();
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);  
    void setgame(float dt);
	void updateHighestHistorySorce() ;
	void addOrange();
	void addGreen();
	void addDirty();
	void addOrgreen();
	void addYellow(CCPoint point);
	void addBlue(CCPoint point);
	void addBY();
	void removeOrgreen(CCNode* pTarget, void* data);
	void removeOrange(CCNode* pTarget, void* data);  
	void removeGreen(CCNode* pTarget, void* data);
	void removeDirty(CCNode* pTarget, void* data);
	void removeYellow(CCNode* pTarget, void* data);
	void removeBlue(CCNode* pTarget, void* data);
	void removeBY(CCNode* pTarget, void* data);
	void resumeOrgreen (CCNode* pTarget, void* data);

	void removeAllYellow();
	void removeAllBlue();
	void removeAllBY();
	void removeAllOrange() ;
	void removeAllGreen() ;
	void removeAllDirty();
	void removeAllOrgreen();
	void removeAllUnitSprite() ;
	void menuPauseCallback(CCObject* pSender);

	void orangebetouched(void *data);
	void greenbetouched(void * data);
	void dirtybetouched(void * data);
    void orgreenbetouched(void *data);
	void bluebetouched(void *data);
	void yellowbetouched(void *data);
	void bybetouched(void *data);

	void orangeuntouched(CCNode* pSender,void* data);
	void greenuntouched(CCNode* pSender,void* data);
	void dirtyuntouched(CCNode* pSender,void* data);
	void orgreenuntouched(CCNode* pSender,void* data);
	void blueuntouched(CCNode* pSender,void* data);
	void yellowuntouched(CCNode* pSender,void* data);
	void byuntouched(CCNode* pSender,void* data);
	virtual void registerWithTouchDispatcher()  ;
	//void animation(char * name);
};