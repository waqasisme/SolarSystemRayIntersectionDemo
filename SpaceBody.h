#ifndef __PLANET_H__
#define __PLANET_H__

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

class SpaceBody {
public:
    SpaceBody();

    SpaceBody(sf::Vector2f const &position, double radius, double velocity,
              sf::Color const &color, std::shared_ptr<SpaceBody> parent);

    void updatePosition(double deltaTime);

    void draw(sf::RenderWindow &w);

    sf::Vector2f getCurrentPosition();

    sf::Vector2f getDistanceMoved();

    sf::CircleShape &getShape();

    void setHighlight(bool highlight);
    bool isHighlighted;

private:
    std::shared_ptr<SpaceBody> parent;
    sf::CircleShape planetShape;
    double velocity;
    sf::Vector2f previous;
    bool isHit;
};
#endif
