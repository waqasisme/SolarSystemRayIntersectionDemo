#ifndef __RAY_MANAGER__
#define __RAY_MANAGER__
#include <SFML/Graphics.hpp>

class RayManager {
public:
    void addSource(sf::RenderWindow &w, sf::Vector2f const &source);
    void addTarget(sf::RenderWindow &w, sf::Vector2f const &target);

    void deleteSource();
    void deleteClickedRay(sf::Vector2f const &coordinates);

    void draw(sf::RenderWindow &w);

    std::vector<std::vector<sf::Vertex>> const &
    getRays() const;

    std::vector<sf::Vertex>
    getCrossForPoint(sf::Vector2f const &point, sf::Color const &col = sf::Color::Red);
    
    std::vector<sf::Vertex>
    getRayForPoints(sf::Vector2f const &p1, sf::Vector2f const &p2,
                    sf::Color const &col = sf::Color::White);

private:
    std::vector<std::pair<sf::RectangleShape, sf::RectangleShape>> rays;
    std::vector<std::vector<sf::Vertex>> lines;
    std::vector<std::vector<sf::Vertex>> crosses;
    std::unique_ptr<sf::Vector2f> last_source;
};

#endif // !__RAY_MANAGER__
