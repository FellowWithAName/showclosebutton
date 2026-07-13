#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. Get the dynamic window size of the user's iOS device screen
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // Create the close button sprite (using the classic standard exit look)
        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        
        // Setup the button wrapper and pair it to our custom quit function
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSprite,
            this,
            menu_selector(MenuLayer::onCustomQuit)
        );

        // Put the button inside a custom menu layout wrapper
        auto menu = CCMenu::create();
        menu->addChild(closeBtn);
        
        // 2. Position it at the top-left (25 pixels from left, 25 pixels down from the very top)
        menu->setPosition({25.f, winSize.height - 25.f});
        menu->setID("close-button-menu"_spr);

        // Add our new layer onto the Main Menu
        this->addChild(menu);

        return true;
    }

    // 3. Trigger the standard closing sequence instead of hard-killing the app
    void onCustomQuit(CCObject* sender) {
        // This invokes the vanilla closing layer, which allows "Save on Exit" 
        // to catch the hook cleanly, save your data, and exit smoothly.
        this->onQuit(sender);
    }
};
