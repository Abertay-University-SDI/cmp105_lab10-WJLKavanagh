#include "platformExample.h"

// Constructor takes name of file to load tileMap from.
platformExample::platformExample(std::string fName) 
{
	loadTexture("gfx/marioTiles.png");

	// Load in mario tiles to tileSet
	GameObject tile;
	for (int i = 0; i < 12*6+1; i++)
	{
		tile.setSize(sf::Vector2f(32, 32));
		tile.setCollisionBox(0, 0, 32, 32);
		tile.setCollider(true);
		tileSet.push_back(tile);
	}
	tileSet[0].setCollider(false);
	tileSet[0].setTextureRect(sf::IntRect(187, 51, 16, 16));
	for (int i = 1; i < 12 * 6 + 1; ++i)
	{
		int left = ((i - 1) * 17) % 204;
		int top = 17 * ((i - 1) / 12);
		tileSet[i].setTextureRect(sf::IntRect(left, top, 16,16));
	}

	// get dimensions and map from file
	tileMap = loadFromFile(fName);
	setPosition(sf::Vector2f(0, 0));
	buildLevel();
}

// Take a csv or txt file and parse ints into tile map lookup values.
// load in map dimensions from endLines and file length.
std::vector<int> platformExample::loadFromFile(const std::string fName)
{
	std::ifstream fileToOpen(fName);
	std::vector<int> mapLoadedIn;
	char delimiter;
	int value;

	// values to calculate dimensions of read-in data. line length being number of columns, line number being number of rows.
	int lineLength = 0;
	int lineNumber = 0;
	int maxLineLength = 0;
	while (fileToOpen >> value) // Read an integer
	{
		int nextVal;
		while (fileToOpen.peek() != '.' && fileToOpen.peek() != ',' && fileToOpen.peek() != ' ' && fileToOpen >> nextVal)
		{
			value *= 10;
			value += nextVal - '0'; // Convert character to integer value
		}

		lineLength++;
		mapLoadedIn.push_back(value);

		// Read the delimiter (comma or space)
		fileToOpen >> delimiter;

		if (delimiter == '.')
		{
			lineNumber++;
			if (lineLength > maxLineLength)
				maxLineLength = lineLength;
			lineLength = 0;
		}
	}
	mapDimensions = sf::Vector2u(maxLineLength, lineNumber);
	fileToOpen.close();
	return mapLoadedIn;
}

// Writes tileMap as .csv to <fName>.
// fName should include folder, e.g. "maps/____.txt" or similar.m
void platformExample::writeToFile(const std::string fName)
{
	std::ofstream fileToWrite(fName);

	for (int y = 0; y < mapDimensions.y; ++y)
	{
		for (int x = 0; x < mapDimensions.x; ++x)
		{
			fileToWrite << tileMap[y * mapDimensions.x + x];

			// Add delimiter (comma or space) if not the last value in the row
			if (x < mapDimensions.x - 1)
			{
				fileToWrite << ",";
			}
		}

		fileToWrite << "." << std::endl; // End of the row
	}

	fileToWrite.close();
}


// Change tile at <pos> with tileSet<val> and rebuilds the level. 
// NOTE: updates tileMap vector.
void platformExample::updateTile(sf::Vector2u pos, int val)
{
	// clicked outside of map, so ignore.
	if (pos.x > mapDimensions.x || pos.y > mapDimensions.y) return;

	// val is out of range of tileSet, so ignore.
	if (val >= tileSet.size() || val <= 0) return;

	int offset = pos.y * mapDimensions.x + pos.x;
	tileMap[offset] = val;
	levelAssets.clear();	// buildLevel() uses push_back so reset levelAssets first.
	buildLevel();
}

sf::Texture platformExample::getTileTexture(int v)
{
	if (v >= 0 && v < tileSet.size())
	{
		return *(tileSet[v].getTexture());
	}
	else
	{
		// Return a default texture or handle the case of invalid tile value
		// For now, returning an empty texture
		return sf::Texture();
	}
}
