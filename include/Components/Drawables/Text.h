//
// Created by Zheng Yang on 29/10/22.
//

#ifndef GAME_TEXT_H
#define GAME_TEXT_H

#include "RenderComponent.h"
#include "Renderer/RenderLayer.h"

namespace game::components {

    /** @brief drawable for texts
     *
     *  use this class if you want to draw some text to the target window
     *  must set up a referenced font resource before it can be properly render to the game window
     *
     *  @author Zheng Yang
     */
    class Text: public RenderComponent {
    public:

        /** @brief text constructor
         *
         *  text constructor
         *
         *  @param owner owner of the component
         *  @param layer render layer of quad
         *  @param depth render depth of quad
         */
                                                Text(GameObject& owner, renderer::RenderLayer layer, int depth);


        /** @brief sprite destructor
        *
        *  sprite destructor
        *
        */                                                ~Text() override;

        /** @brief draw quad to screen
        *
        *  do not call it - this function should only be called by game renderer every frame
        *  this is where drawable components actually gets drawed to the screen
        *
        *  @param window the game window to render the quad on
        */
        void                                    draw(sf::RenderWindow &window) override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is enabled
        *
        */
        void                                    onEnable() override;


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically when component is disabled
        *
        */
        void                                    onDisable() override;


        /** @brief set the alpha value of the drawable
        *
        * set the alpha value of the drawable
        *
        * @param alpha 1 means entirely opaque, 0 means entirely transparent
        */
        void                                    setAlpha(float alpha) override;


        /** @brief set the referenced font with its unique identifier
        *
        *  set the font to be used by sprite object - font must exist as long as the sprite uses it
        *
        *  @param tid the unique identifier of the new font
        */
        void                                    setFont(int tid);

        /** @brief set the referenced font
        *
        *  set the font to be used by sprite object - font must exist as long as the sprite uses it
        *
        *  @param font new font
        */
        void                                    setFont(const sf::Font *font);

        /** @brief set text
        *
        *  set the text to be displayed on the screen. set second parameter to be true if you want to adjust the size of
        *  the gameobject to match the size of the text. Otherwise, the text will be wrapped to the next line once it exceedes
        *  the width of the current gameobject
        *
        *  @param newText new text
        *  @param justifyGoSizeToFitText true if you want to adjust the size of the gameobject to match the size of the text
        */
        void                                    setText(std::string newText, bool justifyGoSizeToFitText = false);

        /** @brief set the text size
        *
        *  set the text size of the text object
        *
        *  @param textSize new text size
        */
        void                                    setTextSize(int textSize);

        /** @brief set the color of the drawable
        *
        * set the color of the drawable
        *
        * @param color new color
        */
        void                                    setColor(sf::Color newColor);

        /** @brief set the size of the gameobject to fize the size of the text
        *
        * set the size of the gameobject to fize the size of the text
        *
        */
        void                                    fitText();

    private:


        /** @brief set the size of the text to fize the size of the gameobject, wrap the text if needed
        *
        * set the size of the text to fize the size of the gameobject, wrap the text if needed
        *
        * @param text the text to be wrapped
        * @return the new wrapped text
        */
        sf::String                              wrapText(sf::String text);

        sf::Text                                mText;                      /*!< the actual text provided by sfml */
        const sf::Font*                         mFont;                      /*!< font of the text */
        sf::Vector2f                            mCachedTransformSize;       /*!< cache transform size for optimization */
        sf::String                              mString;                    /*!< the text to be displayed */
        Pivot                                   mCachedPivot;               /*!< my cached pivot */
        float                                   mCachedOffsetY;             /*!< add a default offset to the text on its y-axis */

        static const int                        DefaultFontID;              /*!< default font id if not otherwise defined */
        static const int                        DefaultTextSize;            /*!< default text size if not otherwise defined */
        static const sf::String                 DefaultText;                /*!< default text if not otherwise defined */
    };
}

#endif //GAME_TEXT_H
