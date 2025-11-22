#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "pilka.h"
#include "paletka.h"
#include "cegla.h"

const int ILOSC_KOLUMN = 12;
const int ILOSC_WIERSZY = 4;
float ROZMIAR_BLOKU_X;
float ROZMIAR_BLOKU_Y;
std::vector<Cegla> bloki;

int main() {
    const float WIDTH = 640.f;
    const float HEIGHT = 480.f;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Arkanoid - projekt");
    window.setFramerateLimit(60);

    ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
    ROZMIAR_BLOKU_Y = 20.f;

    Pilka pilka({ 200.f, 200.f }, { 3.f, 3.f }, 10.f); // tworzenie pilki
    Paletka paletka({ WIDTH / 2.f, HEIGHT - 30.f }); // tworzenie paletki

    // ---------------- GENEROWANIE CEGIE£ ---------------- //
    for (int y = 0; y < ILOSC_WIERSZY; y++) {
        for (int x = 0; x < ILOSC_KOLUMN; x++) {
            int zycia = 3;

            float posX = x * (ROZMIAR_BLOKU_X + 2.f);
            float posY = 30.f + y * (ROZMIAR_BLOKU_Y + 2.f);

            bloki.emplace_back(
                sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y),
                zycia
            );
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --------------- GRA --------------- //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            paletka.przesunLewo();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            paletka.przesunPrawo();
        }

        paletka.ograniczRuch(WIDTH);
        pilka.przesun();
        pilka.kolizjaScian(WIDTH, HEIGHT);

        // ----------- KOLIZJA PI£KI Z CEGLAMI ----------- //
        for (auto& cegla : bloki) {
            if (cegla.czyZniszczony()) continue;

            if (cegla.getGlobalBounds().intersects(pilka.getGlobalBounds())) {
                pilka.odbijY();
                cegla.trafienie();
                break;
            }
        }

        // usuwanie zbitych cegie³
        bloki.erase(
            std::remove_if(bloki.begin(), bloki.end(),
                [](const Cegla& cegla) { return cegla.czyZniszczony(); }),
            bloki.end()
        );

        // odbicie pilki od paletki
        sf::Vector2f ballPos = pilka.getPosition();
        sf::Vector2f paddlePos = paletka.getPosition();
        float paddleWidth = paletka.getWidth();
        float paddleHeight = paletka.getHeight();

        if (ballPos.x + pilka.getRadius() >= paddlePos.x - paddleWidth / 2.f &&
            ballPos.x - pilka.getRadius() <= paddlePos.x + paddleWidth / 2.f &&
            ballPos.y + pilka.getRadius() >= paddlePos.y - paddleHeight / 2.f) {
            pilka.odbijY();
        }

        // sprawdzanie czy pilka wypadla
        sf::Vector2f ballPosition = pilka.getPosition();
        if (ballPosition.y - pilka.getRadius() > HEIGHT) {
            std::cout << "KONIEC GRY!" << std::endl;
            window.close();
        }

        // ----- WYŒWIETLANIE ----- //
        window.clear(sf::Color(20, 20, 30));
        paletka.rysuj(window);
        pilka.rysuj(window);

        // ----------- RYSOWANIE CEGIE£ ----------- //
        for (auto& cegla : bloki) {
            if (!cegla.czyZniszczony())
                window.draw(cegla);
        }

        window.display();
    }

    return 0;
}
