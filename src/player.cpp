#include "../include/player.h"
#include <string>
#include <iostream>

Player::Player(std::chrono::system_clock::time_point gameStartTime,
	int posX, int posY, int endPosX, int endPosY)
{
	m_posX = posX;
	m_posY = posY;
	m_endPosX = endPosX;
	m_endPosY = endPosY;
	m_score = 0;
	m_startTime = gameStartTime;
	m_endTime = gameStartTime;	// by default
	m_hasFinished = false;
}

Player::~Player(){};

void Player::move(int dx, int dy)
{
	m_posX += dx;
	m_posY += dy;
}

bool Player::hasFinished()
{	
	if (m_hasFinished==false && m_posX==m_endPosX && m_posY==m_endPosY)
	{
		m_hasFinished = true;
		m_endTime = std::chrono::system_clock::now();
		
		int millisecs = std::chrono::duration_cast<std::chrono::milliseconds>
			(m_endTime-m_startTime).count();
		int secs = (millisecs%60000)/1000;
		int mins = millisecs/60000;
		millisecs = millisecs%1000;
		std::string str = std::to_string(mins) + " min " 
						+ std::to_string(secs) 
						+ "." + std::to_string(millisecs) + " sec";
		
		std::cout << "Player finished after " + str << std::endl;
	}
	
	return m_hasFinished;
}