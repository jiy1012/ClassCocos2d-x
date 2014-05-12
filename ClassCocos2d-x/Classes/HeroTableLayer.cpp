//
//  HeroTableLayer.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-9.
//
//

#include "HeroTableLayer.h"
#include "DatabaseDefault.h"

USING_NS_CC;
USING_NS_CC_EXT;

int HeroTableLayer::preHeroid = 100;

HeroTableLayer::HeroTableLayer()
{
    hero1 = 0;
    hero2 = 0;
}

HeroTableLayer::~HeroTableLayer()
{
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
    tableView->setPosition(ccp(0 , winSize.height/2));
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
    return true;
}



void HeroTableLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    int heroID = cell->getIdx()+preHeroid;
    CCLOG("cell touched at index: %i", cell->getIdx()+preHeroid);
    if (hero1 != 0 && hero2 != 0) {
        return ;
    }
    if (heroID == hero1 || heroID == hero2) {
        return ;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
    CCDictionary* oneHero = (CCDictionary*) groupHero->objectForKey(heroID);
    
    const char* name = ((CCString*) oneHero->objectForKey("name"))->getCString();
    
    CCMenuItemImage* heroButton = CCMenuItemImage::create(CCString::createWithFormat("hero_%s.png",name)->getCString(), CCString::createWithFormat("hero_%s.png",name)->getCString(), this, menu_selector(HeroTableLayer::HeroSelect));
    
    if (hero1 == 0) {
        hero1 = heroID;
        heroButton->setPosition(ccp(winSize.width/2-heroButton->getContentSize().width, 0));
    }else if (hero2 == 0){
        hero2 = heroID;
        heroButton->setPosition(ccp(winSize.width/2+heroButton->getContentSize().width, 0));
    }
    CCLOG("hero1:%d hero2:%d" ,hero1,hero2);
    
    CCMenu* hMenu = CCMenu::create(heroButton,NULL);
    hMenu->setPosition( ccp(0, winSize.height/2-heroButton->getContentSize().height) );
    this->addChild(hMenu);
    
    
}

void HeroTableLayer::HeroSelect(CCObject* pSender)
{
    CCLog("select hero");

}

CCSize HeroTableLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(200, 200);
}

CCTableViewCell* HeroTableLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("%d", idx+preHeroid);

    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
    CCDictionary* oneHero = (CCDictionary*) groupHero->objectForKey(string->intValue());
    
    const char* name = ((CCString*) oneHero->objectForKey("name"))->getCString();
//    const char* heroImage = CCString::createWithFormat("hero_%s.png",name)->getCString();
    
    CCTableViewCell *cell = table->dequeueCell();

    cell = new CCTableViewCell();
    cell->autorelease();
    CCSprite *sprite = CCSprite::create(CCString::createWithFormat("hero_%s.png",name)->getCString());
//    CCLOG("img : %s",heroImage);
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(ccp(0, 0));
    cell->addChild(sprite);
        
    CCLabelTTF *label = CCLabelTTF::create(name, "Helvetica", 20.0);
    label->setPosition(ccp(0,sprite->getContentSize().height));
    label->setAnchorPoint(CCPointZero);
    cell->addChild(label);
    
    return cell;
}

unsigned int HeroTableLayer::numberOfCellsInTableView(CCTableView *table)
{
    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
//    CCLog("numberOfCellsInTableView:%d",groupHero->count());
    return groupHero->count();
}
