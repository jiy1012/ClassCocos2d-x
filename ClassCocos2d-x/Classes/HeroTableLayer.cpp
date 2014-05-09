//
//  HeroTableLayer.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-9.
//
//

#include "HeroTableLayer.h"


USING_NS_CC;
USING_NS_CC_EXT;

void runTableViewTest()
{
	CCScene *pScene = CCScene::create();
	HeroTableLayer *pLayer = HeroTableLayer::create();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

// on "init" you need to initialize your instance
bool HeroTableLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(winSize.width/5*4, winSize.height/2));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(20,winSize.height/2-30));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
    return true;
}



void HeroTableLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

CCSize HeroTableLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(60, 60);
}

CCTableViewCell* HeroTableLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        CCSprite *sprite = CCSprite::create("Icon.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite);
        
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", 20.0);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    
    return cell;
}

unsigned int HeroTableLayer::numberOfCellsInTableView(CCTableView *table)
{
    return 20;
}
