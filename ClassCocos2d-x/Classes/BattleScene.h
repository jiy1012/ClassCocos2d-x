//
//  BattleScene.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-24.
//
//

#ifndef __ClassCocos2d_x__BattleScene__
#define __ClassCocos2d_x__BattleScene__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "DefinedBase.h"
#include "DatabaseDefault.h"
#include "HeroStruct.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BattleScene : public CCLayer
{
public:
    static BattleScene* shared();
    
    CCScene* ShowHero(HeroStruct* hero);
    
    void clickSkill(CCObject* pSender);
    CCLabelTTF* setSkillDetail1(const char* detail);
    CCLabelTTF* setSkillDetail2(const char* detail);
    CCLabelTTF* skillDetail1;
    CCLabelTTF* skillDetail2;
private:
    static BattleScene* s_BattleScene;
};

#endif /* defined(__ClassCocos2d_x__BattleScene__) */
