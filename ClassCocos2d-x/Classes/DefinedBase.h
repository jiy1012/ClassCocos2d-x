//
//  DefinedBase.h
//  ClassCocos2d-x
//
//  Created by liuyi on 14-5-24.
//
//

#ifndef ClassCocos2d_x_DefinedBase_h
#define ClassCocos2d_x_DefinedBase_h

//获取屏幕长宽
#define WIN_WIDTH CCDirector::sharedDirector()->getWinSize().width
#define WIN_HEIGHT CCDirector::sharedDirector()->getWinSize().height


//类型转换
#define ITOA(i) CCString::createWithFormat("%d",i)->getCString()
#define ATOI(a) CCString::createWithFormat("%s",a)->intValue()

//设置技能图片
#define SET_SKILL_IMG(name) CCSprite::create(name);

//返回最大值
#define GET_MAX(a,b) ((a)>(b)?(a):(b))
//返回最小值
#define GET_MIN(a,b) ((a)<(b)?(a):(b))

#endif
