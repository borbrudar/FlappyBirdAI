#pragma once
#include "Perceptron.h"
#include "Bird.h"
#include "Pipe.h"
#include <deque>

class Player {
public:

	void update(RenderWindow &window,std::deque<Pipe> &pipes,Clock &clock,Text &text,int &bestScore);
	Bird bird = ( Vector2f(50.f, 240.f) );
	Perceptron brain;
	float fitness = 0.f;
	bool gameOver = false;
};