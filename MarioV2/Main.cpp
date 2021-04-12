//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>

using namespace sf;

RenderWindow window(VideoMode(200, 200), "SFML works!");

int main()
{
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }
}
