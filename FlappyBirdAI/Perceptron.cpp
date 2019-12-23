#include "Perceptron.h"

bool Perceptron::guess(std::vector<float> inputs)
{
	float sum = 0.f;
	for (std::size_t i = 0; i < inputs.size(); ++i) {
		sum += inputs[i] * weights[i];
	}
	if (sum >= 5.f) {
		return true;
	}

	return false;
}

std::vector<float> Perceptron::copyBrain()
{
	return weights;
}

void Perceptron::mutateWeights()
{
	float mutationRate = 0.9f;
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_real_distribution<float> dist(0.f, 1.f);
	std::uniform_real_distribution<float> disti(-.1f, .1f);
	
	for (std::size_t i = 0; i < weights.size(); ++i) {
		float rand = dist(gen);
		if ((float)rand < mutationRate) {
			weights[i] += disti(gen);
		}
	}
}
