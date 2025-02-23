#include <SFML/Graphics.hpp>

#include <set>

#include "Game.hpp"

void displayGrid(sf::RenderWindow& window) {
    std::uint8_t gridColor{ 30 };

    for (int i = 1; i < numCols; i++) {
        sf::RectangleShape line{ {1.f, (float)squareSize * numRows} };
        line.setPosition({ (float)i * squareSize, 0 });
        line.setFillColor(sf::Color{ gridColor, gridColor, gridColor });
        window.draw(line);
    }

    for (int i = 1; i < numRows; i++) {
        sf::RectangleShape line{ {(float)squareSize * numCols, 1.f} };
        line.setPosition({ 0, (float)i * squareSize });
        line.setFillColor(sf::Color{ gridColor, gridColor, gridColor });
        window.draw(line);
    }
}

int main()
{
    sf::RenderWindow window{ sf::VideoMode({squareSize * numCols, squareSize * numRows}), "Tetris" };
    window.setKeyRepeatEnabled(false);

    bool movePieceDown{ false };

    enum class Movement {
        LEFT,
        RIGHT,
        DOWN,
        NONE
    };
    Movement movement;

    Game game{};

    sf::Clock pieceDownclock;
    sf::Time autoPieceDownInterval{ sf::seconds(1.f) };

    sf::Clock moveClock;
    sf::Time movePieceInterval{ sf::seconds(0.1f) };

    while (window.isOpen() && !game.isGameOver())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                using sf::Keyboard::Scancode;

                switch (keyPressed->scancode) {
                case Scancode::Left:
                    movement = Movement::LEFT;
                    moveClock.start();
                    break;

                case Scancode::Right:
                    movement = Movement::RIGHT;
                    moveClock.start();
                    break;

                case Scancode::Up:
                    game.rotatePiece();
                    break;

                case Scancode::Down:
                    movement = Movement::DOWN;
                    moveClock.start();
                    break;

                case Scancode::Space:
                    game.dropDown();
                    break;
                }
            }
            else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
                using sf::Keyboard::Scancode;
                std::set keys{ Scancode::Left, Scancode::Right, Scancode::Down };

                if (keys.count(keyReleased->scancode) != 0) {
                    movement = Movement::NONE;
                    moveClock.reset();
                }
            }
        }

        window.clear();

        if (pieceDownclock.getElapsedTime() >= autoPieceDownInterval) {
            game.movePieceDown();
            game.handleCollision();
            pieceDownclock.restart();
        }

        if (moveClock.getElapsedTime() >= movePieceInterval) {
            switch (movement) {
            case Movement::LEFT:
                game.movePieceLeft();
                break;

            case Movement::RIGHT:
                game.movePieceRight();
                break;

            case Movement::DOWN:
                game.movePieceDown();
                game.handleCollision();
                break;
            }

            moveClock.restart();
        }

        game.handleLineClears();

        game.displayBoard(window);
        displayGrid(window);

        window.display();
    }
}
