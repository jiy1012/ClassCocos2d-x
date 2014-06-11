//
//  DatabaseDefault.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-30.
//
//

#ifndef __ClassCocos2d_x__DatabaseDefault__
#define __ClassCocos2d_x__DatabaseDefault__

#include "CommonConfig.h"

#include "support/tinyxml2/tinyxml2.h"
using namespace tinyxml2;


class DatabaseDefault : public cocos2d::CCObject
{
public:
    DatabaseDefault();
    ~DatabaseDefault();
    
    static DatabaseDefault* shared();
    
    CCDictionary* getItemById(int itemId);
    CCDictionary* getGroupItemByGroupID(std::string groupName);
    
    CCDictionary* pGroupItem;
    CCDictionary* pHeroItem;
    CCDictionary* pLanguageItem;
    CCDictionary* pSkillItem;
    CCDictionary* pJobItem;
    CCDictionary* pItem;
    const char* pLastGroupName;
    CCDictionary* pLastGroupItem;
    
    
public:
    void loadDatabase();
    void paraXml(XMLElement* Element);

private:
    static DatabaseDefault* s_DatabaseDefault;
    
};



#endif /* defined(__ClassCocos2d_x__DatabaseDefault__) */
