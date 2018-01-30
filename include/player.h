#ifndef PLAYER_H
#define PLAYER_H

#include <chrono>

class Player
{
	public:
		Player(std::chrono::system_clock::time_point gameStartTime = 
			std::chrono::system_clock::now(), 
			int posX=0, int posY=0, int endPosX=0, int endPosY=0);
		~Player();

		const int getPosX() const {return m_posX;}
		const int getPosY() const {return m_posY;}
		const int getEndPosX() const {return m_endPosX;}
		const int getEndPosY() const {return m_endPosY;}
		const std::chrono::system_clock::time_point getEndTime() const
			{return m_endTime;}
		
		void move(int dx, int dy);
		bool hasFinished();

	private:
		int m_posX;
		int m_posY;
		int m_endPosX;
		int m_endPosY;
		int m_score;
		std::chrono::system_clock::time_point m_startTime;
		std::chrono::system_clock::time_point m_endTime;
		bool m_hasFinished;
};

#endif // PLAYER_H