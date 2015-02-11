#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>

#include <SFML-Book/client/Client.hpp>
#include <SFML-Book/client/Gui.hpp>

#include <SFML-utils/Map.hpp>

namespace book
{
    class Game
    {
        public:
            Game(const Game&) = delete;
            Game& operator=(const Game&) = delete;

            Game(int X=1600, int Y=900);
            ~Game();

            bool connect(const sf::IpAddress& ip, unsigned short port,sf::Time timeout=sf::Time::Zero);

            void run(int frame_per_seconds=60);

        private:
            void processEvents();
            void processNetworkEvents();
            void update(sf::Time deltaTime);
            void render();
            
            sf::RenderWindow _window;
            sf::Sprite _cursor;

            Client _client;
            bool _isConnected;

            enum Status {
                StatusMainMenu,
                StatusInGame,
                StatusDisconnected
            } _status;

            MainMenu _mainMenu;

            sfutils::VMap* _map;
            sfutils::MapViewer* _viewer;

    };
}
#endif