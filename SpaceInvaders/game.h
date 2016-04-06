#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include "objects.h"

using namespace std;
using namespace sf;

class Game
{
	private:
		RenderWindow *w;
		Texture shpt, invt, bltt;
		Font font;
		Text score, live;
		Event e;
		Clock sdelay, idelay;
		Music music;
		int iscore = 0;
		vector<Invader> invaders;
		vector<Bullet> bullets;
		Spaceship *spaceship;

	public:
		Game(RenderWindow *w);
		bool pauseGame(void);
		void overGame(void);
		int startGame(void);
};