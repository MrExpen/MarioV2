#include <SFML/Graphics.hpp>
#include "BaseEntity.h"

using namespace sf;

RenderWindow window(VideoMode(800, 600), "Mario");

int main()
{
    window.setVerticalSyncEnabled(true);

    

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}