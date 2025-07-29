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
    void onChestType(CCObject *sender) {
        log::info("onChestType started");
        SecretRewardsLayer::onChestType(sender);
        log::info("onChestType base called");
        // createQuickPopup("", "", "", "m", [](auto, bool b2){});
        const auto scrollLayer = getChildByType<CCLayer>(1)->getChildByType<BoomScrollLayer>(0);
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
            log::info("onChestType page %d obtained", i);
            for (int j = 0; j < page->getChildrenCount(); j++) {
                const auto chest = page->getChildByType<CCMenuItemSpriteExtra>(j)->getChildByType<GJChestSprite>(0);
                log::info("onChestType page %d chest %d obtained", i, j);
                if (!isChestOpen(chest)) {
                    first_unopened_page = i;
                    break;
                }

                if (first_unopened_page != -1) {break;}
            }
        }
        log::info("onChestType first unopened page obtained: %d", first_unopened_page);

        if (first_unopened_page != -1) {
            for (int i; i <= first_unopened_page; i++) {
                
            }
        }
    }

    bool isChestOpen(CCNode *chest) {
        auto chestSprite = dynamic_cast<GJChestSprite *>(chest);
        if (chestSprite == nullptr) { return true; }
        return chestSprite->m_spriteState == ChestSpriteState::Opened;
    }
};
