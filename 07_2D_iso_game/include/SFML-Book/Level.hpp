#ifndef BOOK_LEVEL_HPP
#define BOOK_LEVEL_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>

#include <SFML-utils/es/Application.hpp>
#include <SFML-utils/Map.hpp>

#include <SFML-Book/Entity.hpp>


namespace book
{
    class Level : private sfutils::Application<Entity>
    {
        public:
            Level(const Level&) = delete;
            Level& operator=(const Level&) = delete;

            Level(sf::RenderWindow& window,const std::string& filename);
            ~Level();

            void update(sf::Time deltaTime);

            bool processEvent(sf::Event& event);
            void processEvents();
            void draw(sf::RenderTarget& window);

            struct Param {
                explicit Param(sf::Vector2i&,
                               Entity&,
                               sfutils::Layer<sfutils::HexaIso,Entity*>&,
                               sfutils::VMap&);

                sf::Vector2i& coord;
                Entity& entity;
                sfutils::Layer<sfutils::HexaIso,Entity*>& layer;
                sfutils::VMap& map;
            };

            using FuncType = std::function<void(Param& param)>;
            static FuncType defaultFunc;

            FuncType onPickup;

            sfutils::EntityManager<Entity>& entityManager();
            Entity& createEntity(const sf::Vector2i& coord);
            sf::Vector2i mapPixelToCoords(const sf::Vector2f& pos)const;
            sf::Vector2f mapCoordsToPixel(const sf::Vector2i& pos)const;
            std::list<Entity*> getByCoords(const sf::Vector2i& coord)const;
            std::list<sf::Vector2i> getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const;


        private:
            friend class Game;

            sfutils::VMap* _map;
            sfutils::MapViewer _viewer;

            sf::ConvexShape* _mouse_light;
            sfutils::Layer<sfutils::HexaIso,sf::ConvexShape>* _mouse_layer;
            sfutils::Layer<sfutils::HexaIso,Entity*>* _entites_layer;
    };
}
#endif
