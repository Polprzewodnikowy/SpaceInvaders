#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "game.h"
#include "menu.h"

using namespace std;
using namespace sf;

int main(void)
{
	srand(time(NULL));
	RenderWindow w(VideoMode(800, 600, 32), "Space Invaders");
	w.setVerticalSyncEnabled(true);

	Menu menu(&w);

	while(w.isOpen())
	{
		switch(menu.showMenu())
		{
			case Menu::EGame:
			{
				Game game(&w);
				game.startGame();
				break;
			}
			case Menu::EExit:
				w.close();
				break;
		}
	}

	return 0;
}