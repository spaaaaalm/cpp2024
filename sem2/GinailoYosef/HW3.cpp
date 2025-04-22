#include <SFML/Graphics.hpp>
#include <windows.h>

int main() {
    sf::RenderWindow window(
        sf::VideoMode({ 400, 150 }),
        "Button", 
        sf::Style::None,
        sf::State::Windowed
    );

    bool mousePressed = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { window.close(); }
        }

        if (!window.hasFocus()) { continue; };

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!mousePressed) {
                mousePressed = true;

                ExitWindows(0, 0); //soft reboot
            };
        }
        else { 
            mousePressed = false; 
        }

        window.clear(sf::Color::Red);

        window.display();
    }
}