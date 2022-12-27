//
// Created by Zheng Yang on 25/11/22.
//

#ifndef GAME_TOWERSHOP_H
#define GAME_TOWERSHOP_H

#include <Components/Component.h>
#include <Prefabs/TowerShopItemPrefab.h>
#include <Data/TowerDefine.h>
#include <LDtkLoader/Level.hpp>

namespace game::grid {
    class GridSystem;
    class Grid;
}

namespace game::components {
    /** @brief controller class for in-game purchase of towers during gameplay
     *
     *  this is the controller class for in-game purchase of towers during gameplay
     *
     *  @author Zheng Yang
     */
    class TowerShop: public Component {
    public:

        /** @brief TowerShop constructor
         *
         *  TowerShop constructor
         *
         *  @param owner owner of the component
         *  @param layer grid layer
         *  @param renderWindow game window
         *  @param gameCamera game camera
         */
                                                                                TowerShop(GameObject& owner,
                                                                                          grid::GridSystem* system,
                                                                                          sf::RenderWindow* renderWindow,
                                                                                          sf::View* gameCamera);


        /** @brief component lifecycle function
        *
        * component lifecycle function, gets called automatically every frame. This is where every component in the game gets updated
        *
        * @param deltaTime the time elpased between now and last frame
        */
        void                                                                    tick(float deltaTime) override;


        /** @brief load the necessary information of towers in a certain game level
        *
        * load the necessary information of towers in a certain game level
        *
        * @param level the new game level
        */
        void                                                                    loadLevel(const ldtk::Level* level);

        /** @brief call this API to buy a tower
        *
        * call this API to add a tower to map
        *
        */
        void                                                                    BuyTower(data::TowerDefine* define, grid::Grid* grid);
    private:
        sf::RenderWindow*                                                       mGameWindow;                    /*!< cached game window */
        sf::View*                                                               mGameView;                      /*!< cached game camera */
        grid::GridSystem*                                                       mGridSystem;                    /*!< cached grid system */
        const ldtk::Level*                                                      mGameLevel;                     /*!< cached game world data */
        grid::Grid*                                                             mSelectedGrid;                  /*!< selected grid */
        components::GameObject*                                                 mSelectedTowerShopGO;           /*!< cached tower shop go */
    };
}

#endif //GAME_TOWERSHOP_H
