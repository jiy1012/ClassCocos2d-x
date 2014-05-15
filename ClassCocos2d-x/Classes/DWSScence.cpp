//
//  DWSScence.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#include "DWSScence.h"
#include "DatabaseDefault.h"
#include "SimpleAudioEngine.h"
#include "HeroTableLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;


CCSprite* DWSScence::DWSLogoDisplay(CCSize winSize)
{
    CCSprite* DWSSprite = CCSprite::create();
    DWSSprite->setContentSize(CCSize(winSize.width/2,winSize.height/2));
    DWSSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    CCSprite* pSprite = CCSprite::create("DWS.LOGO.png");
    pSprite->setPosition( ccp(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2) );
    CCLabelTTF* pLabel = CCLabelTTF::create("DWS，为爱而生", "", 25);
    pLabel->cocos2d::CCNode::setPosition(ccp(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2-pSprite->getContentSize().height));
    
    CCFadeOut* pFadeOutS = CCFadeOut::create(3.0f);
    CCFadeOut* pFadeOutL = CCFadeOut::create(3.0f);
    CCFiniteTimeAction* pSeqS = CCSequence::create(pFadeOutS,NULL);
    CCFiniteTimeAction* pSeqL = CCSequence::create(pFadeOutL,NULL);
    
    pSprite->runAction(pSeqS);
    pLabel->runAction(pSeqL);
    
    DWSSprite->addChild(pSprite);
    DWSSprite->addChild(pLabel);
    
    return DWSSprite;
}

CCSprite* DWSScence::DWSTitleHeroDisplay(CCSize winSize)
{
    CCSprite* DWSHero = CCSprite::create();
    
    CCSprite* pDWSC = CCSprite::create("DWS.C.png");
    CCSprite* pDWSJ = CCSprite::create("DWS.J.png");
    pDWSC->setPosition(ccp(0, 0));
    pDWSJ->setPosition(ccp(winSize.width, 0));
    CCJumpTo* pJumpToC = CCJumpTo::create(3.0f, ccp(winSize.width/2-pDWSC->getContentSize().width, winSize.height*3/4), 100, 10);
    CCJumpTo* pJumpToJ = CCJumpTo::create(3.0f, ccp(winSize.width/2+pDWSJ->getContentSize().width, winSize.height*3/4), 100, 10);
    pDWSC->runAction(pJumpToC);
    pDWSJ->runAction(pJumpToJ);
    
    DWSHero->addChild(pDWSC);
    DWSHero->addChild(pDWSJ);
    
    return DWSHero;
}

CCScene* DWSScence::DWSHeroShow()
{
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCScene* heroAll = CCScene::create();
    HeroTableLayer* layer = HeroTableLayer::create();
    
    CCMenuItemImage* backButton = CCMenuItemImage::create("backButton.png", "backButtonSelected.png", heroAll, menu_selector(DWSScence::HeroClick));
    CCMenuItemImage* stratPKButton = CCMenuItemImage::create("startPKButton.png", "startPKButtonSelected.png", layer, menu_selector(HeroTableLayer::startPK));
    
    backButton->setPosition(ccp(backButton->getContentSize().width, backButton->getContentSize().height/2));
    stratPKButton->setPosition(ccp(winSize.width/2, stratPKButton->getContentSize().height/2));
    
    CCMenu* bMenu = CCMenu::create(backButton,stratPKButton,NULL);
    
    bMenu->setPosition( CCPointZero );
    heroAll->addChild(bMenu);
    CCLabelTTF* pk = CCLabelTTF::create("PK", "", 50);
    pk->setPosition(ccp(winSize.width/2, winSize.height/3*1));
    
    heroAll->addChild(pk);
    heroAll->addChild(layer);
    
    
//    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
//    
//    CCLog("here %d",groupHero->count());
//    
//    CCDictElement* heroOne;
//    CCArray* heroList = CCArray::create();
// 
//    CCDICT_FOREACH(groupHero, heroOne)
//    {
////        int heroId =heroOne->getIntKey();
////        const char* name = ((CCString*)((CCDictionary*)(heroOne->getObject()))->objectForKey("name"))->getCString();
////        const char* heroImage = CCString::createWithFormat("hero_%s.png",name)->getCString();
////        CCMenuItemImage* heroMenu = CCMenuItemImage::create(heroImage, heroImage, this, menu_selector(DWSScence::HeroClick));
////        
////        heroMenu->setPosition(100, 100*i);
////        heroList->addObject(heroMenu);
//
//        
//    };
//    CCMenu* pHeroMenu = CCMenu::createWithArray(heroList);
//    heroAll->addChild(pHeroMenu);
//    CCMenuItemImage* backButton = CCMenuItemImage::create("backButton.png", "backButtonSelected.png", this, menu_selector(DWSScence::HeroClick));
//    backButton->setPosition(ccp(100, 200));
//    CCMenu* bMenu = CCMenu::create(backButton,NULL);
//    bMenu->setPosition( CCPointZero );
//    heroAll->addChild(bMenu);

    return heroAll;
}



void DWSScence::HeroClick(CCObject* pSender)
{
    
    CCLog("click hero");
    CCDirector::sharedDirector()->popScene();

}


