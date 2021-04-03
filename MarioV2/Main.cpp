#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#define g 0.1
#define TIME_SCALE 8000.0

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(800, 600), "Mario");

class BaseEntity
{
public:
    BaseEntity();
    BaseEntity(Sprite sprite, Vector2f position, bool isKinematic);
    ~BaseEntity();
    Sprite sprite;
    bool isKinematic;
    float speedx;
    float speedy;
    void Update(double time);
    void Draw(RenderWindow& window);

private:

};

class Game
{
public:
    Game();
    ~Game();

private:

};

class Player
{
public:
    Player();
    ~Player();

private:

};

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    Texture texture;
    texture.loadFromFile("Mario.png");
    Sprite sprite(texture);
    sprite.setScale(2, 2);
    BaseEntity entity(sprite, Vector2f(0, 0), true);


    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        entity.Update(timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
        timeClock.restart();
        
        window.clear();
        entity.Draw(window);
        window.display();
    }
}

void BaseEntity::Update(double time)
{
    if (!isKinematic)
        return;
    speedy = speedy - g * time;
    sprite.move(0, -speedy * time);
}

void BaseEntity::Draw(RenderWindow& window)
{
    window.draw(sprite);
}

BaseEntity::BaseEntity()
{
}

BaseEntity::BaseEntity(Sprite sprite, Vector2f position, bool isKinematic)
{
    speedx = 0;
    speedy = 0;
    this->sprite = sprite;
    sprite.setPosition(position);
    this->isKinematic = isKinematic;
}

BaseEntity::~BaseEntity()
{
}

Game::Game()
{
}

Game::~Game()
{
}

Player::Player()
{
}

Player::~Player()
{
}