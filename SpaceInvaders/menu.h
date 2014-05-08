#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

using namespace std;
using namespace sf;

class Menu
{
	private:
		RenderWindow *w;
		Event e;
		Font font;
		Text m[4], title;
		int x, y;

	public:
		typedef enum {
			EGame = 0, EExit = 3, EAuthors = 2, EScores = 1,
		} MenuValue;

		Menu(RenderWindow *w);
		MenuValue showMenu(void);
};