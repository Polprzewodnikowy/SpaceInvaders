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
	setFrame(0);
}

void GameObject::setFrame(int i)
{
	if(i < frames)
	{
		setTextureRect(IntRect((i % frames) * size.x, (i / frames) * size.y, size.x, size.y));
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
	live = 10;
}

void Spaceship::update(void)
{

}

Invader::Invader(Texture &t, int column, int line, int frames, int cols, int rows) :
	GameObject(t, frames, cols, rows)
{
	this->line = line;
	this->column = column;
	if(line % 2)
	{
		dir = true;
	}
	else{
		dir = false;
	}
	live = 2;
	animation.restart();
}

void Invader::update(void)
{
	if(animation.getElapsedTime().asMilliseconds() >= 1000)
	{
		++frame;
		if(frame >= frames)
		{
			frame = 0;
		}
		setFrame(frame);
		if(dir)
		{
			move(5, 1);
			dir = false;
		}
		else{
			move(-5, 1);
			dir = true;
		}
		animation.restart();
	}
}
