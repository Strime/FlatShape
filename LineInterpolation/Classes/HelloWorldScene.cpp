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
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 60, 60) );
    pCloseItem->setTag(1);
    pCloseItem->setScale(2.5f);
    
    CCMenuItemImage *pCloseItem1 = CCMenuItemImage::create("CloseNormal.png",
                                                           "CloseSelected.png",
                                                           this,
                                                           menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem1->setPosition( ccp(60, 60) );
    pCloseItem1->setTag(2);
    pCloseItem1->setScale(2.5f);

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem1, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);   

    pSprite = CCSprite::create("player.png");
    pSprite->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2,
                              CCDirector::sharedDirector()->getWinSize().height) );
    pSprite->setTag(-1);
    this->addChild(pSprite, 0);
    
    lines = (Line *)malloc(sizeof(Line) * 4);
    
    
    
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt) {
    CCPoint p = pSprite->getPosition();
    
    // use a gravity velocity that "feels good" for your app
    CCPoint gravity = CCPoint(0, -0.2);
    
    // update velocity with gravitational influence
    velocity.y += gravity.y;
    
    // update velocity with "frottement" influence
    if(velocity.x < 0){
        velocity.x += 0.3;
    } else if(velocity.x > 0) {
        velocity.x -= 0.3;
    }
    
    p.y += velocity.y;
    p.x += velocity.x;
    
    if(!isInsideScreen(p)){
        createLostScene();
        this->unscheduleUpdate();
    }
    pSprite->setPosition(p);
}

bool HelloWorld::isInsideScreen(CCPoint p) {
    if(p.x < 0 || p.y < 0 ||
       p.x > CCDirector::sharedDirector()->getWinSize().width ||
       p.y > CCDirector::sharedDirector()->getWinSize().height ) {
        return false;
    }
    return true;
}


void HelloWorld::createLostScene() {
    printf("FINISHED !");
    CCLabelTTF* ttf1 = CCLabelTTF::create("Finished", "Helvetica", 30,
                                          CCSizeMake(245, 120), kCCTextAlignmentCenter);
    ttf1->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width/2,
                              CCDirector::sharedDirector()->getWinSize().height/2));
    
    this->addChild(ttf1);

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCPoint p = pSprite->getPosition();
    velocity.y += jump.y;
    
    if (((CCNode *)pSender)->getTag() == 1) {
        velocity.x = jump.x;
    } else {
        velocity.x = -jump.x;
    }
}

void HelloWorld::draw() {
    glLineWidth(4.0);
    for (int i = 0; i < 4; i++) {
        //ccDrawLine( lines[i].p1, lines[i].p2 );
    }
    CCLayer::draw();
}



