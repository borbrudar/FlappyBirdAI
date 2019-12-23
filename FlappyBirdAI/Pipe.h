#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

using namespace sf;
class Pipe {
public:
	Pipe() = default;
	Pipe(float x_pos) {
		rectBottom.setFillColor(sf::Color::Green);
		rectTop.setFillColor(sf::Color::Green);
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> dist(120, 360);
		rectBottom.setSize(sf::Vector2f(50.f, (float) dist(generator)));
		rectTop.setSize(sf::Vector2f(50.f, 640.f - rectBottom.getSize().y - 125.f));
		rectBottom.setPosition(sf::Vector2f(x_pos, 640.f - rectBottom.getSize().y));
		pos = sf::Vector2f(x_pos, 640.f - rectBottom.getSize().y);

		pB.loadFromFile("images/pipeBottom.png");
		pipeB.setScale(sf::Vector2f(1.92f, 3.86f));

		pT.loadFromFile("images/pipeTop.png");
		pipeT.setScale(Vector2f(1.92f, 3.86f));
	}

	void update(sf::RenderWindow &window,bool isDead);
	bool isOffscreen(float birdPos);
	bool isColliding(sf::Vector2f pos);
	bool passedPipe(float posX);
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::RectangleShape rectBottom;
	sf::RectangleShape rectTop;
	bool isPassed = false;
	Texture pB;
	Texture pT;
	Sprite pipeB;
	Sprite pipeT;
};