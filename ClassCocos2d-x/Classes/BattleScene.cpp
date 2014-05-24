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


CCScene* BattleScene::ShowHero(HeroStruct* hero , int idx)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSize heroSize;
    heroSize.width = winSize.width/2;
    heroSize.height = winSize.height/2;
    /*
     idx=1 pointx=heroSize.width/2
     idx=2 pointx=heroSize.width*3/2
     */
    
    float pointx = heroSize.width;
    
    CCScene* heroScene = CCScene::create();
    heroScene->setContentSize(heroSize);
    heroScene->setPosition(ccp(heroSize.width/2, heroSize.height/2));
    
//    CCLOG("ww:%f wh:%f hw:%f hh:%f",winSize.width,winSize.height,heroSize.width,heroSize.height);
    
    CCLabelTTF* name = CCLabelTTF::create(hero->name.c_str(), "", 20);
    CCLabelAtlas *hp = CCLabelAtlas::create(ITOA(hero->HP),"tuffy_bold_italic-charmap.plist");

    CCSprite* Qimg = SET_SKILL_IMG("Qimg.png");
    CCSprite* Wimg = SET_SKILL_IMG("Wimg.png");
    CCSprite* Eimg = SET_SKILL_IMG("Eimg.png");
    CCSprite* Rimg = SET_SKILL_IMG("Rimg.png");

    name->setPosition(ccp(-heroSize.width/2+Qimg->getContentSize().width, heroSize.height));
    hp->setPosition(ccp(-heroSize.width/2+Qimg->getContentSize().width, heroSize.height*9/10));
    Qimg->setPosition(ccp(-heroSize.width/2+Qimg->getContentSize().width, heroSize.height*8/10));
    Wimg->setPosition(ccp(-heroSize.width/2+Wimg->getContentSize().width, heroSize.height*5/10));
    Eimg->setPosition(ccp(-heroSize.width/2+Eimg->getContentSize().width, heroSize.height*3/10));
    Rimg->setPosition(ccp(-heroSize.width/2+Rimg->getContentSize().width, heroSize.height*1/10));
    
    heroScene->addChild(name);
    heroScene->addChild(hp);
    heroScene->addChild(Qimg);
    heroScene->addChild(Wimg);
    heroScene->addChild(Eimg);
    heroScene->addChild(Rimg);
    return heroScene;
}
