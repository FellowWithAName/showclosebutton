#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

// Give the hook a custom name (MyMenuLayer) so the compiler can find the new function
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto closeSprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSprite,
            this,
            menu_selector(MyMenuLayer::onCustomQuit) // Changed to MyMenuLayer::
        );

        auto menu = CCMenu::create();
        menu->addChild(closeBtn);
        
        // Positioned at the top-left corner
        menu->setPosition({25.f, winSize.height - 25.f});
        menu->setID("close-button-menu"_spr);

        this->addChild(menu);

        return true;
    }

    // This custom function is now properly recognized under MyMenuLayer
    void onCustomQuit(CCObject* sender) {
        this->onQuit(sender);
    }
};
