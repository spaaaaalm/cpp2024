#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <windows.h>

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(400, 300), "Shutdown Timer");
    window.setFramerateLimit(60);

    sf::RectangleShape button(sf::Vector2f(200, 80));
    button.setFillColor(sf::Color::Red);
    button.setPosition(100, 100);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::Black);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text buttonText("Shutdown", font, 30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(120, 125);

    sf::Clock timer;
    bool isTimerActive = false;
    int delay = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (button.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        delay = 10 + rand() % 51; // 10-60 секунд
                        timer.restart();
                        isTimerActive = true;
                    }
                }
            }
        }

        if (isTimerActive && timer.getElapsedTime().asSeconds() >= delay)
        {
            isTimerActive = false;
            system("shutdown /s /t 0"); //выключение
        }

        window.clear(sf::Color::White);
        window.draw(button);
        window.draw(buttonText);
        window.display();
    }

    return 0;
}