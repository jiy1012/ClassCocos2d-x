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


CCScene* BattleScene::ShowHero(HeroStruct* hero)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSize heroSize;
    heroSize.width = winSize.width/2;
    heroSize.height = winSize.height/2;
    
    CCScene* heroScene = CCScene::create();
//    CCLOG("ww:%f wh:%f hw:%f hh:%f",winSize.width,winSize.height,heroSize.width,heroSize.height);
    
    CCLabelTTF* name = CCLabelTTF::create(hero->name.c_str(), "", 40);
    CCLabelAtlas *hp = CCLabelAtlas::create(ITOA(hero->HP),"tuffy_bold_italic-charmap.plist");

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
    hp->setPosition(ccp(-heroSize.width/2+100, heroSize.height*6/10));

    heroScene->addChild(name,10,20);
    heroScene->addChild(hp,10,10);
    heroScene->addChild(skillMenu,10,15);

    return heroScene;
}

CCLabelTTF* BattleScene::setSkillDetail1(const char* detail)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSize heroSize;
    heroSize.width = winSize.width/2;
    heroSize.height = winSize.height/2;
    
    if (skillDetail1 == NULL) {
        skillDetail1 = CCLabelTTF::create(detail, "", 30);
        skillDetail1->setContentSize(heroSize);
        skillDetail1->setPosition(ccp(100, heroSize.height/2));
    }else{
        skillDetail1->setString(detail);
    }
    return skillDetail1;
}

CCLabelTTF* BattleScene::setSkillDetail2(const char* detail)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSize heroSize;
    heroSize.width = winSize.width/2;
    heroSize.height = winSize.height/2;
    
    if (skillDetail2 == NULL) {
        skillDetail2 = CCLabelTTF::create(detail, "", 30);
        skillDetail2->setContentSize(heroSize);
        skillDetail2->setPosition(ccp(heroSize.width+100, heroSize.height/2));
    }else{
        skillDetail2->setString(detail);
    }
    return skillDetail2;
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
    if (skillDetail1->getTag() == heroId) {
        setSkillDetail1(Detail);
    }else if(skillDetail2->getTag() == heroId){
        setSkillDetail2(Detail);
    }
    
    CCLOG("click skill ok %d %s %s %d %d",heroId,skill,Detail,skillDetail1->getTag(),skillDetail2->getTag());
}
