#ifndef __SOLAR_SYSTEM_MGR__
#define __SOLAR_SYSTEM_MGR__

#include "SolarSystem.h"

#include <SFML/Graphics/RectangleShape.hpp>

class SolarSystemManager {
public:
    SolarSystemManager(double const &centerX, double const &centerY);

    void update(double deltaTime);

    void draw(sf::RenderWindow &w);

    void checkSpaceBodyClicked(sf::Vector2f const &coordinates) const;
    void checkSpaceBodyHit(std::vector<std::vector<sf::Vertex>> const &lines);

    void togglePause();

private:
    SolarSystem solarSystem;
    bool isPaused;
};

#endif
