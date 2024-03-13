#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	font.loadFromFile("font/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(500, 200);
	currentVal = 0;

	// initialise game objects
	tiles = new platformExample("maps/outputTest.txt");
	previewTile.setPosition(400, 200);
	previewTile.setSize(sf::Vector2f(32, 32));
	previewTexture.loadFromFile("gfx/marioTiles.png");
	previewTile.setTexture(&previewTexture);

	areaBG.setSize(sf::Vector2f(32 * 10, 32 * 6));
	areaBG.setFillColor(sf::Color::Red);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	if (input->isLeftMouseDown())
	{
		if (input->getMouseX() < 32*10 && input->getMouseY() < 6*32)
			tiles->updateTile(sf::Vector2u(input->getMouseX()/32, input->getMouseY()/32), currentVal);
		input->setLeftMouse(Input::MouseState::UP);
	}
	if (input->isKeyDown(sf::Keyboard::Up) && currentVal < 12*6)
	{
		currentVal++;
		input->setKeyUp(sf::Keyboard::Up);
	}
	if (input->isKeyDown(sf::Keyboard::Down) && currentVal > 0)
	{
		currentVal--;
		input->setKeyUp(sf::Keyboard::Down);
	}
	if (input->isKeyDown(sf::Keyboard::P))
	{
		tiles->writeToFile("maps/outputTest.txt");
	}
}

// Update game objects
void Level::update(float dt)
{
	int i = currentVal;
	int left = ((i - 1) * 17) % 204;
	int top = 17 * ((i - 1) / 12);
	previewTile.setTextureRect(sf::IntRect(left, top, 16, 16));
	text.setString(std::to_string(currentVal));
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(areaBG);
	tiles->render(window);
	window->draw(text);
	if (currentVal > 0) window->draw(previewTile);
	endDraw();
}
