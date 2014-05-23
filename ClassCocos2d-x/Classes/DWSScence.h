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
#include "HeroTableLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DWSScence : public CCLayer
{
public:

    static DWSScence* shared();
    
    CCSprite* DWSLogoDisplay(CCSize winSize);
    
    CCSprite* DWSTitleHeroDisplay(CCSize winSize);
    
    CCScene* DWSHeroShow();
    
    void heroBackClick(CCObject* pSender);
    void startPK(CCObject* pSender);
private:
    static DWSScence* s_DWSScence;
};


#endif /* defined(__ClassCocos2d_x__DWSScence__) */
