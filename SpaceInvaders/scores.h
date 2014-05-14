#include <fstream>
#include <sstream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

using namespace std;
using namespace sf;

class Scores
{
	private:
		RenderWindow *w;
		Event e;
		Font font;
		fstream fil;
		string scores;

	public:
		Scores(RenderWindow *w);
		void addScore(int score);
		void showScores(void);
};