#include <SFML/System/Vector2.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "cegla.h"

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    inline void capture(const Paletka& paddle,
        const Pilka& ball,
        const std::vector<Cegla>& bricks) {
        paddlePosition = paddle.getPosition();
        ballPosition = ball.getPosition();
        ballVelocity = ball.getVelocity();

        blocks.clear();
        for (const auto& brick : bricks) {
            if (!brick.czyZniszczony()) {
                BlockData bd;
                auto pos = brick.getPozycja();
                bd.x = pos.x;
                bd.y = pos.y;
                bd.hp = brick.getPunktyZycia();
                blocks.push_back(bd);
            }
        }
    }

 
    sf::Vector2f getPaddlePosition() const { return paddlePosition; }
    sf::Vector2f getBallPosition() const { return ballPosition; }
    sf::Vector2f getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
};