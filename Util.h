#ifndef __UTIL_H__
#define __UTIL_H__

#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <utility>

auto constexpr PI = 3.14159265358979;

auto constexpr RADIAN = 0.0175;

auto constexpr MIN_ZOOM_LEVEL = -10;
auto constexpr DEFAULT_ZOOM_LEVEL = 2;
auto constexpr MAX_ZOOM_LEVEL = 5;

unsigned long randomInt(int max);

unsigned long randomInt(int min, int max);

double angleBetween2Points(sf::Vector2f const &first,
                           sf::Vector2f const &second);

bool lineCircleIntersection(sf::CircleShape const &circle,
                            std::vector<sf::Vertex> const &line);

double dot_product(sf::Vector2f const &first, sf::Vector2f const &second);

#endif
