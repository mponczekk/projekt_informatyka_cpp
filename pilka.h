#include <SFML/Graphics.hpp>
#include <vector>

class Pilka {
private:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float radius;
    sf::CircleShape ballShape;

public:
    Pilka(sf::Vector2f startPosition, sf::Vector2f startVelocity, float r) {
        position = startPosition;
        velocity = startVelocity;
        radius = r;

        ballShape.setRadius(radius);
        ballShape.setOrigin(radius, radius);
        ballShape.setPosition(position);
        ballShape.setFillColor(sf::Color::White);
    }

    void przesun() {
        position += velocity;
        ballShape.setPosition(position);
    }

    void odbijX() { velocity.x = -velocity.x; }
    void odbijY() { velocity.y = -velocity.y; }

    void kolizjaScian(float WIDTH, float HEIGHT) {
        if (position.x - radius < 0 || position.x + radius > WIDTH) {
            odbijX();
        }
        if (position.y - radius < 0) {
            odbijY();
        }
    }

    void rysuj(sf::RenderTarget& target) { target.draw(ballShape); }

    void setPosition(sf::Vector2f newPos) {
        position = newPos;
        ballShape.setPosition(position);
    }
    void setVelocity(sf::Vector2f newVel) { velocity = newVel; }

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    float getRadius() const { return radius; }
    sf::FloatRect getGlobalBounds() const { return ballShape.getGlobalBounds(); }
};