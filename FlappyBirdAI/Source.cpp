#include <SFML/Graphics.hpp>
#include "Population.h"
#include "Pipe.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <deque>

using namespace sf;
int main() {
	RenderWindow window;
	window.create(VideoMode(480, 640), "Flappy bird AI");
	window.setPosition(Vector2i(400, 30));
	Event event;
	Clock clock;
	
	std::deque<Pipe> pipes = { Pipe(160.f),Pipe(320.f),Pipe(480.f),Pipe(640.f) };

	Population p(10);

	Texture background;
	background.loadFromFile("images/background.png");
	Sprite back; 
	back.setTexture(background);
	back.setScale(3.5f, 2.5f);
	Player pl;

	Font font;
	font.loadFromFile("fonts/arial/ArialCEBold.ttf");
	Text text;
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(3.f);
	text.setPosition(230.f, 25.f);
	text.setString(std::to_string(0));
	Text geni;
	geni.setFont(font);
	geni.setFillColor(Color::White);
	geni.setOutlineColor(Color::Black);
	geni.setOutlineThickness(3.f);
	geni.setPosition(360.f, 25.f);
	geni.setCharacterSize(20);
	
	clock.restart();

	int gen = 1;
	int bestScore = 0;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				/*if (event.key.code == Keyboard::Space && bird.vel.y >= bird.gravity / 20.f) {
					bird.flap();
				}*/
			}
		}

		geni.setString(std::string("Gen: " + std::string(std::to_string(gen))));
		if (p.overGame) {
			gen++;
			p.naturalSelection(clock);
			pipes = { Pipe(160.f),Pipe(320.f),Pipe(480.f),Pipe(640.f) };
			for (std::size_t i = 0; i < p.players.size(); ++i) {
				p.players[i].bird.pipesPassed = 0;
			}
			geni.setString("0");
		}
		
		window.clear(Color(135, 206, 250));
		//-------------------------------------------
		window.draw(back);
		for (std::size_t i = 0; i < pipes.size(); ++i) {
				pipes[i].update(window, p.gameOver());
			
		}
		p.update(window,pipes,clock,text,bestScore);
		window.draw(text);
		geni.setPosition(360.f, 25.f);
		window.draw(geni);
		geni.setString("Best score: " + std::to_string(bestScore));
		geni.setPosition(30.f, 25.f);
		window.draw(geni);
			//-------------------------------------------
			window.display();
			if (pipes[0].isOffscreen(p.players[0].bird.pos.x)) {
				pipes.pop_front();
				pipes.push_back(Pipe(640.f));
			}
		}
	return 0;
}