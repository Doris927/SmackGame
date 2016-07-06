#include"Global.h"

static Global *global=NULL;

Global::Global():level(1),score(0),highestscore(0),highestlevel(1)
{
}
 Global *Global::sharedGlobal()
 {
	 if(!global)
	 {
		 global=new Global();

	 }
	 return global;
 }
