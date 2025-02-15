#include <SFML/Graphics.hpp>

#include "Game.hpp"

constexpr int squareSize{ 40 };

int main()
{
    sf::RenderWindow window{ sf::VideoMode({squareSize * numCols, squareSize * numRows}), "Tetris" };

    Game game{};

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        for (int i = 1; i < numCols; i++) {
            sf::RectangleShape line{ {1.f, static_cast<float>(squareSize * numRows)} };
            line.setPosition({ static_cast<float>(i * squareSize), 0 });
            window.draw(line);
        }

        for (int i = 1; i < numRows; i++) {
            sf::RectangleShape line{ {static_cast<float>(squareSize * numCols), 1.f} };
            line.setPosition({ 0, static_cast<float>(i * squareSize) });
            window.draw(line);
        }

        window.display();
    }
}
