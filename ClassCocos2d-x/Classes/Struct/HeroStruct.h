//
//  HeroStruct.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-16.
//
//

#ifndef __ClassCocos2d_x__HeroStruct__
#define __ClassCocos2d_x__HeroStruct__

#include "StructBase.h"

class HeroStruct : public CCObject
{
public:
    virtual bool init();
    
    CREATE_FUNC(HeroStruct);
    
	void setData(CCDictionary* pDictData);
    
public:
    /*<Hero id="100" name="chan" q="10"  w="10"  e="10"  r="10"  attackQ="10"  attackW="10"  attackE="10"  attackR="10"  defense="10"/>*/
    //
    int id;
    //
    string name;
    
    //
    string q;
    //
    string w;
    //
    string e;
    //
    string r;
    
    //
    int attackQ;
    //
    int attackW;
    //
    int attackE;
    //
    int attackR;
    
    //
    int defense;
    
};

#endif /* defined(__ClassCocos2d_x__HeroStruct__) */
