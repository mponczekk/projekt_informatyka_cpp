#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

class Cegla : public sf::RectangleShape {
private:
    int punktyZycia;
    bool czyJestZniszczony;

    static const std::array<sf::Color, 4> colorLUT;

public:
    Cegla(sf::Vector2f startPo, sf::Vector2f rozmiar, int L)
        : punktyZycia(L), czyJestZniszczony(false)
    {
        setPosition(startPo);
        setSize(rozmiar);
        setOutlineColor(sf::Color::White);
        aktualizujKolor();
    }

    void trafienie() {
        if (czyJestZniszczony)
            return;

        punktyZycia--;

        if (punktyZycia <= 0)
            czyJestZniszczony = true;

        aktualizujKolor();
    }

    void aktualizujKolor() {
        if (czyJestZniszczony) {
            setFillColor(sf::Color::Transparent);
            return;
        }

        size_t index = static_cast<size_t>(punktyZycia);
        if (index < colorLUT.size()) {
            setFillColor(colorLUT[index]);
        }
        else {
            setFillColor(sf::Color::Magenta);
        }
    }

    bool czyZniszczony() const { return czyJestZniszczony; }
    int getPunktyZycia() const { return punktyZycia; }
    sf::Vector2f getPozycja() const { return getPosition(); }
};

const std::array<sf::Color, 4> Cegla::colorLUT = {
    sf::Color::Transparent,
    sf::Color(255, 228, 225),
    sf::Color(255, 165, 0),
    sf::Color(50, 200, 50),
};