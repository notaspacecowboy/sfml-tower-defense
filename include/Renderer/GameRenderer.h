//
// Created by Zheng Yang on 20/10/22.
//

#ifndef GAME_GAMERENDERER_H
#define GAME_GAMERENDERER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <boost/signals2.hpp>

namespace game::components {
    class RenderComponent;
    class Text;
}

namespace game::renderer {


/** @brief game drawable renderer
 *
 *  this is the class that manages all the drawable components in game, it sorts drawables based on their render layer
 *  and depth, and sort drawables in the same layer and depth based on their distance to the camera, and render these
 *  drawables to game window every frame
 *
 *  @author Zheng Yang
 */
class GameRenderer: private sf::NonCopyable {

public:

    /** @brief GameRenderer constructor
     *
     *  GameRenderer constructor
     *
     *  @param window game window
     *  @param uiView UI camera
     *  @param gameView game camera
     *
     */
                                                        GameRenderer(sf::RenderWindow& window, sf::View& uiView, sf::View& gameView);


    /** @brief GameRenderer destructor
     *
     *  GameRenderer destructor
     *
     */
                                                        ~GameRenderer();


    /** @brief GameRenderer initializer
     *
     *  call this function before using any APIs provided by game renderer
     *
     */
    void                                                init();


    /** @brief called every frame to render active drawables to game window
     *
     *  do not manually call this API: it is called by game manager every frame to render active drawables to game window
     *
     */
    void                                                draw();


    /** @brief register a drawable component
     *
     *  register a drawable component to active render queue
     *
     *  @param drawable drawable component to be added to the render queue
     */
    void                                                registerDrawable(components::RenderComponent* drawable);


    /** @brief unregister a drawable component
     *
     *  unregister a drawable component from active render queue
     *
     *  @param drawable drawable component to be removed from the render queue
     */
    void                                                unregisterDrawable(components::RenderComponent* drawable);


    /** @brief clear render queue
     *
     *  clear entire render queue
     *
     */
    void                                                clear();


    /** @brief get all active drawables
     *
     *  get all active drawables cached in the render queue
     *
     *  @return a list of all active drawables
     */
    const std::vector<components::RenderComponent*>&    getCurrentDrawables() const;


    /** @brief display fps to the left top corner of screen
     *
     *  call this function to display fps to the left top corner of screen
     *
     */
    void                                                showFPS();

    static const sf::Vector2i                           ReferencedResolution;       /*!< referenced game resolution */

private:


    /** @brief game window resize event handler
     *
     *  callback function for game window resize event
     *
     *  @param width new width
     *  @param height new height
     */
    void                                                onGameWindowResize(int width, int height);

    std::vector<components::RenderComponent*>           mRenderQueue;               /*!< render queue */
    sf::RenderWindow&                                   mWindow;                    /*!< cached game window */
    sf::View&                                           mUICamera;                  /*!< cached UI camera */
    sf::View&                                           mGameCamera;                /*!< cached game camera */

    components::Text*                                   mFpsText;                   /*!< fps text */

    boost::signals2::connection                         mGameWindowResizeListener;  /*!< game window resize event listener */
};
}

#endif //GAME_GAMERENDERER_H
