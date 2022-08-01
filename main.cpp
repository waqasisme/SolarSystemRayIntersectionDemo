#include "InputManager.h"
#include "RayManager.h"
#include "SolarSystem.h"
#include "Util.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Window/Event.hpp>

int main() {
    sf::Time time;

    auto const windowWidth = sf::VideoMode::getDesktopMode().width / 1.2;
    auto const windowHeight = sf::VideoMode::getDesktopMode().height / 1.2;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "Simple Solar System");

    SolarSystemManager solarSystemManager(windowWidth / 2, windowHeight / 2);
    InputManager inputManager{};
    RayManager rayManager{};

    double totalTime = 0;
    ImGui::SFML::Init(window);
    auto rayButtonText = "Click Me to Make a Ray and light up the world";
    auto rayCancelText = "Cancel drawing Ray";
    bool open = true;

    inputManager.setCurrentView(window.getDefaultView());
    sf::Clock deltaClock;
    while (window.isOpen()) {
        time = deltaClock.restart();
        double deltaTime = 4.0 * time.asSeconds();

        sf::Event event;
        // Listen for click actions
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            inputManager.HandleEvent(window, event, solarSystemManager,
                                     rayManager);
        }
        ImGui::SFML::Update(window, time);
        totalTime += deltaTime;

        // Render solar system and UI elements
        window.clear(sf::Color(18, 33, 43));
        solarSystemManager.update(deltaTime);
        solarSystemManager.checkSpaceBodyHit(rayManager.getRays());
        solarSystemManager.draw(window);
        rayManager.draw(window);

        // ImGui::ShowDemoWindow();
        ImGui::SetNextWindowPos(ImVec2(1250, 40));
        ImGui::SetNextWindowSize(ImVec2(450, 450));
        ImGui::Begin("Help & Controls", &open,
                     ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Mouse");
        ImGui::BulletText("Hold down Left Click and move cursor to Pan around");
        ImGui::BulletText(
            "Use Mouse Scroll Wheel To Zoom in and out of the universe");
        ImGui::BulletText(
            "Use Left Click to select and highlight objects of interest");
        ImGui::Text("Keyboard");
        ImGui::BulletText("Press R to reset to the center and default zoom "
                          "level if you get lost.");
        ImGui::BulletText("Press P to pause the animation and take a breather");
        ImGui::BulletText("Press Escape to close this demo :(");
        ImGui::Text("Ray Controls");
        ImGui::BulletText(
            "Use the button below to mark a spot for the source of the Ray.");
        ImGui::BulletText(
            "Then click another part of the map to project the Ray");
        ImGui::BulletText("If you change your mind simply click where the Ray "
                          "button was to cancel drawing a ray");
        ImGui::BulletText("Right click on a ray to delete it.");
        ImGui::BulletText(
            "Rays light up the objects they come into contact with");
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(1250, 600));
        ImGui::Begin("RAY CONTROLS", &open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
        if (ImGui::Button(inputManager.rayButtonClicked() ? rayCancelText
                                                          : rayButtonText)) {
            inputManager.toggleRayButton();
            if (!inputManager.rayButtonClicked())
                rayManager.deleteSource();
        };
        ImGui::End();
        

        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
}