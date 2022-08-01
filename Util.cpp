#include "Util.h"

#include <SFML/Graphics.hpp>

unsigned long randomInt(int max) {
    return randomInt(0, max);
}

unsigned long randomInt(int min, int max) {
    static std::mt19937 gen;
    return (gen() % max) + min;
}

double angleBetween2Points(sf::Vector2f const &first,
                           sf::Vector2f const &second) {
    auto rads = std::atan2((first.y - second.y), (second.x - first.x));
    rads = rads < 0 ? rads = std::abs(rads) : rads = 2 * PI - rads;
    auto degs = 180 * (rads / PI);
    return degs;
}

double dot(sf::Vector2f const &v1, sf::Vector2f const &v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

bool lineCircleIntersection(sf::CircleShape const &circle,
                            std::vector<sf::Vertex> const &line) {

    auto d = line[1].position - line[0].position;
    auto f = line[1].position - circle.getPosition();
    double a = dot(d, d);
    double b = 2 * dot(f, d);
    double c = dot(f, f) - pow(circle.getRadius(), 2);

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // no intersection
    } else {
        // Ray didn't miss
        // so we have to solve the equation for the line and circle

        discriminant = sqrt(discriminant);
        double t1 = (-b - discriminant) / (2 * a);
        double t2 = (-b + discriminant) / (2 * a);
        // 3x HIT cases:
        // Impale(t1 hit,t2 hit), Poke(t1 hit,t2>1), ExitWound(t1<0, t2 hit),
        // 3x MISS cases:
        // FallShort (t1>1,t2>1), Past (t1<0,t2<0), CompletelyInside(t1<0, t2>1)

        // Impale, Poke
        if (t1 >= 0 && t1 <= 1) {
            return true;
        }

        // ExitWound
        if (t2 >= 0 && t2 <= 1) {
            return true;
        }

        // no intersection: FallShort, Past, CompletelyInside
        return false;
    }
}
