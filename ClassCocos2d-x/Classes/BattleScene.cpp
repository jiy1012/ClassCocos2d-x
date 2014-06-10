//
//  BattleScene.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-24.
//
//

#include "BattleScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
BattleScene* BattleScene::s_BattleScene = NULL;

BattleScene* BattleScene::shared()
{
    if (NULL == s_BattleScene) {
        s_BattleScene = new BattleScene();
    }
    return s_BattleScene;
}

void BattleScene::releaseSelf()
{
    s_BattleScene = NULL;
}

BattleScene::BattleScene()
{
    skillDetail1 = NULL;
    skillDetail2 = NULL;
    HP1 = NULL;
    HP2 = NULL;

}

BattleScene::~BattleScene()
{
//    CC_SAFE_RELEASE_NULL(skillDetail1);
//    CC_SAFE_RELEASE_NULL(skillDetail2);
//    CC_SAFE_RELEASE_NULL(HP1);
//    CC_SAFE_RELEASE_NULL(HP2);
}

CCScene* BattleScene::ShowHero(HeroStruct* hero)
{
    
    CCSize heroSize;
    heroSize.width = WIN_WIDTH/2;
    heroSize.height = WIN_HEIGHT/2;
    
    CCScene* heroScene = CCScene::create();
    CCLabelTTF* name = CCLabelTTF::create(hero->name.c_str(), "", 40);

    CCMenuItemImage* Qimg = CCMenuItemImage::create("Qimg.png", "Qimg.png", this, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Wimg = CCMenuItemImage::create("Wimg.png", "Wimg.png", this, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Eimg = CCMenuItemImage::create("Eimg.png", "Eimg.png", this, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Rimg = CCMenuItemImage::create("Rimg.png", "Rimg.png", this, menu_selector(BattleScene::clickSkill));
    Qimg->setPosition(ccp(-heroSize.width/2+60, 0));
    Wimg->setPosition(ccp(-heroSize.width/2+120, 0));
    Eimg->setPosition(ccp(-heroSize.width/2+180, 0));
    Rimg->setPosition(ccp(-heroSize.width/2+240, 0));
    
    int tagidx = hero->id*10;
    Qimg->setTag(tagidx+1);
    Wimg->setTag(tagidx+2);
    Eimg->setTag(tagidx+3);
    Rimg->setTag(tagidx+4);
    
    CCMenu* skillMenu = CCMenu::create(Qimg,Wimg,Eimg,Rimg,NULL);
    skillMenu->setContentSize(CCSizeMake(heroSize.width, 60));
    skillMenu->setPosition(ccp(-heroSize.width/2+skillMenu->getContentSize().width/2,0));

    name->setPosition(ccp(-heroSize.width/2+100, heroSize.height-name->getContentSize().height));

    heroScene->addChild(name);
    heroScene->addChild(skillMenu);

    return heroScene;
}

CCLabelTTF* BattleScene::setSkillDetail1(const char* detail)
{
    if (skillDetail1 == NULL) {
        skillDetail1 = CCLabelTTF::create(detail, "", 30);
        skillDetail1->setPosition(ccp(100, WIN_HEIGHT/4));
    }else{
        skillDetail1->setString(detail);
    }
    return skillDetail1;
}

CCLabelTTF* BattleScene::setSkillDetail2(const char* detail)
{
    if (skillDetail2 == NULL) {
        skillDetail2 = CCLabelTTF::create(detail, "", 30);
        skillDetail2->setPosition(ccp(WIN_WIDTH/2+100, WIN_HEIGHT/4));
    }else{
        skillDetail2->setString(detail);
    }
    return skillDetail2;
}

CCLabelTTF* BattleScene::setHP1(const char* detail)
{
    if (HP1 == NULL) {
        HP1 = CCLabelTTF::create(detail, "", 50);
        HP1->setPosition(ccp(WIN_WIDTH/2/2+100, WIN_HEIGHT*8/10));
    }else{
        HP1->setString(detail);
    }
    return HP1;
}

CCLabelTTF* BattleScene::setHP2(const char* detail)
{
    if (HP2 == NULL) {
        HP2 = CCLabelTTF::create(detail, "", 50);
        HP2->setPosition(ccp(WIN_WIDTH/2*3/2+100, WIN_HEIGHT*8/10));
    }else{
        HP2->setString(detail);
    }
    return HP2;
}

void BattleScene::clickSkill(CCObject* pSender)
{
    CCMenuItemImage* skillMenu = (CCMenuItemImage*) pSender;
    int heroId = skillMenu->getTag()/10;
    int sId = skillMenu->getTag()%10;
    const char* skill = "q";
    if (1 == sId) {
        skill = "q";
    }else if (2 == sId){
        skill = "w";
    }else if (3 == sId){
        skill = "e";
    }else if (4 == sId){
        skill = "r";
    }
    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
    CCDictionary* h1 = (CCDictionary*) groupHero->objectForKey(heroId);
    const char* Detail = h1->valueForKey(skill)->getCString();
    int act = h1->valueForKey(CCString::createWithFormat("attack%s",skill)->getCString())->intValue();
    if (skillDetail1->getTag() == heroId) {
        int hero2 = skillDetail2->getTag();
        CCDictionary* h2 = (CCDictionary*) groupHero->objectForKey(hero2);
        int defense = h2->valueForKey("defense")->intValue();
        int minus = act>defense?act-defense:0;
        setSkillDetail1(Detail);
        int nowHp2 = ATOI(HP2->getString()) - minus>0?ATOI(HP2->getString()) - minus:0;
        setHP2(ITOA(nowHp2));
    }else if(skillDetail2->getTag() == heroId){
        int hero1 = skillDetail1->getTag();
        CCDictionary* h2 = (CCDictionary*) groupHero->objectForKey(hero1);
        int defense = h2->valueForKey("defense")->intValue();
        int minus = act>defense?act-defense:0;
        setSkillDetail2(Detail);
        int nowHp1 = ATOI(HP1->getString()) - minus>0?ATOI(HP1->getString()) - minus:0;
        setHP1(ITOA(nowHp1));
    }
    
    CCLOG("click skill ok %d %s %s %d %d",heroId,skill,Detail,skillDetail1->getTag(),skillDetail2->getTag());
}
