#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#define g 0.15
#define TIME_SCALE 8000.0
#define Mu 0.1
#define a 0.15

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(800, 600), "Mario");

class BaseEntity
{
public:
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

enum GameAction : short
{
    PlayerTakeDamage,
    PlayerDead,
    EnemyTakeDamage,
    EnemyDead
};

enum Direction : bool
{
    Right,
    Left
};

class Player : public BaseEntity
{
public:
    int health;
    Player();
    ~Player();
    Player(Vector2f position);
    Vector2f spawn;
    virtual void Update(double time) override;
    void Jump();
    GameAction TakeDamage();
    Direction direction;

private:

};

class BaseEnemy : public BaseEntity
{
public:
    ~BaseEnemy();
    BaseEnemy(Vector2f position, bool isKinematic);
    virtual GameAction onPlayerEnter(Player& player);
    virtual void Die();

private:

};

class Enemy : public BaseEnemy
{
public:
    Enemy(Vector2f position);
    virtual void Update(double time) override;
    virtual GameAction onPlayerEnter(Player& player) override;
    virtual void Die() override;
    ~Enemy();

private:

};

class Wall :public BaseEntity
{
public:
    ~Wall();
    int spriteindex;
    Wall(Vector2f position, int spriteindex);

private:

};

enum State : short
{
    GameOn,
    GamePause,
    GameOver
};

class Game
{
public:
    Game();
    ~Game();
    Player player;
    string lvlName;
    State state;
    vector<Wall*> walls;
    vector<BaseEnemy*> enemies;
    View view;
    void Update(double time);
    void Draw(RenderWindow& window);
    void LoadLevel(string levelName);
    Texture texturePlayer;
    vector<Texture*> texturesWall;
    Texture textureEnemy;

private:

};

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    Game game;
    Color color(117, 255, 255);
    game.LoadLevel("1lvl.txt");
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            if (e.type == Event::KeyPressed)
            {
                if (e.key.code == Keyboard::Escape)
                {
                    if (game.state != State::GameOver)
                    {
                        game.state = (State)!bool(game.state);
                    }
                }
            }
        }

        if (game.state == State::GameOn)
        {
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                game.player.Jump();
                if (game.player.speedy > 0)
                    game.player.speedy += 0.093 * (timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
            }
            if (abs(game.player.speedx) <= 3)
            {
                if (Keyboard::isKeyPressed(Keyboard::Right))
                {
                    game.player.speedx += a;
                }
                if (Keyboard::isKeyPressed(Keyboard::Left))
                {
                    game.player.speedx -= a;
                }
            }

            game.Update(timeClock.getElapsedTime().asMicroseconds() / TIME_SCALE);
        }
        timeClock.restart();
        
        window.clear(color);
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

BaseEntity::~BaseEntity()
{
}

Game::Game()
{
    texturePlayer.loadFromFile("Mario.png");
    textureEnemy.loadFromFile("enemy1.png");
    for (int i = 0; i < 8; i++)
    {
        Texture* textureWall = new Texture();
        textureWall->loadFromFile("Walls.png", IntRect(Vector2i(i * 32, 0), Vector2i(32, 32)));
        texturesWall.push_back(textureWall);
    }
    state = State::GamePause;
    view = View(Vector2f(0, 0), Vector2f(800, 600));
}

Game::~Game()
{
}

void Game::LoadLevel(string levelName)
{
    lvlName = levelName;
    for (auto wall : walls)
    {
        wall->~Wall();
    }
    walls.clear();

    ifstream fin(levelName);
    int n = 0;
    for (std::string line; getline(fin, line); )
    {
        for (int i = 0; i < line.size(); i++)
        {
            switch (line[i])
            {
            case '#':
                walls.push_back(new Wall(Vector2f(32 * i, 32 * n), 0));
                break;
            case '*':
                walls.push_back(new Wall(Vector2f(32 * i, 32 * n), 3));
                break;
            case '@':
                player = Player(Vector2f(32 * i, 32 * n));
                break;
            case '!':
                enemies.push_back(new Enemy(Vector2f(32 * i, 32 * n)));
            }
        }
        n++;
    }
    fin.close();
    state = State::GameOn;
}

void Game::Update(double time)
{
    for (auto wall : walls)
    {
        if (player.speedx > 0 && abs(wall->position.y - player.position.y) < 32)
        {
            float posx = player.position.x + player.speedx * time;
            if (wall->position.x - posx < 24 && wall->position.x - posx > 0)
            {
                player.speedx = 0;
                player.position.x = wall->position.x - 24;
            }
        }
        else if(player.speedx < 0 && abs(wall->position.y - player.position.y) < 32)
        {
            float posx = player.position.x + player.speedx * time;
            if (posx - wall->position.x < 32 && posx - wall->position.x > 0)
            {
                player.speedx = 0;
                player.position.x = wall->position.x + 32;
            }
        }
        for (auto enemy : enemies)
        {
            if (enemy->speedx > 0 && abs(wall->position.y - enemy->position.y) < 32)
            {
                float posx = enemy->position.x + enemy->speedx * time;
                if (wall->position.x - posx < 30 && wall->position.x - posx > 0)
                {
                    enemy->speedx = -enemy->speedx;
                    enemy->position.x = wall->position.x - 30;
                }
            }
            else if (enemy->speedx < 0 && abs(wall->position.y - enemy->position.y) < 32)
            {
                float posx = enemy->position.x + enemy->speedx * time;
                if (posx - wall->position.x < 32 && posx - wall->position.x > 0)
                {
                    enemy->speedx = -enemy->speedx;
                    enemy->position.x = wall->position.x + 32;
                }
            }
        }
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        for (int j = i + 1; j < enemies.size(); j++)
        {
            if (abs(enemies[i]->position.x - enemies[j]->position.x) <= 32 && abs(enemies[i]->position.y - enemies[j]->position.y) <= 32)
            {
                enemies[i]->speedx = -enemies[i]->speedx;
                enemies[j]->speedx = -enemies[j]->speedx;
            }
        }
    }

    for (auto enemy : enemies)
    {
        enemy->Update(time);
        float difx = enemy->position.x - player.position.x, dify = enemy->position.y - player.position.y;
        if (abs(dify) < 32 && difx < 24 && difx > -32)
        {
            switch (enemy->onPlayerEnter(player))
            {
            case GameAction::EnemyDead:
                enemies.erase(find(enemies.begin(), enemies.end(), enemy));
                enemy->~BaseEnemy();
                break;
            case GameAction::PlayerDead:
                state = State::GameOver;
                break;
            case GameAction::PlayerTakeDamage:
                player.position = player.spawn;
                break;
            }
        }
    }
    player.Update(time);
    for (auto wall : walls)
    {
        if (wall->position.x - player.position.x < 24 && wall->position.x - player.position.x > -32 && wall->position.y - player.position.y < 32 && wall->position.y - player.position.y > 0)
        {
            player.position.y = wall->position.y - 32;
            player.speedy = 0;
        }
        if (wall->position.x - player.position.x < 24 && wall->position.x - player.position.x > -32 && wall->position.y - player.position.y > -32 && wall->position.y - player.position.y < 0)
        {
            player.position.y = wall->position.y + 32;
            player.speedy = -0.00001f;
        }
        for (auto enemy : enemies)
        {
            if (wall->position.x - enemy->position.x < 30 && wall->position.x - enemy->position.x > -32 && wall->position.y - enemy->position.y < 32 && wall->position.y - enemy->position.y > 0)
            {
                enemy->position.y = wall->position.y - 32;
                enemy->speedy = 0;
            }
            if (wall->position.x - enemy->position.x < 30 && wall->position.x - enemy->position.x > -32 && wall->position.y - enemy->position.y > -32 && wall->position.y - enemy->position.y < 0)
            {
                enemy->position.y = wall->position.y + 32;
                enemy->speedy = -0.00001;
            }
        }
    }
}

void Game::Draw(RenderWindow& window)
{
    Sprite spritePlayer(texturePlayer), spriteEnemy1(textureEnemy);
    vector<Sprite> spritesWall;
    for (auto texture: texturesWall)
    {
        spritesWall.push_back(Sprite(*texture));
    }

    for (auto var : walls)
    {
        var->Draw(spritesWall[var->spriteindex], window);
    }
    if (player.direction == Direction::Left)
    {
        spritePlayer.setScale(-2, 2);
        spritePlayer.setOrigin(12, 0);
    }
    else
    {
        spritePlayer.setScale(2, 2);
    }
    player.Draw(spritePlayer, window);
    for (auto enemy : enemies)
    {
        enemy->Draw(spriteEnemy1, window);
    }
    view.setCenter(player.position.x/1.1f+100, 100+player.position.y/2.0f);
    window.setView(view);
}

void Player::Update(double time)
{
    BaseEntity::Update(time);
    position.x += speedx * time;
    if (abs(speedx) >= a)
    {
        if (speedx > 0)
            speedx -= Mu;
        else if (speedx < 0)
            speedx += Mu;
    }
    else speedx = 0;
    if (speedx > 0)
    {
        direction = Direction::Right;
    }
    else if (speedx < 0)
    {
        direction = Direction::Left;
    }
}

void Enemy::Update(double time)
{
    BaseEntity::Update(time);
    position.x += speedx * time;
}

Player::Player() : BaseEntity(Vector2f(0, 0), true, true)
{
    health = 3;
    direction = Direction::Right;
}

Player::~Player()
{
}

GameAction Player::TakeDamage()
{
    if (--health <= 0)
    {
        return GameAction::PlayerDead;
    }
    return GameAction::PlayerTakeDamage;
}

void Player::Jump()
{
    if (speedy == 0)
    {
        speedy = 3.8;
    }
}

Player::Player(Vector2f position) : BaseEntity(position, true, true)
{
    spawn = position;
    health = 3;
    direction = Direction::Right;
}

Enemy::Enemy(Vector2f position) : BaseEnemy(position, true)
{
    speedx = 1;
}

Enemy::~Enemy()
{
}

GameAction BaseEnemy::onPlayerEnter(Player& player)
{
    return player.TakeDamage();
}

GameAction Enemy::onPlayerEnter(Player &player)
{
    if (player.speedy < -0.5)
    {
        this->Die();
        player.speedy = 2;
        return GameAction::EnemyDead;
    }
    else
    {
        return player.TakeDamage();
    }
}

void BaseEnemy::Die()
{
}

Wall::Wall(Vector2f position, int spriteindex) : BaseEntity(position, false, true)
{
    this->spriteindex = spriteindex;
}

Wall::~Wall()
{
}

BaseEnemy::BaseEnemy(Vector2f position, bool isKinematic) : BaseEntity(position, isKinematic, true)
{
}

BaseEnemy::~BaseEnemy()
{
}

void Enemy::Die()
{

}
