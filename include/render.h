#ifndef RENDER_H
#define RENDER_H

#include "map.h"
#include "parameters.h"
#include "windowContent.h"
#include <SFML/Graphics.hpp>

void renderGrid(sf::RenderWindow &window, WindowContent &winContent, Map &map);
void renderPlayers(sf::RenderWindow &window, WindowContent &winContent, Map &map);
void renderTime(sf::RenderWindow &window, WindowContent &winContent, Map &map);
void renderEndPortals(sf::RenderWindow &window, WindowContent &winContent, Map &map);
void drawSquare(sf::Image &image, int x, int y, sf::Color color);

#endif // RENDER_H
