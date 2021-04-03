#include <SFML/Graphics.hpp>
#include <vector>

#define g 9.8

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
    bool onGround;
    float speedx;
    float speedy;
    void Update(float& time);
    void Draw(RenderWindow& window);

private:

};

int main()
{
    window.setVerticalSyncEnabled(true);
    Clock timeClock;
    vector<BaseEntity*> BaseEntitys;
    RectangleShape shape(Vector2f(20, 20));
    shape.setFillColor(Color::Blue);
    shape.setPosition(0, 0);
    BaseEntitys.push_back(new BaseEntity(Sprite(*shape.getTexture()), Vector2f(0, 0), true));
    

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        timeClock.restart();

        window.clear();
        window.display();
    }
}

void BaseEntity::Update(float& time)
{
    if (!isKinematic)
        return;
    if (onGround)
        return;
    speedy = speedy + g * time;
    sprite.move(0, speedy * time);
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
    this->sprite = sprite;
    sprite.setPosition(position);
    this->isKinematic = isKinematic;
}

BaseEntity::~BaseEntity()
{
}
