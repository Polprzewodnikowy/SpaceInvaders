#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "game.h"
#include "menu.h"
#include "scores.h"

using namespace std;
using namespace sf;

int main(void)
{
	srand(time(NULL));
	RenderWindow w(VideoMode(800, 600, 32), "Space Invaders", Style::Close);
	w.setVerticalSyncEnabled(true);

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