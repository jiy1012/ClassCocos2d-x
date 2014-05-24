//
//  DWSScene.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#ifndef __ClassCocos2d_x__DWSScene__
#define __ClassCocos2d_x__DWSScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HeroTableLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DWSScene : public CCLayer
{
public:

    static DWSScene* shared();
    
    CCSprite* DWSLogoDisplay(CCSize winSize);
    
    CCSprite* DWSTitleHeroDisplay(CCSize winSize);
    
    CCScene* DWSHeroShow();
    
    void heroBackClick(CCObject* pSender);
    void startPK(CCObject* pSender);
private:
    static DWSScene* s_DWSScene;
};


#endif /* defined(__ClassCocos2d_x__DWSScene__) */
