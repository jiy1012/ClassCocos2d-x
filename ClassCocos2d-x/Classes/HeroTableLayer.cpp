//
//  HeroTableLayer.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-9.
//
//

#include "HeroTableLayer.h"
#include "DatabaseDefault.h"
#include "BattleScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

int HeroTableLayer::preHeroid = 100;

HeroTableLayer::HeroTableLayer()
{
    hero1 = 0;
    hero2 = 0;
    heroCount = 0;
    heroStruct1 = HeroStruct::create() ;
    heroStruct1->retain();
    heroStruct2 = HeroStruct::create() ;
    heroStruct2->retain();
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
    
    CCTableView* tableView = CCTableView::create(this, CCSizeMake(WIN_WIDTH, WIN_HEIGHT/2));
    tableView->setDirection(kCCScrollViewDirectionHorizontal);
    tableView->setPosition(ccp(0 , WIN_HEIGHT/2));
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

    CCMenu* hMenu = CCMenu::create(heroButton,NULL);
    hMenu->setPosition( ccp(0, winSize.height/2-heroButton->getContentSize().height) );
    this->addChild(hMenu);
    
}

//void HeroTableLayer::heroSelect(CCObject* pSender)
//{
//
//
//}

void HeroTableLayer::backClick(CCObject* pSender)
{
    CCLog("click backClick");
    BattleScene::shared()->releaseSelf();
    CCDirector::sharedDirector()->popScene();

}

void HeroTableLayer::startPK(CCObject* pSender)
{
    CCLOG("startPK hero1:%d hero2:%d" ,hero1,hero2);
    if (0 == hero1 || 0 == hero2) {
        return;
    }
    CCDictionary* groupHero = DatabaseDefault::shared()->getGroupItemByGroupID("Hero");
    CCDictionary* h1 = (CCDictionary*) groupHero->objectForKey(hero1);
    CCDictionary* h2 = (CCDictionary*) groupHero->objectForKey(hero2);
    heroStruct1->setData(h1);
    heroStruct2->setData(h2);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize heroSize;
    heroSize.width = winSize.width/2;
    heroSize.height = winSize.height/2;
    
    CCScene* pkScene = CCScene::create();
    pkScene->setContentSize(winSize);
    
    CCScene* hero1Scene = BattleScene::shared()->ShowHero(heroStruct1);
    hero1Scene->setContentSize(heroSize);
    hero1Scene->setPosition(ccp(winSize.width/4, winSize.height/2));
    
    CCScene* hero2Scene = BattleScene::shared()->ShowHero(heroStruct2);
    hero2Scene->setContentSize(heroSize);
    hero2Scene->setPosition(ccp(winSize.width*3/4, winSize.height/2));
    
    CCLabelTTF* skill1 = BattleScene::shared()->setSkillDetail1("");
    skill1->setTag(hero1);
    CCLabelTTF* skill2 = BattleScene::shared()->setSkillDetail2("");
    skill2->setTag(hero2);
    CCLabelTTF* hp1 = BattleScene::shared()->setHP1(ITOA(heroStruct1->HP));
    hp1->setTag(hero1*10);
    CCLabelTTF* hp2 = BattleScene::shared()->setHP2(ITOA(heroStruct2->HP));
    hp2->setTag(hero2*10);
    
    CCLabelTTF* res = BattleScene::shared()->setBattleResult();
    
    CCMenuItemImage* backButton = CCMenuItemImage::create("backButton.png", "backButtonSelected.png", pkScene, menu_selector(HeroTableLayer::backClick));
    CCMenu* pMenu = CCMenu::create(backButton,NULL);
    pMenu->setPosition(ccp(backButton->getContentSize().width, backButton->getContentSize().height/2));
    
    CCLOG("pkx:%f pky:%f h1x:%f h1y:%f h2x:%f h2y:%f",pkScene->getPositionX(),pkScene->getPositionY(),hero1Scene->getPositionX(),hero1Scene->getPositionY(),hero2Scene->getPositionX(),hero2Scene->getPositionY());
    
    pkScene->addChild(hero1Scene);
    pkScene->addChild(hero2Scene);
    pkScene->addChild(pMenu);
    pkScene->addChild(skill1);
    pkScene->addChild(skill2);
    pkScene->addChild(res);
    pkScene->addChild(hp1);
    pkScene->addChild(hp2);
    CCLOG("%s   pk    %s",heroStruct1->name.c_str(),heroStruct2->name.c_str());
    CCDirector::sharedDirector()->pushScene(pkScene);
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
    
    CCLog("cancel hero %d",selected->getTag());
    selected->removeFromParent();    
}

CCSize HeroTableLayer::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
//    CCLOG("cell :%f %f",WIN_WIDTH/4,WIN_HEIGHT/2);
    return CCSizeMake(WIN_WIDTH/4, WIN_HEIGHT/2);
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

    CCSprite* sprite = CCSprite::create(heroImage);
    CCLabelTTF* label = CCLabelTTF::create(name, "Helvetica", 20.0);
    
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(ccp(0, 0));
    
    float scalex = WIN_WIDTH/4/sprite->getContentSize().width;
    float scaley = WIN_HEIGHT/2/(sprite->getContentSize().height+label->getContentSize().height);
    int scale = GET_MIN(scalex, scaley);
    
    sprite->setScale(scale);
    
    cell->addChild(sprite);
        
    label->setAnchorPoint(CCPointZero);
    label->setPosition(ccp(0,sprite->getContentSize().height*scale));

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
