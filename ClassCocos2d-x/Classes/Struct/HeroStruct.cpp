//
//  HeroStruct.cpp
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-16.
//
//

#include "HeroStruct.h"

void HeroStruct::setData(CCDictionary* pDictData)
{
    MODEL_SET_INTEGER(id, pDictData, this);
    MODEL_SET_STRING(name, pDictData, this);
    MODEL_SET_STRING(q, pDictData, this);
    MODEL_SET_STRING(w, pDictData, this);
    MODEL_SET_STRING(e, pDictData, this);
    MODEL_SET_STRING(r, pDictData, this);
    MODEL_SET_INTEGER(attackQ, pDictData, this);
    MODEL_SET_INTEGER(attackW, pDictData, this);
    MODEL_SET_INTEGER(attackE, pDictData, this);
    MODEL_SET_INTEGER(attackR, pDictData, this);
    MODEL_SET_INTEGER(defense, pDictData, this);
}

bool HeroStruct::init()
{
    do {
        id = 0;
        
        //
        name = "";
        
        //
        q = "";
        //
        w = "";
        //
        e = "";
        //
        r = "";
        
        //
        attackQ = 0;
        //
        attackW = 0;
        //
        attackE = 0;
        //
        attackR = 0;
        
        //
        defense = 0;
        
    } while (0);
    
    return true;
}