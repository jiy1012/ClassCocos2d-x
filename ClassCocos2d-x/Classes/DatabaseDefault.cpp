//
//  DatabaseDefault.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-30.
//
//

#include "DatabaseDefault.h"

DatabaseDefault* DatabaseDefault::s_DatabaseDefault = NULL;

DatabaseDefault::DatabaseDefault()
{
    pGroupItem = new CCDictionary();
    pGroupItem->retain();
    pHeroItem = new CCDictionary();
    pHeroItem->retain();
    pLanguageItem = new CCDictionary();
    pLanguageItem->retain();
    pSkillItem = new CCDictionary();
    pSkillItem->retain();
    pJobItem = new CCDictionary();
    pJobItem->retain();
    
    pItem = new CCDictionary();
    pItem->retain();
    pLastGroupItem = new CCDictionary();
    pLastGroupItem->retain();
    
    pLastGroupName = "";

}

DatabaseDefault::~DatabaseDefault()
{
    CC_SAFE_DELETE(pGroupItem);
    CC_SAFE_DELETE(pItem);
    CC_SAFE_DELETE(pLastGroupItem);
}

DatabaseDefault* DatabaseDefault::shared()
{
    if (NULL == s_DatabaseDefault) {
        s_DatabaseDefault = new DatabaseDefault();
        s_DatabaseDefault->loadDatabase();
    }
    return s_DatabaseDefault;
}

void DatabaseDefault::loadDatabase()
{
    std::string  path = CCFileUtils::sharedFileUtils()->fullPathForFilename("database.xml");
    XMLDocument xml;
    xml.LoadFile(path.c_str());
    
    XMLElement* rootElement = xml.RootElement();
    XMLElement* groupElement = rootElement->FirstChildElement();
    
    while (groupElement) {
        paraXml(groupElement);
        groupElement = groupElement->NextSiblingElement();
    }
    
    
    
}

void DatabaseDefault::paraXml(XMLElement* Element)
{
    const XMLAttribute* attr = Element->FirstAttribute();
    std::string elementName = std::string(Element->Name());
    CCDictionary* dictRoot = new CCDictionary();
    CCDictionary* dictAttr = new CCDictionary();
//    std::string logStr;
//    logStr = std::string(Element->Name());
    while (attr) {
        dictAttr->setObject(CCString::create(attr->Value()), attr->Name());
//        logStr += " "+std::string(attr->Name())+"="+std::string(attr->Value())+" ";
        attr = attr->Next();
    }
//    CCLog("%s",logStr.c_str());
    dictRoot->setObject(dictAttr, Element->Name());
    if (strcmp(Element->Name(), "Group") == 0) {
        // get group attr @todo liuyi
        pLastGroupName = dictAttr->valueForKey("id")->getCString();
    }else{
        if (strcmp(pLastGroupName, Element->Name()) == 0) {
            if (strcmp(pLastGroupName, "Hero") == 0) {
                CCLog("H:%s %d %d",pLastGroupName,dictAttr->count(),dictAttr->valueForKey("id")->intValue());
                pHeroItem->setObject(dictAttr, dictAttr->valueForKey("id")->intValue());
            }else if (strcmp(pLastGroupName, "Language") == 0){
                CCLog("L:%s %d %d",pLastGroupName,dictAttr->count(),dictAttr->valueForKey("id")->intValue());
                pLanguageItem->setObject(dictRoot, dictAttr->valueForKey("id")->intValue());
            }else if (strcmp(pLastGroupName, "Skill") == 0){
                CCLog("S:%s %d %d",pLastGroupName,dictAttr->count(),dictAttr->valueForKey("id")->intValue());
                pSkillItem->setObject(dictRoot, dictAttr->valueForKey("id")->intValue());
            }else if (strcmp(pLastGroupName, "Job") == 0){
                CCLog("J:%s %d %d",pLastGroupName,dictAttr->count(),dictAttr->valueForKey("id")->intValue());
                pJobItem->setObject(dictRoot, dictAttr->valueForKey("id")->intValue());
            }
//            if (strcmp(pLastGroupName, "")!=0) {
//                CCLog("LAST: %s,%d",pLastGroupName,pLastGroupItem->count());
//                pGroupItem->setObject(pLastGroupItem, pLastGroupName);
//            }
//            pLastGroupName = Element->Name();
//            pLastGroupItem = new CCDictionary();
        }
//        CCLog("SETLAST: %s,%d",pLastGroupName,dictAttr->valueForKey("id")->intValue());
//        pLastGroupItem->setObject(dictRoot, dictAttr->valueForKey("id")->intValue());
        pItem->setObject(dictRoot, dictAttr->valueForKey("id")->intValue());
    }
    XMLElement* value = Element->FirstChildElement();
    while (value) {
        paraXml(value);
        value = value->NextSiblingElement();
    }
}

CCDictionary* DatabaseDefault::getGroupItemByGroupID(std::string groupName)
{
    if (strcmp(groupName.c_str(), "Hero") == 0) {
        return pHeroItem;
    }else if (strcmp(groupName.c_str(), "Language") == 0){
        return pLanguageItem;
    }else if (strcmp(groupName.c_str(), "Skill") == 0){
        return pSkillItem;
    }else if (strcmp(groupName.c_str(), "Job") == 0){
        return pJobItem;
    }
    return pHeroItem;
//    return (CCDictionary*) pGroupItem->objectForKey(groupName);
}

