
#include "SpaceBody.h"

#include "Util.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

SpaceBody::SpaceBody() :
    parent(nullptr), previous(sf::Vector2f{0, 0}), velocity(0),
    isHighlighted(false) {}

SpaceBody::SpaceBody(sf::Vector2f const &position, double radius,
                     double velocity, sf::Color const &color,
                     std::shared_ptr<SpaceBody> parent) :
    parent(parent),
    previous(position), velocity(RADIAN * velocity), isHighlighted(false) {
    planetShape.setFillColor(color);
    planetShape.setRadius(radius);
    planetShape.setPosition(position);
    planetShape.setOutlineColor(sf::Color::Red);
}

void SpaceBody::updatePosition(double deltaTime) {
    if (parent != nullptr) {
        previous = getCurrentPosition();

        // In order to update the position of each planet, we first translate
        // the planet by how much it's parent moved then rotate it based on it's
        // velocity then translate it back into orbit
        planetShape.move(parent->getDistanceMoved());
        auto distanceToParent =
            planetShape.getPosition() - parent->getCurrentPosition();
        // calculate rotation in circle
        double rotAmount = velocity * deltaTime;
        auto x = (distanceToParent.x * cos(rotAmount)) -
                 (distanceToParent.y * sin(rotAmount));
        auto y = (distanceToParent.x * sin(rotAmount)) +
                 (distanceToParent.y * cos(rotAmount));
        // translate back with rotated position
        planetShape.setPosition(sf::Vector2f(x, y) + parent->getCurrentPosition());
    }
}

void SpaceBody::draw(sf::RenderWindow &w) {
    w.draw(planetShape);
}

sf::Vector2f SpaceBody::getCurrentPosition() {
    return planetShape.getPosition();
}

sf::Vector2f SpaceBody::getDistanceMoved() {
    return getCurrentPosition() - previous;
}

sf::CircleShape &SpaceBody::getShape() {
    return planetShape;
}

void SpaceBody::setHighlight(bool highlight) {
    planetShape.setOutlineThickness(highlight ? 3.0f : 0.0f);
    isHighlighted = highlight;
}
