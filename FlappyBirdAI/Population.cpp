#include "Population.h"

void Population::update(RenderWindow & window, std::deque<Pipe>& pipes, Clock & clock,Text &text,int &bestScore)
{
	for (std::size_t i = 0; i < players.size(); ++i) {
		players[i].update(window, pipes, clock,text,bestScore);
	}
}

bool Population::gameOver()
{
	for (std::size_t i = 0; i < players.size(); ++i) {
		if (players[i].bird.isDead == false) {
			return false;
	}
	}
	overGame = true;
	return true;
}

void Population::chooseBestBird()
{
	std::sort(players.begin(), players.end(), [](const Player &a, const Player &b) { return a.fitness < b.fitness; });
	std::reverse(players.begin(), players.end());
}


void Population::naturalSelection(Clock & clock)
{
	chooseBestBird();

	std::vector<Player> newPlayers(10);
	std::vector<float> newWeights(5);

	if (prevBestPlayer.fitness < players[0].fitness) {
		newWeights = players[0].brain.copyBrain();
		//crossover test
		/*newWeights[0] = players[0].brain.weights[0];
		newWeights[1] = players[0].brain.weights[1];
		newWeights[2] = players[0].brain.weights[2];
		newWeights[3] = players[1].brain.weights[3];
		newWeights[4] = players[1].brain.weights[4];*/
	}else {
		newWeights = prevBestPlayer.brain.copyBrain();
	}

	for (std::size_t i = 1; i < players.size(); ++i) {
		newPlayers[i].brain.weights = newWeights;
		newPlayers[i].brain.mutateWeights();
	}
	newPlayers[0].brain.weights = newWeights;
	prevBestPlayer = players[0];
	players = newPlayers;
	overGame = false;
	
	clock.restart();
}
