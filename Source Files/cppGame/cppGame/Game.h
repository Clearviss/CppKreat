#pragma once

//cpp libraries
#include <iostream>
#include <vector>
#include <ctime>
//libraries

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>



// Game Engine ?

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// Mouse position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Game Logic
	bool endgame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseDown;

	//Ojects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	//sf::RectangleShape hover;

	void initializeVariables();
	void initWindow();
	void initEnemies();


public:
	// Contstructors
	Game();
	virtual ~Game();

	//Accessors 
	const bool getWindowIsOpen() const;
	const bool getEndGame() const;


	// Functions
	void spawnEnemy();
	

	void pollEvents();
	void updateMousePos();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};

