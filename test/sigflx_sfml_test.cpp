#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

int main()
{   
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window",sf::Style::Close | sf::Style::Resize | sf::Style::None);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);

        window.display();
    }
    return 0;
}