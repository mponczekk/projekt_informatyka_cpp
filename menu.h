#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

#define MAX_LICZBA_POZIOMOW 3

class Menu {
private:
    sf::Font font;
    sf::Text menu[MAX_LICZBA_POZIOMOW];
    int selectedItem = 0;

public:
    Menu(float width, float height) {
        if (!font.loadFromFile("Chunkfive Ex.ttf")) {
            std::cerr << "Blad! Brak pliku z czcionka";
            return;
        }

        menu[0].setFont(font); menu[0].setFillColor(sf::Color(255, 165, 0)); menu[0].setString("Nowa gra");
        menu[1].setFont(font); menu[1].setFillColor(sf::Color::White); menu[1].setString("Wczytaj gre");
        menu[2].setFont(font); menu[2].setFillColor(sf::Color::White); menu[2].setString("Wyjscie");

        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
            menu[i].setOrigin(
                menu[i].getLocalBounds().left + menu[i].getLocalBounds().width / 2.f,
                menu[i].getLocalBounds().top + menu[i].getLocalBounds().height / 2.f
            );
            menu[i].setPosition(width / 2.f, height / (MAX_LICZBA_POZIOMOW + 1) * (i + 1));
        }
    }

    void przesunG() {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem--;
        if (selectedItem < 0) selectedItem = MAX_LICZBA_POZIOMOW - 1;
        menu[selectedItem].setFillColor(sf::Color(255, 165, 0));
    }

    void przesunD() {
        menu[selectedItem].setFillColor(sf::Color::White);
        menu[selectedItem].setStyle(sf::Text::Regular);
        selectedItem++;
        if (selectedItem >= MAX_LICZBA_POZIOMOW) selectedItem = 0;
        menu[selectedItem].setFillColor(sf::Color(255, 165, 0));
    }

    int getSelectedItem() const { return selectedItem; }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < MAX_LICZBA_POZIOMOW; i++) {
            window.draw(menu[i]);
        }
    }
};