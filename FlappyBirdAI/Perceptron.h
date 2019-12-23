#pragma once
#include <random>

class Perceptron {
public:
	Perceptron() {
		std::random_device rd;
		std::default_random_engine generator(rd());
		std::uniform_real_distribution<float> dist(-1.f, 1.f);
		
		weights.resize(5);
		for (std::size_t i = 0; i < weights.size(); ++i) {
			weights[i] = dist(generator);
		}
	}
	bool guess(std::vector<float> inputs);
	std::vector<float> copyBrain();
	void mutateWeights();

	std::vector<float> weights;


};