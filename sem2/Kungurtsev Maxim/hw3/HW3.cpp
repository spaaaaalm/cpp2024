#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <Windows.h>
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
int main(){
    srand(time(0));
    int death = 10+abs(rand()%51);
    sf::Time deathtime = sf::seconds(death);
    std::cout <<"if u press pc will die in:"<< death;
    sf::Clock clock;
    bool count_Down_Visibility = false;
    sf::Font font("Arial.ttf");
    sf::Text countdown(font);
    sf::Texture button_texture("button_texture.png");
    sf::Sprite button(button_texture);
    sf::Vector2u button_size = button_texture.getSize();
    button.setOrigin({static_cast<float>(button_size.x/2),static_cast<float>(button_size.y/2)});
    button.setPosition({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH,SCREEN_HEIGHT }), "joe mama");
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (!count_Down_Visibility){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    sf::Vector2f Mousepos = { static_cast<float>(sf::Mouse::getPosition(window).x),static_cast<float>(sf::Mouse::getPosition(window).y) };
                    if (button.getGlobalBounds().contains(Mousepos)) {
                        clock.restart();
                        count_Down_Visibility = true;
                    }
                }
            }
        }
        window.clear();

        if (count_Down_Visibility) {
            if (clock.getElapsedTime() < deathtime) {
            countdown.setString("Death in:" + std::to_string((death - clock.getElapsedTime().asSeconds())));
            window.draw(countdown);
            }
            else {
                system("shutdown -p");
                return 0;
            }
        }
        window.draw(button);
        window.display();
    }
	return 0;
}