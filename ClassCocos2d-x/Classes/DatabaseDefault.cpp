//
//  DatabaseDefault.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-4-30.
//
//

#include "DatabaseDefault.h"

DatabaseDefault* DatabaseDefault::s_DatabaseDefault = NULL;

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
//    std::string logStr;
//    logStr = std::string(Element->Name());
    while (attr) {
//        logStr += " "+std::string(attr->Name())+"="+std::string(attr->Value())+" ";
        attr = attr->Next();
    }
//    CCLog("%s",logStr.c_str());
    XMLElement* value = Element->FirstChildElement();
    while (value) {
        paraXml(value);
        value = value->NextSiblingElement();
    }
}