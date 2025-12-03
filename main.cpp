#include <SFML/Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "game.h"

const unsigned int width = 640;
const unsigned int height = 480;

enum class GameMode { Menu, Playing, Exiting };

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(width, height);
    Game game;

    GameMode currentState = GameMode::Menu;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (currentState == GameMode::Menu) {
                    if (event.key.code == sf::Keyboard::Up) menu.przesunG();
                    if (event.key.code == sf::Keyboard::Down) menu.przesunD();
                    if (event.key.code == sf::Keyboard::Enter) {
                        int sel = menu.getSelectedItem();
                        if (sel == 0) {
                            game.reset();
                            currentState = GameMode::Playing;
                            std::cout << "Nowa gra" << std::endl;
                        }
                        else if (sel == 1) {
                            currentState = GameMode::Playing;
                            std::cout << "Wczytano poprzednia gre" << std::endl;
                        }
                        else if (sel == 2) {
                            std::cout << "Ostatnie wyniki" << std::endl;
                        }
                        else if (sel == 3) {
							std::cout << "Menu graficzne zamkniete" << std::endl;
                            window.close();
                        }
                    }
                }
                else if (currentState == GameMode::Playing) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        game.zapiszAktualnyStan();  // zapis stanu gry
                        currentState = GameMode::Menu;  // powrot do menu
                        std::cout << "Powrot do menu (ESC)" << std::endl;
                    }
                }
            }
        }

        sf::Time dt = clock.restart();

        if (currentState == GameMode::Playing)
            game.update(dt, window);

        window.clear(sf::Color(20, 20, 30));

        if (currentState == GameMode::Menu)
            menu.draw(window);
        else if (currentState == GameMode::Playing)
            game.render(window);

        window.display();
    }

    return 0;
}