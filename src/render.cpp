#include "../include/render.h"
#include "../include/map.h"
#include "../include/parameters.h"
#include <iostream>
#include <string>
#include <chrono>


void renderGrid(sf::RenderWindow &window, WindowContent &winContent, Map &map)
{
	// render the squares to update	on image
	
	for (std::vector<int> square : map.GetupdateList())
	{
		int squareType = map.GetgridAt(square[0], square[1]);
		
		if (squareType==0)
		{
			drawSquare(winContent.m_imageGrid, 1+square[1], 1+square[0], sf::Color(191,191,191,255));
		}
		else if (squareType==1)
		{
			drawSquare(winContent.m_imageGrid, 1+square[1], 1+square[0], sf::Color::Black);
		}
		else {}
	}

	map.clearUpdateList();

	// draw

	winContent.m_textureGrid.update(winContent.m_imageGrid);
	winContent.m_spriteGrid.setTexture(winContent.m_textureGrid);
	window.draw(winContent.m_spriteGrid);
}

void renderPlayers(sf::RenderWindow &window, WindowContent &winContent, Map &map)
{
	// render the main player

	int posX = (map.Getplayer().getPosY()+1)*squareSize;	// x and y not the same in the maze matrix (i and j) that those in the window
	int posY = (map.Getplayer().getPosX()+1)*squareSize;

	winContent.m_spritePlayer.setColor(sf::Color(255, 0, 0));
	winContent.m_spritePlayer.setPosition(sf::Vector2f(posX, posY));
	
	window.draw(winContent.m_spritePlayer);
}

void renderTime(sf::RenderWindow &window, WindowContent &winContent, Map &map)
{
	sf::Text text;
	
	std::chrono::system_clock::time_point lap;
	
	if (map.Getplayer().hasFinished())
	{
		lap = map.Getplayer().getEndTime();
	}
	else
	{
		lap = std::chrono::system_clock::now();
	}
	
	int millisecs = std::chrono::duration_cast<std::chrono::milliseconds>(lap-map.GetgameStartTime()).count();
	int secs = (millisecs%60000)/1000;
	int mins = millisecs/60000;
	millisecs = millisecs%1000;
	std::string str = std::to_string(mins) + "." + std::to_string(secs) +
					"."	+ std::to_string(millisecs);
	str = "Time: " + str;
	
	text.setFont(winContent.font);
	text.setString(str);
	text.setCharacterSize(writingUnit);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(writingSpace/2,-writingSpace));
	
	window.draw(text);
}

void renderEndPortals(sf::RenderWindow &window, WindowContent &winContent, Map &map)
{
	// render the main player's portal

	int posX = (map.Getplayer().getEndPosY()+1)*squareSize;
	int posY = (map.Getplayer().getEndPosX()+1)*squareSize;

	winContent.m_spritePortal.setColor(sf::Color(255, 0, 0));
	winContent.m_spritePortal.setPosition(sf::Vector2f(posX, posY));
	
	window.draw(winContent.m_spritePortal);
}

void drawSquare(sf::Image &image, int x, int y, sf::Color color)
{
	for (int i=0; i<squareSize; i++)
	{
		for (int j=0; j<squareSize; j++)
		{
			image.setPixel(x*squareSize+i, y*squareSize+j, color);
		}
	}	
}