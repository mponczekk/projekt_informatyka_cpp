#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "gamestate.h"


class Game {
private:
    Pilka m_pilka;
    Paletka m_paletka;
    std::vector<Cegla> m_bloki;
    GameState m_gameState;

    const int ILOSC_KOLUMN = 12;
    const int ILOSC_WIERSZY = 4;
    float m_blockWidth;
    float m_blockHeight;

    void generateBricks() {
        for (int y = 0; y < ILOSC_WIERSZY; y++)
            for (int x = 0; x < ILOSC_KOLUMN; x++)
                m_bloki.emplace_back(
                    sf::Vector2f(x * (m_blockWidth + 2.f), 30.f + y * (m_blockHeight + 2.f)),
                    sf::Vector2f(m_blockWidth, m_blockHeight), 3);
    }

public:
    Game()
        : m_pilka({ 200.f, 200.f }, { 3.f, 3.f }, 10.f),
        m_paletka({ 640.f / 2.f, 480.f - 30.f }) {
        m_blockWidth = (640.f - (ILOSC_KOLUMN - 1) * 2.f) / ILOSC_KOLUMN;
        m_blockHeight = 20.f;
        generateBricks();
    }

    void update(sf::Time dt, sf::RenderWindow& window) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_paletka.przesunLewo();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_paletka.przesunPrawo();

        m_paletka.ograniczRuch(640.f);
        m_pilka.przesun();
        m_pilka.kolizjaScian(640.f, 480.f);

        for (auto& cegla : m_bloki) {
            if (cegla.czyZniszczony()) continue;
            if (cegla.getGlobalBounds().intersects(m_pilka.getGlobalBounds())) {
                m_pilka.odbijY();
                cegla.trafienie();
                break;
            }
        }

        m_bloki.erase(
            std::remove_if(m_bloki.begin(), m_bloki.end(),
                [](const Cegla& cegla) { return cegla.czyZniszczony(); }),
            m_bloki.end()
        );

        sf::Vector2f ballPos = m_pilka.getPosition();
        sf::Vector2f paddlePos = m_paletka.getPosition();
        float paddleWidth = m_paletka.getWidth();
        float paddleHeight = m_paletka.getHeight();

        if (ballPos.x + m_pilka.getRadius() >= paddlePos.x - paddleWidth / 2.f &&
            ballPos.x - m_pilka.getRadius() <= paddlePos.x + paddleWidth / 2.f &&
            ballPos.y + m_pilka.getRadius() >= paddlePos.y - paddleHeight / 2.f) {
            m_pilka.odbijY();
        }

        if (ballPos.y - m_pilka.getRadius() > 480.f) {
            std::cout << "KONIEC GRY!" << std::endl;
            window.close();
        }
    }

    void render(sf::RenderWindow& target) {
        m_paletka.rysuj(target);
        m_pilka.rysuj(target);
        for (auto& cegla : m_bloki)
            if (!cegla.czyZniszczony()) target.draw(cegla);
    }

    void reset() {
        m_pilka.setPosition({ 200.f, 200.f });
        m_pilka.setVelocity({ 3.f, 3.f });

        m_paletka.setPosition({ 640.f / 2.f, 480.f - 30.f });

        m_bloki.clear();
        generateBricks();
    }

    void zapiszAktualnyStan() {
        m_gameState.capture(m_paletka, m_pilka, m_bloki);
        std::cout << "[ZAPIS] Stan gry:" << std::endl;
        std::cout << "  - Pozostale cegly: " << m_gameState.getBlocks().size() << std::endl;
        std::cout << "  - Pozycja paletki: " << m_gameState.getPaddlePosition().x
            << ", " << m_gameState.getPaddlePosition().y << std::endl;
		std::cout << "  - Pozycja pilki: " << m_gameState.getBallPosition().x
			<< ", " << m_gameState.getBallPosition().y << std::endl;
        std::cout << "  - Predkosc pilki: " << m_gameState.getBallVelocity().x
			<< ", " << m_gameState.getBallVelocity().y << std::endl;
    }
};