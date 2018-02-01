#include "../include/windowContent.h"
#include "../include/parameters.h"

WindowContent::WindowContent(sf::RenderWindow &window, Map &map)
{
	// grid

	m_imageGrid.create((map.GetmapWidth()+2)*squareSize, (map.GetmapHeight()+2)*squareSize, sf::Color::Black);
	m_textureGrid.create((map.GetmapWidth()+2)*squareSize, (map.GetmapHeight()+2)*squareSize);

	// players

	if (!m_texturePlayer.loadFromFile("resources/textures/player.png"))
	{
    	// ERROR
	}
	m_spritePlayer.setTexture(m_texturePlayer);
	
	// end portals

	if (!m_texturePortal.loadFromFile("resources/textures/endPortal.png"))
	{
    	// ERROR
	}
	m_spritePortal.setTexture(m_texturePortal);
	
	// text
	
	if (!font.loadFromFile("resources/fonts/NotoSans-Bold.ttf"))
	{
   		// error...
	}
}

WindowContent::~WindowContent(){};