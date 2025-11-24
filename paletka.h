#include <SFML/Graphics.hpp>
#include <vector>

// ----- KLASA PALETKA ----- //
class Paletka {
private:
    sf::Vector2f position;           // pozycja paletki
    sf::RectangleShape paddleShape;  // ksztalt paletki
    const float speed = 5.f;         // predkosc paletki
    const float width = 100.f;       // szerokosc paletki
    const float height = 20.f;       // wysokosc paletki

public:
    // Konstruktor
    Paletka(sf::Vector2f startPosition) {
        position = startPosition;

        paddleShape.setSize({ width, height });
        paddleShape.setOrigin(width / 2.f, height / 2.f); // odniesienie do srodka paletki
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
    sf::Vector2f getPosition() const { return position; }   // zwraca pozycje paletki
    float getWidth() const { return width; }                // zwraca szerokosc paletki
    float getHeight() const { return height; }              // zwraca wysokosc paletki
    sf::FloatRect getGlobalBounds() const { return paddleShape.getGlobalBounds(); } // granice paletki
};