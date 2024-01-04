#include "Game.h"


//private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	//Game logic
	int points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	this->points = 0;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 1.f;
	this->maxEnemies = 10;

}

void Game::initWindow()
{
	this->videomode.height = 600;
	this->videomode.width = 800;
	
	this->window = new sf::RenderWindow(this->videomode, "Kreat", sf::Style::Default);

	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	// Hover rectangle for change color on hover
	/*this->hover.setPosition(sf::Vector2f(250.f, 250.f));
	this->hover.setSize(sf::Vector2f(300.f, 100.f));
	this->hover.setFillColor(sf::Color::Blue);*/

	this->enemy.setPosition(sf::Vector2f(350.f, 250.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(2.f);
}

//Constructors 
Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initEnemies();
	this->spawnEnemy();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemy.setFillColor(sf::Color::Red);

	this->enemies.push_back(this->enemy);
}

void Game::pollEvents()
{
	// Something happening here polling or whatever
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			// Closing window 
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) this->window->close();
		}
	}

}

void Game::updateMousePos()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	// Spawn Timer logic
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
	// Enemies move
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 3.f);

		// click collision
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				this->points += 10;
			}
		}
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}
		if (deleted) this->enemies.erase(this->enemies.begin() + i);

	}

}

void Game::update()
{
	this->pollEvents();
	this->updateMousePos();
	this->updateEnemies();
	// Screen relative aka viewpoint
	// std::cout << "Mouse Position: " << sf::Mouse::getPosition().x << ", " << sf::Mouse::getPosition().y << std::endl;
	// Window relative
	std::cout << "Mouse Position: " << sf::Mouse::getPosition(*this->window).x << ", " << sf::Mouse::getPosition(*this->window).y << std::endl;
	

	// Box (this->enemy) on the center of mouse position this->enemy.setPosition(sf::Vector2f(sf::Mouse::getPosition(*this->window).x - 25, sf::Mouse::getPosition(*this->window).y - 25));


	// small test: Change color on hover (All done by myself) however it's probably not very efficient 
	/*if ((this->enemy.getPosition().x >= 250 || this->enemy.getPosition().x + 50 >= 250) && this->enemy.getPosition().x <= 550 && (this->enemy.getPosition().y >= 250 || this->enemy.getPosition().y + 50 >= 250) && this->enemy.getPosition().y <= 350)
	{
		this->hover.setFillColor(sf::Color::Green);
	}
	else
	{
		this->hover.setFillColor(sf::Color::Blue);
	}*/
}

void Game::renderEnemies()
{

	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}

void Game::render()
{
	// Rendering part

	//Clearing with 
	this->window->clear();
	//Drawing
	// drawing hover rectangle see init this->window->draw(this->hover);
	 this->renderEnemies();

	this->window->display();
}
