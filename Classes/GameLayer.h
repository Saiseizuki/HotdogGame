#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"

class GameLayer : public cocos2d::CCLayer
{
public:
    GameSprite* hotdogSprite;
    CCSequence* sequence;
    
    ~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    virtual void keyBackClicked();
    
    virtual void ccTouchesBegan(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    
    void update (float dt);
    
    void pokeTheHotdog();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

};

#endif // __GAMELAYER_H__
