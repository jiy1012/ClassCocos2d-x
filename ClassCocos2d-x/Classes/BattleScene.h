//
//  BattleScene.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-24.
//
//

#ifndef __ClassCocos2d_x__BattleScene__
#define __ClassCocos2d_x__BattleScene__


#include "CommonConfig.h"
#include "DatabaseDefault.h"
#include "HeroStruct.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BattleScene : public CCLayer
{
public:
    BattleScene();
    ~BattleScene();
    
    static BattleScene* shared();
    
    CCScene* ShowHero(HeroStruct* hero);
    
    void clickSkill(CCObject* pSender);
    
    void releaseSelf();
    
    CCLabelTTF* skillDetail1;
    CCLabelTTF* skillDetail2;
    CCLabelTTF* setSkillDetail1(const char* detail);
    CCLabelTTF* setSkillDetail2(const char* detail);

    
    CCLabelTTF* HP1;
    CCLabelTTF* HP2;
    CCLabelTTF* setHP1(const char* detail);
    CCLabelTTF* setHP2(const char* detail);
private:
    static BattleScene* s_BattleScene;
};

#endif /* defined(__ClassCocos2d_x__BattleScene__) */
