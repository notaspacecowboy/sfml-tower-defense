//
// Created by Zheng Yang on 29/09/22.
//

#ifndef GAME_RESOURCEMANAGER_H
#define GAME_RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Utils/Singleton.h"

namespace game::resource {


    /** @brief all texture identifiers
     *
     *  this enum defines enumerators for all texture identifiers
     *
     *  @author Zheng Yang
     */
    enum TextureType: int {
        TEXTURE_LOADING_SPIN            = 1,    /*!< loading spin */
        TEXTURE_BUTTON_FRAME_1          = 2,    /*!< button frame 1 */
        TEXTURE_BUTTON_FRAME_2          = 3,    /*!< button frame 2 */
        TEXTURE_BG_START                = 4,    /*!< start scene background */
        TEXTURE_BG_MAIN                 = 5,    /*!< main scene background */
        TEXTURE_BUTTON_FRAME_3          = 6,    /*!< button frame 3 */
        TEXTURE_ENEMY_1_IDLE            = 7,    /*!< enemy 1 idle */
        TEXTURE_ENEMY_1_RUN             = 8,    /*!< enemy 1 running */
        TEXTURE_ENEMY_1_WALK            = 9,    /*!< enemy 1 walking */
        TEXTURE_TOWER_1_IDLE            = 10,   /*!< tower 1 idle */
        TEXTURE_SKELETON_DEAD           = 11,   /*!< enemy skelton dying */
        TEXTURE_SKELETON_WALK           = 12,   /*!< enemy skelton walking */
        TEXTURE_ICON_ARROW              = 13,   /*!< arrow icon */
        TEXTURE_ICON_ARROWS             = 14,   /*!< arrows icon */
        TEXTURE_ICON_AX                 = 15,   /*!< axe icon */
        TEXTURE_ICON_BATTLE             = 16,   /*!< battle icon  */
        TEXTURE_ICON_BOMB               = 17,   /*!< bomb icon  */
        TEXTURE_ICON_BOOK_MAGIC         = 18,   /*!< magic book icon  */
        TEXTURE_ICON_BOOK_OPEN          = 19,   /*!< open book icon  */
        TEXTURE_ICON_BOOK_SKILL         = 20,   /*!< skill book icon  */
        TEXTURE_ICON_ARMOR              = 21,   /*!< armor icon  */
        TEXTURE_ITEM_FRAME_1            = 22,   /*!< item frame 1  */
        TEXTURE_ITEM_FRAME_2            = 23,   /*!< item frame 2  */
        TEXTURE_TILESET_1               = 24,   /*!< tileset 1  */
        TEXTURE_ICON_POTION_RED         = 25,   /*!< red potion icon  */
        TEXTURE_ICON_STOPWATCH          = 26,   /*!< stopwatch icon  */
        TEXTURE_ICON_POUCH              = 27,   /*!< pouch icon  */
        TEXTURE_BUTTON_FRAME_RED        = 28,   /*!< ref button frame  */
        TEXTURE_ICON_HOME               = 29,   /*!< home icon  */
        TEXTURE_ICON_POINT              = 30,   /*!< point icon  */
        TEXTURE_TELEVISION              = 31,   /*!< television  */
        TEXTURE_ICON_SHEET              = 32,   /*!< icon sheet  */
        TEXTURE_PROJECTION_1            = 33,   /*!< projection 1  */
        TEXTURE_TILESET_2               = 34,   /*!< tile map 2  */
        TEXTURE_TILESET_3               = 35,   /*!< tile map 2  */
        TEXTURE_TILESET_4               = 36,   /*!< tile map 2  */
    };


    /** @brief all font identifiers
     *
     *  this enum defines enumerators for all font identifiers
     *
     *  @author Zheng Yang
     */
    enum FontType: int {
        FONT_GUI_1                      = 1,    /*!< pixelate gui font 1  */
        FONT_GUI_2                      = 2,    /*!< pixelate gui font 2  */
    };


    /** @brief all sound effect identifiers
     *
     *  this enum defines enumerators for all sound effect identifiers
     *
     *  @author Zheng Yang
     */
    enum SoundBufferType: int {
        SOUND_BUTTON_CLICK_1            = 1,    /*!< button click sound 1  */
    };


    /** @brief manager of all in-game resources
     *
     *  this class manager of all in-game resources - font, texture, sound effect, and provides APIs for user to access
     *  the references of these resources
     *
     *  @author Zheng Yang
     */
    template<typename TResource>
    class ResourceManager: public utils::Singleton<ResourceManager<TResource>> {
        friend class utils::Singleton<ResourceManager<TResource>>;
    public:

        /** @brief resource manager initialization
         *
         *  must call this function before using any API provided by resource manager
         *
         *
         */
        void                                                            init();


        /** @brief load all registered resources
         *
         *  load all registered resources and store them in a list of unique pointers
         *
         */
        void                                                            loadAll();


        /** @brief register a game resource
         *
         *  register a game resource so it can be loaded later
         *
         * @param tid resource id
         * @param resourceName reource name
         * @param path resource path in hard drive
         */
        void                                                            registerResource(std::string resourceName, int tid, std::string path);


        /** @brief get resource by its id
         *
         *  get reference to a resource by its id
         *
         * @param tid resource id
         * @return reference to resource
         */
        TResource*                                                      getByID(int tid) const;


        /** @brief get resource by its name
         *
         *  get reference to a resource by its name
         *
         * @param name resource name
         * @return reference to resource
         */
        TResource*                                                      getByName(std::string name) const;


        /** @brief load a resource by its id
         *
         *  load a resource by its id
         *
         * @param tid resource id
         */
        void                                                            load(int tid);
        //TResource*                                                      get(int tid) const;


        /** @brief check if a resource is loaded
         *
         *  check if a resource is loaded
         *
         * @return true if resource is loaded, false otherwise
         */
        bool                                                            contains(int tid) const;

    private:

        /** @brief private constructor
         *
         *  private constructor to ensure singleton pattern
         *
         */
                                                                        ResourceManager();


        /** @brief load a resource based on its id and path
         *
         *  load a resource based on its id and path
         *
         *  @param tid resource id
         *  @param path resource path in hard drive
         */
        void                                                            load(int tid, const std::string& path);

        std::unordered_map<int, std::unique_ptr<TResource>>             mResources;         /*!< all the loaded resources */
        std::unordered_map<int, std::string>                            mIdToPathMapping;   /*!< resource id to file path mapping */
        std::unordered_map<std::string, int>                            mNameToIdMapping;   /*!< resource name to id mapping */
    };

    typedef ResourceManager<sf::Texture>                                TextureManager;
    typedef ResourceManager<sf::Font>                                   FontManager;
    typedef ResourceManager<sf::SoundBuffer>                            SoundBufferManager;
}

#include "ResourceManager.inl"

#endif //GAME_RESOURCEMANAGER_H
