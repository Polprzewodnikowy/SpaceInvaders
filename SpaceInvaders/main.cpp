#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "game.h"
#include "menu.h"
#include "scores.h"

using namespace std;
using namespace sf;

int main(int argc, char *argv[])
{
	bool vsync = false;
	int framelimit = 60;

	cout << "Space Invaders v0.9" << endl << endl
		<< "Avaiable arguments:" << endl << endl
		<< "\t-help - View help (this)" << endl
		<< "\t-vsync - Enable vertical sync, overrides framelimit settings" << endl
		<< "\t-fr [number] - Set frame limit from 1 to 240 (default 60)" << endl << endl
		<< "https://github.com/Polprzewodnikowy/SpaceInvaders" << endl;

	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			if(!strcmp(argv[i], "-vsync"))
			{
				vsync = true;
			}
			else if(!strcmp(argv[i], "-fr"))
			{
				if(argv[i + 1] && isdigit(argv[i + 1][0]))
				{
					framelimit = strtol(argv[i + 1], NULL, 10);
					if(framelimit < 1 || framelimit > 240)
						framelimit = 60;
					++i;
				}
			}
			else if(!strcmp(argv[i], "-help"))
			{
				return 0;
			}else{
				cout << "Invalid argument: " << argv[i] << endl;
			}
		}		
	}

	srand(time(NULL));
	RenderWindow w(VideoMode(800, 600, 32), "Space Invaders", Style::Close);

	cout << endl;

	if(vsync)
	{
		w.setVerticalSyncEnabled(true);
		cout << "Vsync: enabled" << endl;
	}else{
		w.setFramerateLimit(framelimit);
		cout << "Frame limit: " << framelimit << endl;
	}

	Menu menu(&w);
	Scores scores(&w);

	while(w.isOpen())
	{
		switch(menu.showMenu())
		{
			case Menu::EGame:
			{
				Game game(&w);
				scores.addScore(game.startGame());
				break;
			}
			case Menu::EScores:
				scores.showScores();
				break;
			case Menu::EAuthors:
				menu.showAuthors();
				break;
			case Menu::EExit:
				w.close();
				break;
		}
	}

	return 0;
}