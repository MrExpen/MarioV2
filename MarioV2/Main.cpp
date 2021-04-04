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
    BaseEntity(Vector2f position, bool isKinematic, bool canCollide);
    ~BaseEntity();
    Vector2f position;
    bool isKinematic;
    bool canCollide;
    float speedx;
    float speedy;
    virtual void Update(double time);
    virtual void Draw(Sprite& sprite, RenderWindow& window);

private:

};

class Player : public BaseEntity
{
public:
    Player();
    ~Player();
    Player(Vector2f position);
    virtual void Update(double time) override;
    void Jump();

private:

};

class Enemy : public BaseEntity
{
public:
    Enemy();
    ~Enemy();

private:

};

class Wall :public BaseEntity
{
public:
    Wall();
    ~Wall();
    Wall(Vector2f position);

private:

};

class Game
{
public:
    Game();
    ~Game();
    Player player;
    vector<Wall*> walls;
    void Update(double time);
    void Draw(RenderWindow& window);
    Texture texturePlayer;
    Texture textureWall;

private:

};

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    Game game;


    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            game.player.Jump();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            game.player.speedx += 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            game.player.speedx -= 3;
        }


        game.Update(timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
        timeClock.restart();
        
        window.clear();
        game.Draw(window);
        window.display();
    }
}

void BaseEntity::Update(double time)
{
    if (!isKinematic)
        return;
    position.y += -speedy * time;
    speedy = speedy - g * time;
}

void BaseEntity::Draw(Sprite& sprite,RenderWindow& window)
{
    sprite.setPosition(position);
    window.draw(sprite);
}

BaseEntity::BaseEntity(Vector2f position, bool isKinematic, bool canCollide)
{
    speedx = 0;
    speedy = 0;
    this->canCollide = canCollide;
    this->position = position;
    this->isKinematic = isKinematic;
}

BaseEntity::BaseEntity()
{
}

BaseEntity::~BaseEntity()
{
}

Game::Game()
{
    textureWall.loadFromFile("Wall.png");
    texturePlayer.loadFromFile("Mario.png");

    this->player = Player(Vector2f(0, 0));
    
    for (int i = 0; i < 20; i++)
    {
        walls.push_back(new Wall(Vector2f(i * 32, 128)));
    }
    for (int i = 0; i < 5; i++)
    {
        walls.push_back(new Wall(Vector2f(128, 64 + 32 + i*32)));
    }
}

Game::~Game()
{
}

void Game::Update(double time)
{
    for(auto var : walls)
    {
        var->Update(time);
    }
    player.Update(time);
    for (auto wall : walls)
    {
        if (wall->position.x - player.position.x < 32 && wall->position.x - player.position.x > 0 && wall->position.y - player.position.y < 32)
        {
            player.position.x = wall->position.x - 32;
        }
        /*else if(wall->position.x - player.position.x > -32 && wall->position.x - player.position.x < 0 && wall->position.y - player.position.y < 32)
        {
            player.position.x = wall->position.x + 32;
        }*/
        if (abs(wall->position.x - player.position.x) < 32 && wall->position.y - player.position.y < 32)
        {
            player.position.y = wall->position.y - 32;
            player.speedy = 0;
        }
    }
}

void Game::Draw(RenderWindow& window)
{
    Sprite spriteWall(textureWall), spritePlayer(texturePlayer);
    spritePlayer.scale(2, 2);
    for (auto var : walls)
    {
        var->Draw(spriteWall, window);
    }
    player.Draw(spritePlayer, window);
}

void Player::Update(double time)
{
    BaseEntity::Update(time);
    position.x += speedx * time;
    speedx = 0;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Jump()
{
    if (speedy == 0)
    {
        speedy = 3;
    }
}

Player::Player(Vector2f position) : BaseEntity(position, true, true)
{

}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

Wall::Wall()
{
}

Wall::Wall(Vector2f position) : BaseEntity(position, false, true)
{

}

Wall::~Wall()
{
}