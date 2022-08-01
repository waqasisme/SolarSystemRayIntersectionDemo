#include "RayManager.h"

#include "Util.h"

void RayManager::addSource(sf::RenderWindow &w, sf::Vector2f const &source) {
    last_source = std::make_unique<sf::Vector2f>(source);
}

void RayManager::deleteSource() {
    last_source.reset();
}

void RayManager::addTarget(sf::RenderWindow &w, sf::Vector2f const &target) {
    auto genLine = [](sf::Vector2f first, sf::Vector2f second) {
        sf::RectangleShape line{{5000, 3}};
        line.setPosition(first);
        auto angle = angleBetween2Points(first, second);
        line.setRotation(angle);
        return line;
    };

    rays.emplace_back(genLine(*last_source, target),
                      genLine(target, *last_source));

   
    lines.push_back(getRayForPoints(*last_source, target));
    lines.push_back(getRayForPoints(target, *last_source)); 
    crosses.push_back(getCrossForPoint(*last_source));
    crosses.push_back(getCrossForPoint(target));

    deleteSource();
}

void RayManager::draw(sf::RenderWindow &w) {
    for (auto line : lines) {
        w.draw(line.data(), 5, sf::Lines);
    }

    for (auto cross : crosses) {
        w.draw(cross.data(), 5, sf::Lines);
    }

    if (last_source != nullptr) {
        auto cross = getCrossForPoint(*last_source);
        w.draw(cross.data(), 5, sf::Lines);
    }
}

void RayManager::deleteClickedRay(sf::Vector2f const &coordinates) {
    auto contains =
        [coordinates](std::pair<sf::RectangleShape, sf::RectangleShape> ray) {
            return ray.first.getGlobalBounds().contains(coordinates) ||
                   ray.second.getGlobalBounds().contains(coordinates);
        };

    if ((rays.size() == 1) && contains(rays[0])) {
        rays.clear();
        crosses.clear();
        lines.clear();
    } else {
        auto it = std::remove_if(rays.begin(), rays.end(), contains);
        if (it != rays.end()) {
            auto i = crosses.begin() + 2 * std::distance(rays.begin(), it);
            auto l = lines.begin() + 2 * std::distance(rays.begin(), it);
            crosses.erase(i, i + 2);
            lines.erase(l, l + 2);
            rays.erase(it);
        }
    }
}

std::vector<sf::Vertex> RayManager::getCrossForPoint(sf::Vector2f const &point,
                                                     sf::Color const &color) {
    return {{{point.x - 10, point.y - 10}, color},
            {{point.x + 10, point.y + 10}, color},
            {{point.x + 10, point.y - 10}, color},
            {{point.x - 10, point.y + 10}, color}};
}

std::vector<sf::Vertex> RayManager::getRayForPoints(sf::Vector2f const &point1,
                                                   sf::Vector2f const &point2,
                                                     sf::Color const &color) {

    // a ray for the line p1->p2 is p1 + t * (p2 - p1) where t is the length
    auto rayStart = point1;
    auto rayEnd = point2 - point1;
    rayEnd.x *= 1000.0;
    rayEnd.y *= 1000.0;
    
    return {{rayStart, color}, {rayEnd, color}};
    
}

std::vector<std::vector<sf::Vertex>> const &
RayManager::getRays() const {
    return lines;
}