#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

std::string version = "1.0000.2";
bool debug = false;
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
    
    float expire = 1.0f;
    if (true == debug) {
        expire = 0.1f;
    }
    CCFadeOut* pFadeout = CCFadeOut::create(expire);

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
    
    float expire = 3.0f;
    if (true == debug) {
        expire = 0.1f;
    }
    
    CCFadeIn* pFadein = CCFadeIn::create(expire);
    CCDelayTime* pDelay = CCDelayTime::create(expire);
    CCFadeOut* pFadeout = CCFadeOut::create(expire);
    
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

    float expire = 3.0f;
    if (true == debug) {
        expire = 0.1f;
    }
    
    CCFadeIn* pFadein = CCFadeIn::create(expire);
    CCFadeOut* pFadeout = CCFadeOut::create(expire);
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
    
    CCMenuItemImage* pStratButton = CCMenuItemImage::create("startButton.png", "startButtonSelected.png", this, menu_selector(HelloWorld::startGame));
    
    pStratButton->setPosition(ccp(winSize.width/6, winSize.height/3));
    
    CCMenuItemImage* pExitButton = CCMenuItemImage::create("exitButton.png", "exitButtonSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    pExitButton->setPosition(ccp(winSize.width/2, winSize.height/3));

    CCMenuItemImage* pCheckVersion = CCMenuItemImage::create("checkUpdate.png", "checkUpdateSelected.png", this, menu_selector(HelloWorld::checkUpdate));
    pCheckVersion->setPosition(ccp(winSize.width/6*5, winSize.height/3));
    
    
    CCMenu* pMenu = CCMenu::create(pStratButton,pExitButton,pCheckVersion,NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("大战", "Thonburi", 50);
    pLabel->setPosition( ccp(winSize.width/2, winSize.height*3/4) );
    this->addChild(pLabel, 2);
    
    std::string labelV = "当前版本："+version;
    CCLabelTTF* pLabelV = CCLabelTTF::create(labelV.c_str(), "Thonburi", 25);
    pLabelV->setPosition( ccp(pLabelV->getContentSize().width/2,pLabelV->getContentSize().height/2) );
    this->addChild(pLabelV, 3);
    
}

void HelloWorld::startGame(CCObject* pSender)
{
    CCLog("start game");
}
void HelloWorld::checkUpdate(CCObject* pSender)
{
    CCLog("check version:%s",version.c_str());
    CCHttpRequest* request = new CCHttpRequest();
    request->setUrl("http://5461.sinaapp.com/checkversion.php");
    request->setRequestType(CCHttpRequest::kHttpPost);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::checkUpdateResponse));
    
    const char* postData = "game=class";
    request->setRequestData(postData, strlen(postData));
    
    request->setTag("POST check version");
    CCHttpClient::getInstance()->send(request);
    request->release();
}



void HelloWorld::checkUpdateResponse(CCHttpClient *sender, CCHttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        CCLog("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    CCLog("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        CCLog("response failed");
        CCLog("response failed buffer: %s", response->getErrorBuffer());
        return;
    }
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    
//    std::string res;
//    res.assign(buffer->begin(),buffer->end());
//    CCLog("response data: %lu %s \n",buffer->size(),res.c_str());
    
    char const* json = &(*buffer->begin());
    Json* resJson = Json_create(json);
    
    const char* versionRes = Json_getString(resJson, "version",0);
    const char* updateUrl = Json_getString(resJson, "updateUrl", 0);
    
    CCLog("ver:%s updateUrl:%s" , versionRes,updateUrl);
    
    CCScene* checkRes = CCScene::create();
    
    std::string text ="当前已经是最新版本";
    
    if (strcmp(versionRes, version.c_str()) != 0 )
    {
        text = versionRes;
        text = "发现新版本" + text ;
    }
    
    CCLabelTTF* label = CCLabelTTF::create(text.c_str() , "", 50);
    label->setPosition(ccp(winSize.width/2,winSize.height/2 ));
    CCMenuItemImage* backButton = CCMenuItemImage::create("backButton.png", "backButtonSelected.png", this, menu_selector(HelloWorld::backCallback));
    backButton->setPosition(ccp(winSize.width-backButton->getContentSize().width, backButton->getContentSize().height));
    checkRes->addChild(label);
    CCMenu* bMenu = CCMenu::create(backButton,NULL);
    bMenu->setPosition( CCPointZero );
    checkRes->addChild(bMenu);
    CCDirector::sharedDirector()->pushScene(checkRes);
//    checkRes->release();
}

void HelloWorld::backCallback(CCObject* pSender)
{
    CCLog("back button click");
    CCDirector::sharedDirector()->popScene();

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
