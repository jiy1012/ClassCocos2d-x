//
//  DefinedBase.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-24.
//
//

#ifndef ClassCocos2d_x_DefinedBase_h
#define ClassCocos2d_x_DefinedBase_h

//类型转换
#define ITOA(i) CCString::createWithFormat("%d",i)->getCString()
#define ATOI(a) CCString::createWithFormat("%s",a)->intValue()

//设置技能图片
#define SET_SKILL_IMG(name) CCSprite::create(name);



#endif
