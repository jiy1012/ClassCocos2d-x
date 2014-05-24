//
//  DWSScene.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-28.
//
//

#include "DWSScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
DWSScene* DWSScene::s_DWSScene = NULL;

DWSScene* DWSScene::shared()
{
    if (NULL == s_DWSScene) {
        s_DWSScene = new DWSScene();
    }
    return s_DWSScene;
}


CCSprite* DWSScene::DWSLogoDisplay(CCSize winSize)
{
    CCSprite* DWSSprite = CCSprite::create();
    DWSSprite->setContentSize(CCSize(winSize.width/2,winSize.height/2));
    DWSSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
    
    CCSprite* pSprite = CCSprite::create("DWS.LOGO.png");
    pSprite->setPosition( ccp(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2) );
    CCLabelTTF* pLabel = CCLabelTTF::create("DWS，为爱而生", "", 25);
    pLabel->cocos2d::CCNode::setPosition(ccp(DWSSprite->getContentSize().width/2, DWSSprite->getContentSize().height/2-pSprite->getContentSize().height));
    
    CCFadeOut* pFadeOutS = CCFadeOut::create(1.0f);
    CCFadeOut* pFadeOutL = CCFadeOut::create(1.0f);
    CCFiniteTimeAction* pSeqS = CCSequence::create(pFadeOutS,NULL);
    CCFiniteTimeAction* pSeqL = CCSequence::create(pFadeOutL,NULL);
    
    pSprite->runAction(pSeqS);
    pLabel->runAction(pSeqL);
    
    DWSSprite->addChild(pSprite);
    DWSSprite->addChild(pLabel);
    
    return DWSSprite;
}

CCSprite* DWSScene::DWSTitleHeroDisplay(CCSize winSize)
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

CCScene* DWSScene::DWSHeroShow()
{

    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCScene* heroAll = CCScene::create();
    
    CCMenuItemImage* backButton = CCMenuItemImage::create("backButton.png", "backButtonSelected.png", heroAll, menu_selector(DWSScene::heroBackClick));
    backButton->setPosition(ccp(backButton->getContentSize().width, backButton->getContentSize().height/2));
    
    HeroTableLayer* layer = HeroTableLayer::create();
    CCMenuItemImage* stratPKButton = CCMenuItemImage::create("startPKButton.png", "startPKButtonSelected.png", layer, menu_selector(HeroTableLayer::startPK));
    stratPKButton->setPosition(ccp(winSize.width/2, stratPKButton->getContentSize().height/2));
    
    CCMenu* bMenu = CCMenu::create(backButton,stratPKButton,NULL);
    bMenu->setPosition( CCPointZero );
    
    CCLabelTTF* pk = CCLabelTTF::create("PK", "", 50);
    pk->setPosition(ccp(winSize.width/2, winSize.height/3*1));
    
    heroAll->addChild(bMenu);
    heroAll->addChild(pk);
    heroAll->addChild(layer);
    return heroAll;
}

void DWSScene::heroBackClick(CCObject* pSender)
{
    
    CCLog("click hero table back");
    CCDirector::sharedDirector()->popScene();

}


