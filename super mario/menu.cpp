#include "menu.h"
#include <iostream>
#include <string>
using namespace std;
menu::menu(float width, float height)


{

	if (!font.loadFromFile("text3.ttf"))
	{
		cout << "error";
	}
	men[0].setFont(font);
	men[0].setCharacterSize(70);
	men[0].setFillColor(sf::Color::White);
	men[0].setStyle(sf::Text::Underlined);
	men[0].setString("Start");
	men[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.5));
	men[1].setFont(font);
	men[1].setCharacterSize(70);
	men[1].setFillColor(sf::Color::White);
	men[1].setStyle(sf::Text::Underlined);
	men[1].setString("How To play");
	men[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	men[2].setFont(font);
	men[2].setCharacterSize(70);
	men[2].setFillColor(sf::Color::White);
	men[2].setStyle(sf::Text::Underlined);
	men[2].setString("About Us");
	men[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.5));
	men[3].setFont(font);
	men[3].setCharacterSize(70);
	men[3].setFillColor(sf::Color::White);
	men[3].setStyle(sf::Text::Underlined);
	men[3].setString("Exit");
	men[3].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	selected = 0;
}
menu::~menu()
{
}
void menu::draw(sf::RenderWindow& win)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		win.draw(men[i]);
	}
}
void menu::MoveUp()
{
	if (selected - 1 >= 0) {

		men[selected].setFillColor(sf::Color::White);
		men[selected].setCharacterSize(50);
		selected--;
		men[selected].setFillColor(sf::Color::White);
		men[selected].setCharacterSize(70);
	}

}
void menu::MoveDown()
{
	if (selected + 1 < MAX_NUMBER_OF_ITEMS) {

		men[selected].setFillColor(sf::Color::White);
		men[selected].setCharacterSize(50);

		selected++;
		men[selected].setFillColor(sf::Color::White);
		men[selected].setCharacterSize(70);

	}

}