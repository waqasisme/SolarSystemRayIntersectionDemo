#include "SolarSystemManager.h"

#include "SpaceBody.h"
#include "UniformDistribution.h"
#include "Util.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <unordered_map>

SolarSystemManager::SolarSystemManager(double const &centerX,
                                       double const &centerY) :
    solarSystem(),
    isPaused(false) {
    auto translate = [](sf::Vector2f vec, float dx, float dy) -> sf::Vector2f {
        return {vec.x + dx, vec.y + dy};
    };

    sf::Vector2f sunPosition(centerX, centerY);
    auto sunRadius = 75.0;
    auto sun = std::make_shared<SpaceBody>(sunPosition, sunRadius, 0.0,
                                           sf::Color::Yellow, nullptr);

    UniformDistribution ndx{sunRadius, 800}, ndy{sunRadius, 800}, ndv{-20, 20};

    auto totalBodies = randomInt(1, 10) + 1; // for Sun
    solarSystem.spaceBodies.reserve(totalBodies);
    solarSystem.spaceBodies.push_back(sun);

    for (auto i = 0; i < totalBodies; ++i) {
        auto planetPosition = translate(sunPosition, ndx.next(), ndy.next());
        auto planetRadius = randomInt(20, 40);
        auto planet = std::make_shared<SpaceBody>(
            planetPosition, planetRadius, ndv.next(), sf::Color::Blue, sun);
        solarSystem.spaceBodies.push_back(planet);

        auto moonCount = randomInt(3);
        for (auto j = 0; j < moonCount; ++j) {
            auto moonPosition =
                translate(planetPosition, planetRadius + 10, planetRadius + 10);
            auto moonRadius = randomInt(5, 15);
            auto moon = std::make_shared<SpaceBody>(
                moonPosition, moonRadius, ndv.next(), sf::Color::White, planet);
            solarSystem.spaceBodies.push_back(moon);

            auto asteroidCount = randomInt(2);
            for (auto k = 0; k < asteroidCount; ++k) {
                auto asteroidPosition =
                    translate(moonPosition, moonRadius + 5, moonRadius + 5);
                auto asteroid = std::make_shared<SpaceBody>(
                    asteroidPosition, randomInt(4, 10), ndv.next(),
                    sf::Color::Green, moon);
                solarSystem.spaceBodies.push_back(asteroid);
            }
        }
    }
}

void SolarSystemManager::update(double deltaTime) {
    if (!isPaused) {
        for (auto body : solarSystem.getBodies()) {
            body->updatePosition(deltaTime);
            body->setHighlight(false); // un-highlight every body at update we will re highlight if it's being hit by a line
        }
    }
}

void SolarSystemManager::togglePause() {
    isPaused = !isPaused;
}

void SolarSystemManager::draw(sf::RenderWindow &w) {
    for (auto body : solarSystem.getBodies()) {
        body->draw(w);
    }
}

void SolarSystemManager::checkSpaceBodyClicked(
    sf::Vector2f const &coordinates) const {
    static std::unordered_map<SpaceBody *, sf::Color> colorMap;
    for (auto body : solarSystem.getBodies()) {
        if (body->getShape().getGlobalBounds().contains(coordinates)) {
            colorMap[body.get()] = body->getShape().getFillColor();
            body->getShape().setFillColor(sf::Color::Red);
        } else if (colorMap.count(body.get())) {
            body->getShape().setFillColor(colorMap.at(body.get()));
        }
    }
}

void SolarSystemManager::checkSpaceBodyHit(std::vector<std::vector<sf::Vertex>> const &lines) {
    for (auto body : solarSystem.getBodies()) {
        for (auto line : lines) {
            auto highlight = !lineCircleIntersection(body->getShape(), line);
            body->setHighlight(highlight);
            if (highlight) // no need to check other lines if being hit by 1
                break;
        }
    }
}