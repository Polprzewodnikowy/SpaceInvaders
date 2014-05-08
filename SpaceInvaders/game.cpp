#include <cstdlib>
#include "game.h"

using namespace std;
using namespace sf;

Game::Game(RenderWindow (*w))
{
	this->w = w;
	shpt.loadFromFile("../data/shp.png");
	invt.loadFromFile("../data/inv.png");
	bltt.loadFromFile("../data/blt.png");
	font.loadFromFile("../data/font.ttf");
	music.openFromFile("../data/music.ogg");

	for(int i = 0; i < 10; i++)
	{
		for(int n = 0; n < 20; n++)
		{
			Invader inv(invt, n, i, 2, 2, 1);
			float x, y;
			x = inv.size.x / 2 + 16 + n * (inv.size.x + 16) + (i % 2) * -8;
			y = inv.size.y / 2 + 40 + i * (inv.size.y + 8);
			inv.setPosition(x, y);
			if(i % 2)
				inv.setFrame(1);
			invaders.push_back(inv);
		}
	}

	score.setFont(font);
	score.setCharacterSize(30);
	score.setColor(Color(51, 255, 0));
	score.setPosition(24, 0);

	live.setFont(font);
	live.setCharacterSize(30);
	live.setColor(Color(255, 0, 0));
	live.setString("LIVES: 2");
	live.setPosition((*w).getSize().x - live.getGlobalBounds().width - 24, 0);

	music.setVolume(20);
	music.setLoop(true);
	music.play();
}

bool Game::pauseGame(void)
{
	Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setColor(Color(255, 255, 255));
	text.setString("PAUSE");
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition((*w).getSize().x / 2, (*w).getSize().y / 2);

	(*w).draw(text);
	(*w).display();

	while((*w).isOpen())
	{
		while((*w).pollEvent(e))
		{
			switch(e.type)
			{
				case Event::Closed:
					(*w).close();
					break;
				case Event::KeyPressed:
					switch(e.key.code)
					{
						case Keyboard::Escape:
							return true;
							break;
						default:
							return false;
							break;
					}
					break;
			}
		}
	}
	return false;
}

void Game::overGame(void)
{
	Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	text.setColor(Color(255, 255, 255));
	text.setString("GAME OVER\nSCORE: " + to_string(iscore));
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition((*w).getSize().x / 2, (*w).getSize().y / 2);
	(*w).draw(text);
	(*w).display();

	while((*w).isOpen())
	{
		while((*w).pollEvent(e))
		{
			switch(e.type)
			{
				case Event::Closed:
					(*w).close();
					break;
				case Event::KeyPressed:
					switch(e.key.code)
					{
						case Keyboard::Left:
						case Keyboard::Right:
						case Keyboard::Up:
						case Keyboard::Down:
						case Keyboard::Space:
							break;
						default:
							return;
							break;
					}
					break;
			}
		}
	}
}

int Game::startGame(void)
{
	Spaceship spaceship(shpt, 1, 1, 1);

	spaceship.setPosition((*w).getSize().x / 2, (*w).getSize().y - spaceship.size.y / 2 - 16);
	spaceship.setTexture(shpt);

	while((*w).isOpen())
	{
		while((*w).pollEvent(e))
		{
			switch(e.type)
			{
				case Event::Closed:
					(*w).close();
					break;
				case Event::KeyPressed:
					switch(e.key.code)
					{
						case Keyboard::P:
						case Keyboard::Escape:
							if(pauseGame())
							{
								overGame();
								return iscore;
							}
							break;
					}
					break;
			}
		}

		spaceship.update();

		if(Keyboard::isKeyPressed(Keyboard::Left))
		{
			if(spaceship.getPosition().x > 20)
				spaceship.move(-3, 0);
		}
		else if(Keyboard::isKeyPressed(Keyboard::Right))
		{
			if(spaceship.getPosition().x < (*w).getSize().x - 20)
				spaceship.move(3, 0);
		}
		if(Keyboard::isKeyPressed(Keyboard::Space))
		{
			if(sdelay.getElapsedTime().asMilliseconds() >= 250)
			{
				Bullet b(bltt, Bullet::ESpaceship, 1, 1, 1);
				b.setPosition(spaceship.getPosition());
				bullets.push_back(b);
				sdelay.restart();
			}
		}

		if(idelay.getElapsedTime().asSeconds() >= 1)
		{
			if(invaders.size())
			{
				int r = rand() % invaders.size();
				Bullet b(bltt, Bullet::EInvader, 1, 1, 1);
				b.setPosition(invaders[r].getPosition());
				bullets.push_back(b);
			}
			idelay.restart();
		}

		for(vector<Bullet>::iterator itb = bullets.begin(); itb < bullets.end(); ++itb)
		{
			if((*itb).type == Bullet::ESpaceship)
			{
				if((*itb).getPosition().y < 0)
				{
					bullets.erase(itb);
					continue;
				}
				for(vector<Invader>::iterator iti = invaders.begin(); iti < invaders.end(); ++iti)
				{
					if((*itb).getGlobalBounds().intersects((*iti).getGlobalBounds()))
					{
						iscore += 10;
						invaders.erase(iti);
						bullets.erase(itb);
					}
				}
			}
			else if((*itb).type == Bullet::EInvader)
			{
				if((*itb).getPosition().y > (*w).getSize().y)
				{
					bullets.erase(itb);
				}
				if((*itb).getGlobalBounds().intersects(spaceship.getGlobalBounds()))
				{
					--spaceship.live;
					bullets.erase(itb);
				}
			}
		}

		score.setString("SCORE: " + to_string(iscore));
		live.setString("LIVES: " + to_string(spaceship.live));

		(*w).clear();

		for(vector<Invader>::iterator it = invaders.begin(); it < invaders.end(); ++it)
		{
			if((*it).getPosition().y > (*w).getSize().y - 64)
			{
				overGame();
				return iscore;
			}
			(*it).update();
			(*w).draw(*it);
		}

		for(vector<Bullet>::iterator it = bullets.begin(); it < bullets.end(); ++it)
		{
			(*it).update();
			(*w).draw(*it);
		}

		(*w).draw(spaceship);
		(*w).draw(score);
		(*w).draw(live);
		(*w).display();
		if(spaceship.live <= 0 || !invaders.size())
		{
			overGame();
			return iscore;
		}
	}
	return 0;
}