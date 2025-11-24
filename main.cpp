#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "game.h"

// wymiary okna
const unsigned int width = 640;
const unsigned int height = 480;

enum class GameState { Menu, Playing, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Arkanoid");

    window.setFramerateLimit(60);

    Menu menu(width, height);
    Game game;

    GameState currentState = GameState::Menu;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (currentState == GameState::Menu) {
                    if (event.key.code == sf::Keyboard::Up) menu.przesunG();
                    if (event.key.code == sf::Keyboard::Down) menu.przesunD();
                    if (event.key.code == sf::Keyboard::Enter) {
                        int sel = menu.getSelectedItem();
                        if (sel == 0) currentState = GameState::Playing; // Nowa gra
                        else if (sel == 1) std::cout << "Ostatnie wyniki" << std::endl;
                        else if (sel == 2) window.close(); // Wyjœcie
                    }
                }
            }
        }

        sf::Time dt = clock.restart();

        if (currentState == GameState::Playing)
            game.update(dt, window);

        window.clear(sf::Color(20, 20, 30));

        if (currentState == GameState::Menu)
            menu.draw(window);
        else if (currentState == GameState::Playing)
            game.render(window);

        window.display();
    }

    return 0;
}
