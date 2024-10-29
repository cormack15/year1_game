#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"

using namespace sf;
using namespace std;

std::vector<Ship*> ships;
sf::RenderWindow window(sf::VideoMode({ 200,200 }), "SFML works!");
sf::CircleShape shape(100.f);
sf::Texture spritesheet;
sf::Sprite invader;

void Load() {
	Invader::speed = 20.f;
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}
	invader.setTexture(spritesheet);
	invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
	Invader* inv = new Invader(sf::IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 100,100 });
	ships.push_back(inv);
	Invader* inv2 = new Invader(sf::IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 50,50 });
	ships.push_back(inv2);
	Invader* inv3 = new Invader(sf::IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 150,50 });
	ships.push_back(inv3);

	for (int r = 0; r < 10; ++r) 
	{
		auto rect = IntRect();
		for (int c = 0; c < 4; ++c)
		{
			Vector2f position = Vector2f(100, 100) ;
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}
}

void Render() {
	window.draw(invader);

	for (const auto s : ships) {
		window.draw(*s);
	}
}

void Update()
{
	//Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// check and consume events
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	// Quit via ESC key
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	for (auto& s : ships) {
		s->Update(dt);
	};

}
int main()
{
	Load();
	while (window.isOpen())
	{
		window.clear();
		Update();
		Render();
		window.display();
	}
	return 0;
}