//
//  HeroTableLayer.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-9.
//
//

#ifndef __ClassCocos2d_x__HeroTableLayer__
#define __ClassCocos2d_x__HeroTableLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HeroStruct.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HeroTableLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    HeroTableLayer();
    ~HeroTableLayer();
    
    virtual bool init();
    
  
    CREATE_FUNC(HeroTableLayer);
    
    virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
    virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);
    virtual cocos2d::CCSize tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);
    
    void heroSelect(CCObject* pSender);
    void backClick(CCObject* pSender);
    void heroCancel(CCObject* pSender);
    void startPK(CCObject* pSender);
    
    static int preHeroid;
    
    int heroCount;
    
    int hero1;
    int hero2;
    
    HeroStruct* heroStruct1;
    HeroStruct* heroStruct2;
    
};

#endif /* defined(__ClassCocos2d_x__HeroTableLayer__) */
