#include <SFML\System.hpp>
#include "objects.h"

using namespace std;
using namespace sf;

GameObject::GameObject(Texture &t, int frames, int cols, int rows)
{
	setTexture(t);
	size.x = t.getSize().x / cols;
	size.y = t.getSize().y / rows;
	this->frames = frames;
	dt = 0;
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

void GameObject::update(void)
{

}

Bullet::Bullet(Texture &t, BulletType type, int frames, int cols, int rows) :
	GameObject(t, frames, cols, rows)
{
	this->type = type;
}

void Bullet::update(void)
{
	dt = delta.restart().asSeconds();
	
	switch(type)
	{
		case EInvader:
			move(0, 150 * dt);
			break;
		case ESpaceship:
			move(0, -300 * dt);
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
	dt = delta.restart().asSeconds();
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
	dt = delta.restart().asSeconds();

	if(line % 2)
		phase -= dt;
	else
		phase += dt;

	setPosition(original_position + Vector2f(sin(phase * 3) * 12, abs(phase * 3)));

	if(sin((phase * 3) + ((line % 2) ? (3.14159265358979323846 / 2) : -(3.14159265358979323846 / 2))) >= 0)
		setFrame(0);
	else
		setFrame(1);
}

void Invader::setOriginalPosition(Vector2f pos)
{
	original_position = pos;
	setPosition(pos);
}
