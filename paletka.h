#include <SFML/Graphics.hpp>
#include <vector>

class Paletka {
private:
    sf::Vector2f position;
    sf::RectangleShape paddleShape;
    const float speed = 5.f;
    const float width = 100.f;
    const float height = 20.f;

public:
    Paletka(sf::Vector2f startPosition) {
        position = startPosition;
        paddleShape.setSize({ width, height });
        paddleShape.setOrigin(width / 2.f, height / 2.f);
        paddleShape.setPosition(position);
        paddleShape.setFillColor(sf::Color(60, 130, 170));
    }

    void przesunLewo() {
        position.x -= speed;
        paddleShape.setPosition(position);
    }

    void przesunPrawo() {
        position.x += speed;
        paddleShape.setPosition(position);
    }

    void ograniczRuch(float WIDTH) {
        if (position.x - width / 2.f < 0)
            position.x = width / 2.f;
        if (position.x + width / 2.f > WIDTH)
            position.x = WIDTH - width / 2.f;
        paddleShape.setPosition(position);
    }

    void rysuj(sf::RenderTarget& target) {
        target.draw(paddleShape);
    }

    void setPosition(sf::Vector2f newPos) {
        position = newPos;
        paddleShape.setPosition(position);
    }

    sf::Vector2f getPosition() const { return position; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    sf::FloatRect getGlobalBounds() const { return paddleShape.getGlobalBounds(); }
};