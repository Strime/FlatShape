#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

typedef struct {
    CCPoint p1, p2;
} Line;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    virtual void update(float dt);
    bool isInsideScreen(CCPoint p);
    void createLostScene();

    
    //CONSTANTE FOR GRAVITY
    float gravity = 1.12;
    CCPoint velocity = CCPoint(0, -0.2);
    CCPoint jump = CCPoint(9, +10);

    CCSprite* pSprite;
    
    void menuCloseCallback(CCObject* pSender);
    
    Line *lines;
    
    virtual void draw();
};

#endif // __HELLOWORLD_SCENE_H__
