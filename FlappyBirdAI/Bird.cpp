#include "Bird.h"

void Bird::flap()
{
	if (!isDead) {
		vel.y = 0.f;
		vel.y -= 250 * gravity;
	}
}

void Bird::update(sf::RenderWindow & window)
{
	bird.setTexture(birdT);
	if (pos.y <= 620.f) vel.y += gravity; else pos.y = 620.f;
	if (pos.y < 0.f || pos.y > 619.f) isDead = true;
	pos += vel;
	bird.setPosition(pos);
	window.draw(bird);
}
