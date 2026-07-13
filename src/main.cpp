#include <Geode/modify/MenuLayer.hpp>
#include <Geode/utils/general.hpp>
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

// 1. Give the hook a custom name (MyMenuLayer) so we can reference it in menu_selector
class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // On desktop, GD already adds its own close button to the main menu.
        // If it's there, we don't need to add another one.
        if (this->getChildByID("close-menu")) {
            return true;
        }

        auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        // Never assume a sprite frame exists - bail out safely if it's missing.
        if (!closeSpr) {
            return true;
        }

        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSpr,
            this,
            menu_selector(MyMenuLayer::onCloseGameButton) // 2. Changed from MenuLayer:: to MyMenuLayer::
        );
        closeBtn->setID("show-close-button-btn"_spr);

        auto menu = CCMenu::create();
        menu->setID("show-close-button-menu"_spr);
        menu->addChild(closeBtn);
        // Bottom-left corner of the screen, matching where GD normally
        // places the close button on desktop.
        menu->setPosition({ 30.f, 30.f });

        this->addChild(menu);

        return true;
    }

    void onCloseGameButton(CCObject*) {
        createQuickPopup(
            "Close Game",
            "Are you sure you want to <cr>close</c> the game?",
            "Cancel",
            "Close",
            [](FLAlertLayer* layer, bool btn2) { // 3. Changed 'auto' to 'FLAlertLayer*' to make MSVC happy
                if (btn2) {
                    geode::utils::game::exit(true); // 4. Added 'true' so the game saves data before exiting
                }
            }
        );
    }
};