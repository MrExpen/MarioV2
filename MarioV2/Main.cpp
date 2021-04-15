//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include "Game.h"

#define W 800
#define H 600
#define TIME_SCALE 8000.0f

using namespace sf;

RenderWindow window(VideoMode(W, H), "SFML works!");

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    Game game;
    game.LoadLevel("1lvl.txt");

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (game.State == GameState::GameOn)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                game.Player.Jump();
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                game.Player.Move = Move::Left;
            }
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if (game.Player.Move == Move::Left)
                {
                    game.Player.Move = Move::None;
                }
                else
                {
                    game.Player.Move = Move::Right;
                }
            }

            game.Update(timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
        }
        timeClock.restart();

        window.clear(Color::White);
        game.Draw(window);
        window.display();
    }
}
