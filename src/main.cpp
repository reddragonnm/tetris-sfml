#include <SFML/Graphics.hpp>

#include "Game.hpp"

void displayGrid(sf::RenderWindow& window) {
    for (int i = 1; i < numCols; i++) {
        sf::RectangleShape line{ {1.f, (float)squareSize * numRows} };
        line.setPosition({ (float)i * squareSize, 0 });
        window.draw(line);
    }

    for (int i = 1; i < numRows; i++) {
        sf::RectangleShape line{ {(float)squareSize * numCols, 1.f} };
        line.setPosition({ 0, (float)i * squareSize });
        window.draw(line);
    }
}

int main()
{
    sf::RenderWindow window{ sf::VideoMode({squareSize * numCols, squareSize * numRows}), "Tetris" };

    Game game{};

    sf::Clock clock;
    sf::Time pieceDownInterval{ sf::seconds(1.f) };

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                using sf::Keyboard::Scancode;

                switch (keyPressed->scancode) {
                case Scancode::Left:
                    game.movePieceLeft();
                    break;

                case Scancode::Right:
                    game.movePieceRight();
                    break;

                case Scancode::Up:
                    game.rotatePieceLeft();
                    break;

                case Scancode::Down:
                    game.rotatePieceRight();
                    break;
                }
            }
        }

        window.clear();

        if (clock.getElapsedTime() >= pieceDownInterval) {
            game.movePieceDown();
            clock.restart();
        }

        game.displayBoard(window);
        displayGrid(window);

        window.display();
    }
}
