#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__
#include "RayManager.h"
#include "SolarSystemManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class InputManager {
public:
    InputManager();

    void HandleEvent(sf::RenderWindow &window, sf::Event const &event,
                     SolarSystemManager &solMgr, RayManager &rayMgr);
    void setCurrentView(sf::View currentView);
    void toggleRayButton();
    bool rayButtonClicked() const;

private:
    bool moving;
    bool isRayButtonClicked;
    bool droppedRaySource;

    int currentZoomLevel;
    sf::View currentView;
    sf::Vector2f currentMousePosition;
};

#endif // !__INPUT_MANAGER__
