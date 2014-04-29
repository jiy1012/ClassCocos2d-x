//
//  DWSScence.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#include "DWSScence.h"
#include "SimpleAudioEngine.h"

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