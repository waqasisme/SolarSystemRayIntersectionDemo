#ifndef __SOLAR_SYSTEM_H__
#define __SOLAR_SYSTEM_H__

#include "SpaceBody.h"

#include <SFML/Graphics/RenderWindow.hpp>

class SolarSystem {
public:
    std::vector<std::shared_ptr<SpaceBody>> spaceBodies;
    SolarSystem() = default;
    SolarSystem(unsigned long totalBodies);

    std::vector<std::shared_ptr<SpaceBody>> const &getBodies() const;
};

#endif // !__SOLAR_SYSTEM_H__
