#include <SFML/Graphics.hpp>
#include <vector>

// ----- KLASA PILKA ----- //
class Pilka {
private:
    sf::Vector2f position;          // pozycja pilki
    sf::Vector2f velocity;          // predkosc pilki
    float radius;                   // promien pilki
    sf::CircleShape ballShape;      // ksztalt pilki
public:
    // Konstruktor
    Pilka(sf::Vector2f startPosition, sf::Vector2f startVelocity, float r) {
        position = startPosition;
        velocity = startVelocity;
        radius = r;

        ballShape.setRadius(radius);
        ballShape.setOrigin(radius, radius);    // odniesienie do srodka pilki
        ballShape.setPosition(position);
        ballShape.setFillColor(sf::Color::White);
    }

    // przesuwanie pilki
    void przesun() {
        position += velocity;
        ballShape.setPosition(position);
    }

    // odbicie pilki X
    void odbijX() { velocity.x = -velocity.x; }

    // odbicie pilki Y
    void odbijY() { velocity.y = -velocity.y; }

    // kolizja ze scianami
    void kolizjaScian(float WIDTH, float HEIGHT) {
        if (position.x - radius < 0 || position.x + radius > WIDTH) {
            odbijX();
        }
        if (position.y - radius < 0) {
            odbijY();
        }
    }

    // rysowanie pilki
    void rysuj(sf::RenderTarget& target) { target.draw(ballShape); }

    // gettery
    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    float getRadius() const { return radius; }
    sf::FloatRect getGlobalBounds() const { return ballShape.getGlobalBounds(); } // granice pilki
};