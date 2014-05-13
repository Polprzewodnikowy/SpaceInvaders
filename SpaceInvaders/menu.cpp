#include "menu.h"

using namespace std;
using namespace sf;

Menu::Menu(RenderWindow *w) :
	w(w),
	x(20),
	y(400)
{
	font.loadFromFile("../data/font.ttf");
	for(int i = 0; i < 4; ++i)
	{
		m[i].setFont(font);
		m[i].setCharacterSize(40);
		m[i].setColor(Color(255, 255, 255));
	}

	title.setFont(font);
	title.setCharacterSize(80);
	title.setColor(Color(51, 255, 0));

	m[0].setString("START GAME");
	m[1].setString("HIGH SOCRES");
	m[2].setString("AUTHORS");
	m[3].setString("EXIT");
	title.setString("SPACE INVADERS");

	m[0].setPosition(x + 20, y);
	m[1].setPosition(x + 20, y + 40);
	m[2].setPosition(x + 20, y + 80);
	m[3].setPosition(x + 20, y + 120);
	title.setPosition(40, 0);
}

Menu::MenuValue Menu::showMenu(void)
{
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
						return EExit;
						break;
					case Keyboard::Return:
						return EGame;
						break;
				}
				break;
			}
		}

		(*w).clear();

		for(int i = 0; i < 4; ++i)
		{
			if(m[i].getGlobalBounds().contains(Mouse::getPosition(*w).x, Mouse::getPosition(*w).y))
			{
				m[i].setColor(Color(51, 255, 0));
				if(Mouse::isButtonPressed(Mouse::Left))
					return (MenuValue)i;
			}else{
				m[i].setColor(Color(255, 255, 255));
			}
				
			(*w).draw(m[i]);
		}

		(*w).draw(title);

		(*w).display();
	}
	return EExit;
}

void Menu::showAuthors(void)
{
	Text authors;

	authors.setFont(font);
	authors.setCharacterSize(50);
	authors.setColor(Color(255, 255, 255));
	authors.setPosition(20, 0);
	authors.setString("PROGRAMMING:\n\tFADEREWSKI MATEUSZ\n\nGRAPHICS:\n\tHUBERT PERCZYNSKI");

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
				case Event::MouseButtonPressed:
					return;
					break;
			}
		}

		(*w).clear();
		(*w).draw(authors);
		(*w).display();
	}
}