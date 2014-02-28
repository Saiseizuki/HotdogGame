#include "GameLayer.h"
#include "GameSprite.h"

USING_NS_CC;

CCSequence* tibokSequence;
bool isHeld;

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // set background color of the whole scene
    // layer->initWithColor(ccc4(255,25 5,255,255));
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

GameLayer::~GameLayer(void){
    tibokSequence->release();
    tibokSequence = NULL;
    
    isHeld = NULL;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameLayer::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    // add da hotdog
    //CCSprite* backGroundSprite = CCSprite::create("background.jpg");
   
    GameSprite* backGroundSprite = GameSprite::gameSpriteWithFile("background.jpg");
    backGroundSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    float scaleX = visibleSize.width/backGroundSprite->boundingBox().size.width;
    float scaleY = visibleSize.height/backGroundSprite->boundingBox().size.height;
    
    CCLOG("%f",backGroundSprite->boundingBox().size.height);
    CCLOG("%f",backGroundSprite->boundingBox().size.width);
    CCLOG("%f",visibleSize.height);
    CCLOG("%f",visibleSize.width);

    //backGroundSprite->setScale(backGroundSprite->getScale());
    backGroundSprite->cocos2d::CCNode::setScale(scaleX, scaleY);
    this->addChild(backGroundSprite,0);
    
    // add da hotdog
    //CCSprite* hotdogSprite = CCSprite::create("Hotdog.png");
    this->hotdogSprite = GameSprite::gameSpriteWithFile("Hotdog.png");
    this->hotdogSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    float hotDogScaleX = (visibleSize.width/8)/hotdogSprite->boundingBox().size.width;
    
    this->hotdogSprite->CCNode::setScale(hotDogScaleX);
    
    this->addChild(hotdogSprite,0);
    
    tibokSequence = CCSequence::create(CCScaleBy::create(0.125f, 1.111f),
                                              CCScaleBy::create(0.125f, 0.9f)
                                              ,NULL);
    tibokSequence->retain();
    
    isHeld = false;
    
    
    
    CCLOG("%s","Sequence object created");
    
    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);
    
    //pokeTheHotdog();
    
    // Code for forever beating animation loop
//    CCSequence* sequence = CCSequence::create(
//                                              CCScaleBy::create(0.125f, 1.111f),
//                                              CCScaleBy::create(0.125f, 0.9f),
//                                              NULL
//                                              );
//    
//    CCRepeatForever* beatingSequence = CCRepeatForever::create(sequence);
//    this->hotdogSprite->runAction(beatingSequence);
    return true;
}

void GameLayer::keyBackClicked(){
    CCDirector::sharedDirector()->end();
    #if (CC_TARGET_PLATFORM == CC_TARGET_PLATFORM_IOS)
        exit(0);
    #endif
}

void GameLayer::update(float dt){

}

void GameLayer::pokeTheHotdog(){
    //if(sequence->isDone()){
//    this->hotdogSprite->runAction(CCSequence::create(CCScaleBy::create(0.125f, 1.111f),
//                                                     CCScaleBy::create(0.125f, 0.9f)
//                                                     ,NULL));
    CCLOG("Elapsed is %f",tibokSequence->getElapsed());
    if(tibokSequence->isDone() || (tibokSequence->getElapsed() <= 0.000001f && tibokSequence->getElapsed() >= -0.000001f)){
        CCLOG("Runningaction");
        this->hotdogSprite->runAction(tibokSequence);
    }
    //}
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent){
    for(auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
        auto touch = dynamic_cast<CCTouch*>(*it);
        if(touch == NULL)
            break;
        
        if(this->hotdogSprite->boundingBox().containsPoint(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()))){
            pokeTheHotdog();
            isHeld=true;
        }
//        else{
//            this->hotdogSprite->setPosition(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
//        }
    };
}
void GameLayer::ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent){
    for(auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
        auto touch = dynamic_cast<CCTouch*>(*it);
        if(touch == NULL)
            break;
        if(this->hotdogSprite->boundingBox().containsPoint(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView())) || isHeld){
            this->hotdogSprite->setPosition(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
        }
       
    };
}
void GameLayer::ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent){
    //pokeTheHotdog();
    for(auto it = pTouches->begin(); it != pTouches->end(); it++)
    {
       
        auto touch = dynamic_cast<CCTouch*>(*it);
        if(touch == NULL)
            break;
        isHeld=false;
//        if(this->hotdogSprite->boundingBox().containsPoint(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()))){
//        //    pokeTheHotdog();
//        }else{
//            this->hotdogSprite->setPosition(CCDirector::sharedDirector()->convertToGL(touch->getLocationInView()));
//        }
    };
}

void GameLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
