#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 4
class menu

{
public:
	menu(float width, float height);
	~menu();
	void draw(sf::RenderWindow& win);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selected; }
private:
	int selected;
	sf::Font font;
	sf::Text men[MAX_NUMBER_OF_ITEMS];




};