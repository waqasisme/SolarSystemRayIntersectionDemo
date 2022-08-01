#include "InputManager.h"

#include "RayManager.h"
#include "SolarSystemManager.h"
#include "Util.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Event.hpp>

InputManager::InputManager() :
    moving(false), isRayButtonClicked(false),
    currentZoomLevel(DEFAULT_ZOOM_LEVEL) {}

void InputManager::HandleEvent(sf::RenderWindow &window, sf::Event const &event,
                               SolarSystemManager &solarSystemManager,
                               RayManager &rayManager) {
    switch (event.type) {
        // Window Closed - Exit program
        case sf::Event::Closed:
            window.close();
            break;
        // Window Resized
        case sf::Event::Resized: {
            sf::FloatRect visible_area(0, 0, event.size.width,
                                       event.size.height);
            window.setView(sf::View(visible_area));
            break;
        }
        // KEYBOARD EVENTS - ESC for Close, R for reset zoom P for pause
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.key.code == sf::Keyboard::R) {
                window.setView(window.getDefaultView());
                currentZoomLevel = DEFAULT_ZOOM_LEVEL;
            }
            if (event.key.code == sf::Keyboard::P)
                solarSystemManager.togglePause();
            break;
        }
        // Mouse Wheel Zooms
        case sf::Event::MouseWheelScrolled: {
            currentView = window.getView();
            // positive means zoom in
            if (event.mouseWheelScroll.delta > 0 &&
                currentZoomLevel < MAX_ZOOM_LEVEL) {
                currentZoomLevel += 1;
                currentView.zoom(0.95f);
            } else if (event.mouseWheelScroll.delta < 0 &&
                       currentZoomLevel > MIN_ZOOM_LEVEL) {
                currentZoomLevel -= 1;
                currentView.zoom(1.05f);
            }
            window.setView(currentView);
            break;
        }
        // Mouse Left Button used for Panning and Clicking Planets
        case sf::Event::MouseButtonPressed: {
            if (ImGui::GetIO().WantCaptureMouse)
                break;
            // Mouse button is pressed, get the position and set moving
            // as active
            if (event.mouseButton.button == sf::Mouse::Button::Left &&
                !moving) {
                moving = true;
                currentMousePosition = window.mapPixelToCoords(
                    sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                solarSystemManager.checkSpaceBodyClicked(currentMousePosition);
            }
            break;
        }
        case sf::Event::MouseButtonReleased: {
            if (ImGui::GetIO().WantCaptureMouse)
                break;
            // Mouse button is released, no longer move
            currentMousePosition = window.mapPixelToCoords(
                sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                // we've dropped 1 x already
                if (isRayButtonClicked && droppedRaySource) {
                    // drop 2nd x and draw ray
                    rayManager.addTarget(window, currentMousePosition);
                    isRayButtonClicked = false;
                    droppedRaySource = false;
                } else if (isRayButtonClicked) {
                    rayManager.addSource(window, currentMousePosition);
                    droppedRaySource = true;
                }

                if (moving)
                    moving = false;
            }

            if (event.mouseButton.button == sf::Mouse::Button::Right) {
                // delete if intersecting with ray
                rayManager.deleteClickedRay(
                    sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
            }

            break;
        }
        case sf::Event::MouseMoved: {
            if (ImGui::GetIO().WantCaptureMouse)
                break;
            // Ignore mouse movement unless a button is pressed
            if (!moving)
                break;
            // Determine the new position in world coordinates
            const sf::Vector2f newPosition = window.mapPixelToCoords(
                sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            // Determine how the cursor has moved
            const sf::Vector2f delta = currentMousePosition - newPosition;
            currentView = window.getView();
            // Move our view accordingly and update the window
            currentView.setCenter(currentView.getCenter() + delta);
            window.setView(currentView);

            // Save the new position as the old one
            // We're recalculating this, since we've changed the view
            currentMousePosition = window.mapPixelToCoords(
                sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
            break;
        }

        default:
            break;
    }
}

void InputManager::setCurrentView(sf::View view) {
    currentView = view;
}

bool InputManager::rayButtonClicked() const {
    return isRayButtonClicked;
}

void InputManager::toggleRayButton() {
    isRayButtonClicked = !isRayButtonClicked;
    droppedRaySource = false;
}