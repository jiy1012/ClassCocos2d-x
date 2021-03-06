#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "CommonConfig.h"
#include <spine/Json.h>
#include "DWSScene.h"
#include "DatabaseDefault.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    
    /*
     HelloWorld();
    ~HelloWorld();
    */
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void startGame(CCObject* pSender);
    
    void backCallback(CCObject* pSender);
    
    void HeroClick(CCObject* pSender);
    
    void checkUpdate(CCObject* pSender);
    void checkUpdateResponse(CCHttpClient *sender, CCHttpResponse *response);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void sloganDisplayCallback(CCNode* pNode);
    void logoDisplayCallback(CCNode* pNode);
    
    void titleDisplayCallback(CCNode* pNode);
    
    void loadConfig();
    
    CCSize winSize;
    
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    
};

#endif // __HELLOWORLD_SCENE_H__
