#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class GameObject : public Sprite
{
	public:
		int frame, frames;
		Vector2u size;
		Clock animation;
		Clock delta;
		float dt;

		GameObject(Texture &t, int frames, int cols, int rows);
		void setFrame(int i);
		void update(void);
};

class Bullet : public GameObject
{
	public:
		typedef enum {
			EInvader, ESpaceship,
		} BulletType;
		BulletType type;

		Bullet(Texture &t, BulletType type, int frames, int cols, int rows);
		void update(void);
};

class Spaceship : public GameObject
{
	public:
		int live;

		Spaceship(Texture &t, int frames, int cols, int rows);
		void update(void);
};

class Invader : public GameObject
{
	public:
		int line, column, live;
		float phase;
		Vector2f original_position;
		bool dir;
		Invader(Texture &t, int column, int line, int frames, int cols, int rows);
		void update(void);
		void setOriginalPosition(Vector2f pos);
};