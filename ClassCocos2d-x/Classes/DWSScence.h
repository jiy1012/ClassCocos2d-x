//
//  DWSScence.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#ifndef __ClassCocos2d_x__DWSScence__
#define __ClassCocos2d_x__DWSScence__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <spine/Json.h>

USING_NS_CC;
USING_NS_CC_EXT;

class DWSScence : public cocos2d::CCLayer
{
public:
    
    
    CCSprite* DWSLogoDisplay(CCSize winSize);
    
    CREATE_FUNC(DWSScence);
    
    CCSprite* DWSTitleHeroDisplay(CCSize winSize);
    
};


#endif /* defined(__ClassCocos2d_x__DWSScence__) */
