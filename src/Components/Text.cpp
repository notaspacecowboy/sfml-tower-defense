//
// Created by Zheng Yang on 29/10/22.
//

#include "Components/Drawables/Text.h"
#include <assert.h>
#include <Resource/ResourceManager.h>
#include <Data.h>
#include <Utils/Logger.h>

namespace game::components {
    using namespace game::resource;
    using namespace game::data;

    const int Text::DefaultFontID = 1;
    const int Text::DefaultTextSize = 12;
    const sf::String Text::DefaultText = "This is a placeholder...";

    Text::Text(game::components::GameObject &owner, renderer::RenderLayer layer, int depth)
    : RenderComponent(owner, layer, depth)
    , mFont(nullptr)
    , mString(DefaultText)
    , mCachedTransformSize(mTransform->getSize())
    , mCachedPivot(PIVOT_TOP_LEFT) {
    }

    Text::~Text() noexcept {
    }

    void Text::onEnable() {
        RenderComponent::onEnable();

        if(mFont == nullptr) {
            //set default font
            mFont = FontManager::getInstance().getByID(FONT_GUI_1);
            mText.setCharacterSize(DefaultTextSize);
            mText.setString(mString);
            mText.setFont(*mFont);
        }
    }

    void Text::onDisable() {
        RenderComponent::onDisable();
    }

    void Text::setFont(int tid) {
        setFont(resource::FontManager::getInstance().getByID(tid));
    }

    void Text::setFont(const sf::Font *font) {
        if(mFont == font)
            return;

        mText.setFont(*font);
        mFont = font;
        mText.setString(wrapText(mString));
    }

    void Text::setText(std::string newText, bool justifyGoSizeToFitText) {
        mString = newText;
        if(justifyGoSizeToFitText) {
            fitText();
            mText.setString(mString);
        }
        else
            mText.setString(wrapText(mString));
    }

    void Text::setColor(sf::Color newColor) {
        mText.setFillColor(newColor);
    }

    sf::String Text::wrapText(sf::String text) {
        unsigned offset = 0;
        bool firstWord = true;
        std::size_t wordBeginning = 0;
        int textSize = mText.getCharacterSize();
        int width = mTransform->getSize().x;

        for(std::size_t i = 0; i < text.getSize(); ++i) {
            char current = text[i];
            if(current == '\n') {
                offset = 0;
                firstWord = true;
                continue;
            }
            else if(current == ' ') {
                wordBeginning = i;
                firstWord = false;
            }

            auto glyph = mFont->getGlyph(current, mText.getCharacterSize(), false);
            offset += glyph.advance;

            if(!firstWord && offset > width) {
                i = wordBeginning;
                text[i] = '\n';
                firstWord = true;
                offset = 0;
            }
        }

        return text;
    }

    void Text::setTextSize(int textSize) {
        if(mText.getCharacterSize() == textSize)
            return;

        mText.setCharacterSize(textSize);
        mText.setString(wrapText(mString));
    }

    void Text::fitText() {
        unsigned offset = 0;
        unsigned longestX = 0;
        unsigned longestY = 0;
        int textSize = mText.getCharacterSize();

        for(std::size_t i = 0; i < mString.getSize(); ++i) {
            char current = mString[i];
            if(current == '\n') {
                longestX = (offset > longestX ? offset : longestX);
                offset = 0;
                continue;
            }

            auto glyph = mFont->getGlyph(current, mText.getCharacterSize(), false);
            auto height = glyph.bounds.height;
            longestY = (height > longestY ? height : longestY);
            offset += glyph.advance;
        }
        longestX = (offset > longestX ? offset : longestX);

        mTransform->setSize(longestX, longestY);
    }

    void Text::draw(sf::RenderWindow &window) {
        auto currentSize = mTransform->getSize();
        if(mCachedTransformSize.x != currentSize.x || mCachedTransformSize.y != currentSize.y || mCachedPivot != mTransform->getPivot()) {
            mCachedPivot = mTransform->getPivot();
            mCachedTransformSize = currentSize;
            mText.setString(wrapText(mString));
        }

        auto bound(mText.getLocalBounds());
        mCachedOffsetY = bound.top;

        auto worldPos = mTransform->getWorldPosition();
        worldPos.y -= mCachedOffsetY;
        mText.setPosition(worldPos);

        mText.setRotation(mTransform->getRotate());
        window.draw(mText);
    }

    void Text::setAlpha(float alpha) {
        if(alpha > 1.f || alpha < 0.f) {
            throw std::runtime_error("alpha must be a value between 0 and 1");
        }

        int alphaChannel = 255 * alpha;
        sf::Color currentColor = mText.getFillColor();
        currentColor.a = alphaChannel;
        setColor(currentColor);

    }
}
