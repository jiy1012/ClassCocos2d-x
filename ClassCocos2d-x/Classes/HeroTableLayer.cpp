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
    heroCount = 0;
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
    
    CCMenuItemImage* heroButton = CCMenuItemImage::create(CCString::createWithFormat("hero_%s.png",name)->getCString(), CCString::createWithFormat("hero_%s.png",name)->getCString(), this, menu_selector(HeroTableLayer::heroCancel));
    
    if (hero1 == 0) {
        hero1 = heroID;
        heroButton->setPosition(ccp(winSize.width/2-heroButton->getContentSize().width, 0));
        heroButton->setTag(1);
    }else if (hero2 == 0){
        hero2 = heroID;
        heroButton->setPosition(ccp(winSize.width/2+heroButton->getContentSize().width, 0));
        heroButton->setTag(2);
    }
    CCLOG("hero1:%d hero2:%d" ,hero1,hero2);
    if (0!=hero1 && 0 != hero2) {
        CCMenuItemImage* pStratButton = CCMenuItemImage::create("startPKButton.png", "startPKButtonSelected.png", this, menu_selector(HeroTableLayer::startPK));

        pStratButton->setPosition(ccp(winSize.width/2, -winSize.height/4));

        CCMenu* hMenu = CCMenu::create(heroButton,pStratButton,NULL);
        hMenu->setPosition( ccp(0, winSize.height/2-heroButton->getContentSize().height) );
        this->addChild(hMenu);
    }else{
        CCMenu* hMenu = CCMenu::create(heroButton,NULL);
        hMenu->setPosition( ccp(0, winSize.height/2-heroButton->getContentSize().height) );
        this->addChild(hMenu);
    }
    

    
    
}

void HeroTableLayer::heroSelect(CCObject* pSender)
{


}
void HeroTableLayer::startPK(CCObject* pSender)
{
    CCLOG("startPK hero1:%d hero2:%d" ,hero1,hero2);
    
}
void HeroTableLayer::heroCancel(CCObject* pSender)
{
    CCMenu* selected = (CCMenu*) pSender;
    ;
    if (1 == selected->getTag()) {
        hero1 = 0;
    }else{
        hero2 = 0;
    }
    selected->removeFromParent();
    CCLog("cancel hero ");
    
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
    const char* heroImage = CCString::createWithFormat("hero_%s.png",name)->getCString();
    
    CCTableViewCell *cell = table->dequeueCell();

    cell = new CCTableViewCell();
    cell->autorelease();
//    CCLOG("sprite:%s",heroImage);
    CCSprite* sprite = CCSprite::create(heroImage);
//    CCLOG("img : %s",heroImage);
//    CCLOG("sprite:%f %f",sprite->getContentSize().width,sprite->getContentSize().height);
    
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
    if (heroCount == 0) {
        CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
        heroCount = groupHero->count();
    }
    return heroCount;
//    CCLOG("xml Hero start");
//    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
//    CCLOG("xml Hero end");
//    CCLog("numberOfCellsInTableView:%d",groupHero->count());
//    return groupHero->count();
}
