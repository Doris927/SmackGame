#include "UnitSprite.h"

UnitSprite::UnitSprite()
{
    m_sprite=NULL;
	m_state=0;
}
UnitSprite::~UnitSprite()
{
    
}

UnitSprite * UnitSprite::create()
{
	UnitSprite* pRet=new UnitSprite;
	pRet->autorelease();
	return pRet;
}
void UnitSprite::bindSprite(CCSprite *sprite,int state)
{
	m_sprite=sprite;
	m_state=state;
	this->addChild(m_sprite);  
}
CCSprite* UnitSprite::getSprite()
{
	return m_sprite;
}
int UnitSprite::getState()
{
	return m_state;
}
void UnitSprite::changeState()
{
	if(m_state==0)
		m_state=1;
	else
		m_state=0;
}
CCRect UnitSprite::getBoundingBox()
{
	CCRect rect=m_sprite->boundingBox();  
    CCPoint pos=this->convertToWorldSpace(rect.origin);  
	
    return CCRect(pos.x-10,pos.y-10,rect.size.width+20,rect.size.height+20);   
	//return rect; 
}