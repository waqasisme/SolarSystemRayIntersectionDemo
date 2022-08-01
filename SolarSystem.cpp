#include "SolarSystem.h"

SolarSystem::SolarSystem(unsigned long totalBodies) {
    spaceBodies.reserve(totalBodies);
}

std::vector<std::shared_ptr<SpaceBody>> const &SolarSystem::getBodies() const {
    return spaceBodies;
}