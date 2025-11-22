#include <SFML/Graphics.hpp>

// ----- KLASA PALETKA ----- //
class Paletka {
private:
    sf::Vector2f position;           // pozycja paletki
    sf::RectangleShape paddleShape;  // kszta³t paletki
    const float speed = 5.f;         // prêdkoœæ paletki
    const float width = 100.f;       // szerokoœæ paletki
    const float height = 20.f;       // wysokoœæ paletki

public:
    // Konstruktor
    Paletka(sf::Vector2f startPosition) {
        position = startPosition;

        paddleShape.setSize({ width, height });
        paddleShape.setOrigin(width / 2.f, height / 2.f); // odniesienie do œrodka paletki
        paddleShape.setPosition(position);
        paddleShape.setFillColor(sf::Color(60, 130, 170));
    }

    // przesun lewo
    void przesunLewo() {
        position.x -= speed;
        paddleShape.setPosition(position);
    }

    // przesun prawo
    void przesunPrawo() {
        position.x += speed;
        paddleShape.setPosition(position);
    }

    // ograniczenie ruchu paletki
    void ograniczRuch(float WIDTH) {
        if (position.x - width / 2.f < 0)
            position.x = width / 2.f;
        if (position.x + width / 2.f > WIDTH)
            position.x = WIDTH - width / 2.f;
        paddleShape.setPosition(position);
    }

    // rysowanie paletki
    void rysuj(sf::RenderTarget& target) {
        target.draw(paddleShape);
    }

    // gettery
    sf::Vector2f getPosition() const { return position; }   // zwraca pozycjê paletki
    float getWidth() const { return width; }                // zwraca szerokoœæ paletki
    float getHeight() const { return height; }              // zwraca wysokoœæ paletki
    sf::FloatRect getGlobalBounds() const { return paddleShape.getGlobalBounds(); } // granice paletki
};
