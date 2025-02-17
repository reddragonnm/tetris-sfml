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
    window.setKeyRepeatEnabled(false);

    bool movePieceDown{ false };

    Game game{};

    sf::Clock clock;
    sf::Time autoPieceDownInterval{ sf::seconds(1.f) };
    sf::Time movePieceDownInterval{ sf::seconds(0.07f) };

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
                    game.rotatePiece();
                    break;

                case Scancode::Down:
                    movePieceDown = true;
                    break;
                }
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                if (keyReleased->scancode == sf::Keyboard::Scancode::Down) {
                    movePieceDown = false;
                }
            }
        }

        window.clear();

        if ((clock.getElapsedTime() >= autoPieceDownInterval) || (movePieceDown && clock.getElapsedTime() >= movePieceDownInterval)) {
            game.movePieceDown();
            clock.restart();
        }

        game.displayBoard(window);
        displayGrid(window);

        window.display();
    }
}
