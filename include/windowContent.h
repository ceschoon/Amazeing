#ifndef WINDOWCONTENT_H
#define WINDOWCONTENT_H

#include "map.h"
#include <SFML/Graphics.hpp>

class WindowContent
{
	public:
		WindowContent(sf::RenderWindow &window, Map &map);
		~WindowContent();

		// grid

		sf::Image m_imageGrid;
		sf::Texture m_textureGrid;
		sf::Sprite m_spriteGrid;	

		// players

		sf::Texture m_texturePlayer;
		sf::Sprite m_spritePlayer;
		
		// end portals
		
		sf::Texture m_texturePortal;
		sf::Sprite m_spritePortal;
		
		// text
		
		sf::Font font;
};

#endif // WINDOWCONTENT_H