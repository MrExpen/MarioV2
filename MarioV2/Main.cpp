//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include "Game.h"

#define W 800
#define H 600
#define TIME_SCALE 800.0f

using namespace sf;

RenderWindow window(VideoMode(W, H), "SFML works!");

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    Game game;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        game.Update(timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
        timeClock.restart();

        window.clear(Color::White);
        game.Draw(window);
        window.display();
    }
}
