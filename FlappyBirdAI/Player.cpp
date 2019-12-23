#include "Player.h"

void Player::update(RenderWindow & window,std::deque<Pipe> &pipes,Clock &clock,Text &text,int &bestScore)
{

	for (std::size_t i = 0; i < pipes.size(); ++i) {
		if (pipes[i].isColliding(bird.pos)) {
			bird.isDead = true;
		}
		if (!pipes[i].isPassed && pipes[i].passedPipe(bird.pos.x)) {
			bird.pipesPassed++;
			text.setString("");
			std::string str = std::to_string(bird.pipesPassed);
			text.setString(str);
			if (bird.pipesPassed > bestScore) bestScore = bird.pipesPassed;
		}
	}
	if (brain.guess({ bird.vel.y,bird.pos.x - pipes[0].pos.x,bird.pos.y - (pipes[0].pos.y - 125.f),pipes[0].pos.y - bird.pos.y,1 })) {
		bird.flap();
	}
	if (!gameOver) {
		if (bird.isDead) {
			fitness = (float)clock.getElapsedTime().asMilliseconds() * (float)clock.getElapsedTime().asMilliseconds();
			gameOver = true;
		}
	}
	bird.update(window);
}
