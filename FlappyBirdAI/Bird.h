#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
class Bird {
public:
	Bird(sf::Vector2f position) {
		bird.setPosition(position);
		birdT.loadFromFile("images/bird.png");
		bird.setTexture(birdT);
		bird.setScale(Vector2f(1.5f, 1.5f));
		pos = position;
	}
	void flap();
	void update(sf::RenderWindow &window);

	sf::Vector2f pos;
	sf::Vector2f vel{0.f,0.f};
	Texture birdT;
	Sprite bird;
	float gravity = .002f;
	bool isDead = false;
	int pipesPassed = 0;
};