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
    CCLabelTTF* skillDetail = CCLabelTTF::create();
    CCMenuItemImage* Qimg = CCMenuItemImage::create("Qimg.png", "Qimg.png", heroScene, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Wimg = CCMenuItemImage::create("Wimg.png", "Wimg.png", heroScene, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Eimg = CCMenuItemImage::create("Eimg.png", "Eimg.png", heroScene, menu_selector(BattleScene::clickSkill));
    CCMenuItemImage* Rimg = CCMenuItemImage::create("Rimg.png", "Rimg.png", heroScene, menu_selector(BattleScene::clickSkill));
    Qimg->setPosition(ccp(-heroSize.width/2+60, 0));
    Wimg->setPosition(ccp(-heroSize.width/2+120, 0));
    Eimg->setPosition(ccp(-heroSize.width/2+180, 0));
    Rimg->setPosition(ccp(-heroSize.width/2+240, 0));
    CCMenu* skillMenu = CCMenu::create(Qimg,Wimg,Eimg,Rimg,NULL);
    skillMenu->setContentSize(CCSizeMake(heroSize.width, 60));
    skillMenu->setPosition(ccp(-heroSize.width/2+skillMenu->getContentSize().width/2,0));

    name->setPosition(ccp(-heroSize.width/2+100, heroSize.height-name->getContentSize().height));
    hp->setPosition(ccp(-heroSize.width/2+100, heroSize.height*8/10));
    
    heroScene->addChild(name);
    heroScene->addChild(hp);
    heroScene->addChild(skillMenu,hero->id);
    heroScene->addChild(skillDetail);
    return heroScene;
}

void BattleScene::clickSkill(CCObject* pSender)
{
    CCScene* heroScene = (CCScene*) pSender;
    CCLOG("click skill %d",heroScene->getTag());
}
