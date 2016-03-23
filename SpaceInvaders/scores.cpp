#include "scores.h"

using namespace std;
using namespace sf;

Scores::Scores(RenderWindow *w) :
	w(w)
{
	string t;
	font.loadFromFile("../data/font.ttf");
	fil.open("../scores.txt", ios::in);
	if(fil.good())
	{
		while (!fil.eof())
		{
			getline(fil, t);
			scores += t + '\n';
		}
		scores.pop_back();
	}else{

	}
	fil.close();
	fil.open("../scores.txt", ios::out | ios::app);
}

void Scores::addScore(int score)
{
	string name;
	Text tname;

	tname.setFont(font);
	tname.setCharacterSize(50);
	tname.setColor(Color(255, 255, 255));
	tname.setPosition(20, 0);

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
					if(e.key.code == Keyboard::Return && name.size() > 0)
					{
						scores += name + ';' + to_string(score) + '\n';
						fil << name + ';' + to_string(score) + '\n';
						fil.sync();
						showScores();
						return;
					}
					break;
				case Event::TextEntered:
					if(e.text.unicode < 128)
					{
						if(e.text.unicode == '\b')
						{
							if(name.size() > 0)
							{
								name.pop_back();
							}
						}
						else if(e.text.unicode == '\r' || e.text.unicode == ';' || e.text.unicode == 0x1B)
						{

						}else{
							if(name.size() < 8)
							{
								name += static_cast<char>(e.text.unicode);
							}
						}
					}
					break;
			}
		}

		tname.setString("SCORE: " + to_string(score) + "\nENTER YOUR NAME:\n\t-> " + name);

		(*w).clear();
		(*w).draw(tname);
		(*w).display();
	}
}

void Scores::showScores(void)
{
	Text s;
	Text hs;
	string t;
	vector<string> ts;
	istringstream f(scores);
	int entries = 0;

	s.setFont(font);
	s.setCharacterSize(40);
	s.setColor(Color(255, 255, 255));
	s.setPosition(60, 60);

	hs.setFont(font);
	hs.setCharacterSize(50);
	hs.setColor(Color(255, 255, 255));
	hs.setPosition(30, 0);
	hs.setString("HIGH SCORES:");

	while(!f.eof())
	{
		t.clear();
		getline(f, t);
		ts.push_back(t);
		++entries;
	}
	
	//TODO: Sort scores;

	for(int i = 0; i < entries; i++)
		t += ts[i] + '\n';

	s.setString(t);

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
					return;
					break;
			}
		}

		(*w).clear();
		(*w).draw(s);
		(*w).draw(hs);
		(*w).display();
	}
}