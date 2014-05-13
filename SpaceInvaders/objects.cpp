#include <SFML\System.hpp>
#include "objects.h"

using namespace std;
using namespace sf;

GameObject::GameObject(Texture &t, int frames, int cols, int rows)
{
	//t.setSmooth(true);
	setTexture(t);
	size.x = t.getSize().x / cols;
	size.y = t.getSize().y / rows;
	this->frames = frames;
	setFrame(0);
}

void GameObject::setFrame(int i)
{
	if(i < frames)
	{
		setTextureRect(IntRect((i % frames) * size.x, (i / frames) * size.y, size.x, size.y));
		frame = i;
	}
}

Bullet::Bullet(Texture &t, BulletType type, int frames, int cols, int rows) :
	GameObject(t, frames, cols, rows)
{
	this->type = type;
}

void Bullet::update(void)
{
	switch(type)
	{
		case EInvader:
			move(0, 2);
			break;
		case ESpaceship:
			move(0, -5);
			break;
	}
}

Spaceship::Spaceship(Texture &t, int frames, int cols, int rows) :
	GameObject(t, frames, cols, rows)
{
	setOrigin(size.x / 2, size.y / 2);
	live = 2;
}

void Spaceship::update(void)
{

}

Invader::Invader(Texture &t, int column, int line, int frames, int cols, int rows) :
	GameObject(t, frames, cols, rows)
{
	this->line = line;
	this->column = column;
	phase = 0;
	animation.restart();
	delta.restart();
}

void Invader::update(void)
{
	float dt = delta.restart().asSeconds();
	
	if(line % 2)
		phase += 3 * dt;
	else
		phase -= 3 * dt;

	if(sin(phase) >= 0)
		setFrame(0);
	else
		setFrame(1);

	move(sin(phase) * 0.6, abs(sin(phase)) * 0.08);
}
