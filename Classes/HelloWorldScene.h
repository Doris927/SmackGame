#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class HelloWorld : public cocos2d::CCLayer
{
public:

    virtual bool init();  

    static cocos2d::CCScene* scene();

    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
