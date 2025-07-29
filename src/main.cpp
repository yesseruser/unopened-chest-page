/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyRewardsPage : Modify<MyMenuLayer, MenuLayer> {};
 */
#include <Geode/modify/SecretRewardsLayer.hpp>
#include <Geode/modify/GJChestSprite.hpp>
class $modify(MyRewardsPage, SecretRewardsLayer) {
    void createSecondaryLayer(int p0) {
        log::info("onChestType started");
        SecretRewardsLayer::createSecondaryLayer(p0);
        log::info("onChestType base called");
        // createQuickPopup("", "", "", "m", [](auto, bool b2){});
        const auto scrollLayer = m_secondaryScrollLayer;
        log::info("onChestType scrollLayer obtained");
        if (scrollLayer == nullptr) {
            log::error("onChestType scrollLayer is null");
            return;
        }
        const auto pages = scrollLayer->getChildByType<ExtendedLayer>(0);
        log::info("onChestType pages ExtendedLayer obtained");
        const auto page_count = pages->getChildrenCount();
        log::info("onChestType page count obtained");
        int first_unopened_page = -1;
        for (int i = 0; i < page_count; i++) {
            const auto page = pages->getChildByType<CCLayer>(i)->getChildByType<CCMenu>(0);
            log::info("onChestType page {} obtained", i);
            for (int j = 0; j < page->getChildrenCount(); j++) {
                const auto chest = page->getChildByType<CCMenuItemSpriteExtra>(j)->getChildByType<GJChestSprite>(0);
                log::info("onChestType page {} chest {} obtained", i, j);
                if (isChestClosed(chest)) {
                    log::info("onChestType page {} chest {} not opened", i, j);
                    first_unopened_page = i;
                    break;
                }

                if (first_unopened_page != -1) {break;}
            }
        }
        log::info("onChestType first unopened page obtained: {}", first_unopened_page);

        if (first_unopened_page != -1) {
            for (int i; i <= first_unopened_page; i++) {
                
            }
        }
    }

    bool isChestClosed(GJChestSprite *chest) {
        if (chest == nullptr) {
            log::info("isChestOpen chestSprite is null");
            return false;
        }
        switch (chest->m_spriteState) {
            case ChestSpriteState::Opened:
                log::info("isChestOpen chestSprite state: Opened");
                break;
            case ChestSpriteState::Opening:
                log::info("isChestOpen chestSprite state: Opening");
                break;
            case ChestSpriteState::Closed:
                log::info("isChestOpen chestSprite state: Closed");
                return true;
            case ChestSpriteState::Locked:
                log::info("isChestOpen chestSprite state: Locked");
                break;
        }
        return false;
    }
};
