//
//  StructBase.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-16.
//
//

#ifndef ClassCocos2d_x_StructBase_h
#define ClassCocos2d_x_StructBase_h

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

//  为model封装数据；
//  整型
#define MODEL_SET_INTEGER(key,pDictObj,pModel)\
{\
CCString* pValue = const_cast<CCString*>(pDictObj->valueForKey(#key));\
if (pValue)\
{\
pModel->key = pValue->intValue();\
}else{\
pModel->key = 0;\
}\
}

//  浮点
#define MODEL_SET_FLOAT(key,pDictObj,pModel)\
{\
CCString* pValue = const_cast<CCString*>(pDictObj->valueForKey(#key));\
if (pValue)\
{\
pModel->key = pValue->floatValue();\
}\
}

//  字符串
#define MODEL_SET_STRING(key,pDictObj,pModel)\
{\
CCString* pValue = const_cast<CCString*>(pDictObj->valueForKey(#key));\
if (pValue)\
{\
pModel->key = pValue->getCString();\
}\
}

#endif
