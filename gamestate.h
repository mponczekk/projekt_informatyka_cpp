#include <SFML/System/Vector2.hpp>
#include <vector>
#include "paletka.h"
#include "pilka.h"
#include "cegla.h"
#include <fstream>
#include <string>
#include <iostream>

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
    int punkty;

public:
    inline void capture(const Paletka& paddle,
        const Pilka& ball,
        const std::vector<Cegla>& bricks, 
        int sumaPunktow = 0) {
        paddlePosition = paddle.getPosition();
        ballPosition = ball.getPosition();
        ballVelocity = ball.getVelocity();
		punkty = sumaPunktow;

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

    bool saveToFile(const std::string& filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "B??d: Nie mo?na otworzy? pliku " << filename << " do zapisu!\n";
            return false;
        }

        file << "PADDLE" << " " << paddlePosition.x << " " << paddlePosition.y << "\n";
        file << "BALL" << " " << ballPosition.x << " " << ballPosition.y << " " << ballVelocity.x << " " << ballVelocity.y << "\n";
		file << "POINTS" << " " << punkty << "\n";
        file << "BLOCKS_COUNT" << " " << blocks.size() << "\n";

        for (const auto& block : blocks) {
            file << block.x << " " << block.y << " " << block.hp << "\n";
        }

        file.close();
        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);

        punkty = 0;

        if (!file.is_open()) {
            std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << " do odczytu!\n";
            return false;
        }

        std::string label;

        // 1. Wczytaj Paletke
        file >> label;
        if (label != "PADDLE") {
            std::cerr << "Blad formatu: oczekiwano PADDLE, otrzymano " << label << "\n";
            return false;
        }
        file >> paddlePosition.x >> paddlePosition.y;

        // 2. Wczytaj Pilke
        file >> label;
        if (label != "BALL") {
            std::cerr << "Blad formatu: oczekiwano BALL, otrzymano " << label << "\n";
            return false;
        }
        file >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y;

        // 3. Wczytaj liczbe punktow
		file >> label;
        if (label != "POINTS") {
            std::cerr << "Blad formatu: oczekiwano POINTS, otrzymano " << label << "\n";
            return false;
		}
		file >> punkty;


        // 4. Wczytaj liczbe blokow
        file >> label;
        if (label != "BLOCKS_COUNT") {
            std::cerr << "Blad formatu: oczekiwano BLOCKS_COUNT, otrzymano " << label << "\n";
            return false;
        }

        int blocksCount;
        file >> blocksCount;

        // 5. Wczytaj bloki
        blocks.clear();
        for (int i = 0; i < blocksCount; ++i) {
            BlockData bd;
            if (!(file >> bd.x >> bd.y >> bd.hp)) {
                std::cerr << "Blad wczytywania bloku " << i << "\n";
                return false;
            }
            blocks.push_back(bd);
        }

        file.close();
        std::cout << "Wczytano stan z pliku " << filename << " (blokow: " << blocks.size() << ", punkty: " << punkty << ")\n";
        return true;
    }

    void apply(Paletka& p, Pilka& b, std::vector<Cegla>& cegly, int& sumaPunktow) {
        p.setPosition(paddlePosition);
        b.setPosition(ballPosition);
        b.setVelocity(ballVelocity);
		sumaPunktow = punkty;
        cegly.clear();

        const float brickWidth = (640.f - (12 - 1) * 2.f) / 12;
        const float brickHeight = 20.f;

        for (const auto& block : blocks) {
            cegly.emplace_back(
                sf::Vector2f(block.x, block.y),
                sf::Vector2f(brickWidth, brickHeight),
                block.hp
            );
        }
    }


    sf::Vector2f getPaddlePosition() const { return paddlePosition; }
    sf::Vector2f getBallPosition() const { return ballPosition; }
    sf::Vector2f getBallVelocity() const { return ballVelocity; }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
};