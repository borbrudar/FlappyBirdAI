#include "Pipe.h"

void Pipe::update(sf::RenderWindow & window,bool isDead)
{
	pipeB.setTexture(pB);
	pipeT.setTexture(pT);	
	if(!isDead) pos.x -= .1f;
	rectBottom.setPosition(pos);
	rectTop.setPosition(sf::Vector2f(pos.x, 0));
	pipeT.setPosition(Vector2f(pos.x,pos.y - 471.f - 175.f));
	pipeB.setPosition(pos);
	window.draw(pipeB);
	window.draw(pipeT);
}

bool Pipe::isOffscreen(float birdPos)
{
	if (this->pos.x <= birdPos - 100.f) {
		return true;
	}
	return false;
}

bool Pipe::isColliding(sf::Vector2f pos)
{
	if (pos.x + 20.f > this->pos.x && pos.x  < this->pos.x + 50.f && pos.y + 20.f > this->pos.y) {
		return true;
	}
	if (pos.x + 20.f > this->pos.x && pos.x < this->pos.x + 50.f && pos.y < this->pos.y - 125.f) {
        return true;
	}
	return false;
}

bool Pipe::passedPipe(float posX)
{
	if (posX > this->pos.x + 50.f) {
		isPassed = true;
		return true;
	}
	return false;
}
