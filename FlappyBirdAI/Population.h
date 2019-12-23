#pragma once
#include "Player.h"


class Population {
public:
	Population(int number) {
		players.resize(number);
	}
	void update(RenderWindow &window, std::deque<Pipe> &pipes, Clock &, Text &text,int &bestScore);
	bool gameOver();
	void chooseBestBird();
	void naturalSelection(Clock &clock);
	std::vector<Player> players;
	Player prevBestPlayer;
	float fitnessSum = 0.f;
	bool overGame = false;
};