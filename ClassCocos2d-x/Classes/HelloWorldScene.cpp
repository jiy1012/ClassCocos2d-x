#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object


    /////////////////////////////
    // 3. add your codes below...

    // ask director the window size
    winSize = CCDirector::sharedDirector()->getWinSize();


    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(winSize.width/2, winSize.height/2) );
    

    CCFadeOut* pFadeout = CCFadeOut::create(1.0f);

    CCFiniteTimeAction* pSequence = CCSequence::create(pFadeout,
                                                      CCCallFuncN::create(this,callfuncN_selector(HelloWorld::logoDisplayCallback)),
                                                        NULL);
    pSprite->runAction(pSequence);
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    return true;
}


void HelloWorld::logoDisplayCallback(CCNode* pNode)
{
    CCLOG("%s","logoDisplayCallback pNode");
    CCSprite* pMydraw = CCSprite::create("mydraw.jpg");
    pMydraw->setPosition(ccp(winSize.width/2, winSize.height/2));
    
    CCFadeIn* pFadein = CCFadeIn::create(3.0f);
    CCDelayTime* pDelay = CCDelayTime::create(1.0f);
    CCFadeOut* pFadeout = CCFadeOut::create(3.0f);
    
    CCFiniteTimeAction* pSequence = CCSequence::create(pFadein,
                                                       pDelay,
                                                       pFadeout,
                                                       CCCallFuncN::create(this,callfuncN_selector(HelloWorld::sloganDisplayCallback)),
                                                       NULL);
    
    pMydraw->runAction(pSequence);
    this->addChild(pMydraw);
    
}

void HelloWorld::sloganDisplayCallback(CCNode* pNode)
{
    CCLOG("%s","sloganDisplayCallback");
    CCLabelTTF* pLabel = CCLabelTTF::create("四火品质 坚如磐石", "", 50);

    pLabel->setPosition(ccp(winSize.width/2, winSize.height/2));

    CCFadeIn* pFadein = CCFadeIn::create(3.0f);
    CCFadeOut* pFadeout = CCFadeOut::create(3.0f);
    CCFiniteTimeAction* pSequence = CCSequence::create(pFadein,
                                                       pFadeout,
                                                       CCCallFuncN::create(this,callfuncN_selector(HelloWorld::titleDisplayCallback)),
                                                       NULL);
    pLabel->runAction(pSequence);
    this->addChild(pLabel);
}

void HelloWorld::titleDisplayCallback(CCNode* pNode)
{
    CCLOG("%s","titleDisplayCallback");
    
    CCMenuItemImage* pStratButton = CCMenuItemImage::create("startButton.png", "startButtonSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    pStratButton->setPosition(ccp(winSize.width/2, winSize.height/3));
    
    CCMenuItemImage* pExitButton = CCMenuItemImage::create("exitButton.png", "exitButtonSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    pExitButton->setPosition(ccp(winSize.width/2, winSize.height/5));

    CCMenu* pMenu = CCMenu::create(pStratButton,pExitButton,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("大战", "Thonburi", 50);
    pLabel->setPosition( ccp(winSize.width/2, winSize.height*3/4) );
    this->addChild(pLabel, 1);
    
}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
