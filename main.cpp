#include "include/map.h"
#include "include/render.h"
#include "include/parameters.h"
#include "include/randSeed.h"
#include "include/windowContent.h"
#include "include/initParameters.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char *argv[])
{
	// load parameters

	int mapSizeX = 25;
	int mapSizeY = 25;
	int windowBaseSize = 480;
	int seedGiven = -1;
	
	bool interrupt = initParameters(argc, argv, mapSizeX, mapSizeY, seedGiven, windowBaseSize);
    if (interrupt){return 0;}
    
    // create the window
	
	sf::RenderWindow window(sf::VideoMode(windowBaseSize, 
		windowBaseSize+writingSpace), "Amazeing");
		
	sf::View viewGrid(sf::FloatRect(0, 0, (mapSizeX+2)*squareSize, 
		(mapSizeY+2)*squareSize));
	viewGrid.setViewport(sf::FloatRect(0, 
		double(writingSpace)/double(windowBaseSize+2*writingSpace), 1, 
		double(windowBaseSize)/double(windowBaseSize+writingSpace)));
	sf::View viewBarUp(sf::FloatRect(0,-writingSpace,
		(mapSizeX+2)*squareSize,writingSpace));
	viewBarUp.setViewport(sf::FloatRect(0, 0, 1, 
		double(writingSpace)/double(windowBaseSize+writingSpace)));
/*
	sf::View viewBarDown(sf::FloatRect(0,-writingSpace,
		(mapSizeX+2)*squareSize,writingSpace));
	viewBarDown.setViewport(sf::FloatRect(0,
		double(windowBaseSize+writingSpace)/double(windowBaseSize	
		+2*writingSpace), 1, 
		double(writingSpace)/double(windowBaseSize+2*writingSpace)));
*/
		
	// create the map

	RandSeed seed;
	if (seedGiven!=-1){seed = RandSeed(seedGiven);}
	Map map(mapSizeY,mapSizeX,seed);
	map.recursiveDivision2();

	// create the window's objects

	WindowContent winContent(window, map);

	// main loop
	
	int prevTimeStep = 0;
	bool gameFinished = false;
	
    while (window.isOpen())
    {			
		// event handling

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
			{
				
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				// move view
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 						sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.move(-viewVelocity, 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.move(viewVelocity, 0);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && 
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.move(0, viewVelocity);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.move(0, -viewVelocity);
				}
				
				// zoom view

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.zoom(0.8f);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) &&
						 sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				{
    				viewGrid.zoom(1.25f);
				}

				// get seed

				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
    				std::cout << "seed: " << map.Getseed().getSeed() << 
    					std::endl;
				}
			}
        }

		// processing objects
		
		std::chrono::system_clock::time_point lap =
			std::chrono::system_clock::now();
		int millisecs = std::chrono::duration_cast<std::chrono::milliseconds>
			(lap-map.GetgameStartTime()).count();
		int timeStep = millisecs/millisecsToWaitBeforeMovingPlayer;
	
		if (timeStep!=prevTimeStep)
		{
			prevTimeStep = timeStep;
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				map.tryMovePlayer(0, -1);	// matrix indices
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
					 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				map.tryMovePlayer(0, 1);	
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
					 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				map.tryMovePlayer(1, 0);	
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
					 && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				map.tryMovePlayer(-1, 0);	
			}
		}
		
		map.checkForFinish();
		
		// render the map
		
		window.clear();

		window.setView(viewGrid);
		renderGrid(window, winContent, map);
		renderPlayers(window, winContent, map);
		renderEndPortals(window, winContent, map);

		window.setView(viewBarUp);
		renderTime(window, winContent, map);
		
		//window.setView(viewBarDown);

		window.display();

		// pause
		
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecsMinToWaitPerLoop));
	}
	
	return 0;
}