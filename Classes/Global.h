#pragma once

#include "cocos2d.h"
USING_NS_CC; 

class Global
{

	
public:
	int level;
	int highestlevel;
	int score;
	int highestscore;
	static Global *sharedGlobal();

	Global();
	~Global();
};