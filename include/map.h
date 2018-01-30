#ifndef MAP_H
#define MAP_H

#include "randSeed.h"
#include "player.h"
#include <vector>
#include <iostream>
#include <chrono>

class Map
{
    public:
        Map(int mapHeight, int mapWidth, RandSeed seed);	// odd numbers 
        ~Map();

        const int GetmapWidth() const {return m_mapWidth;}
		const int GetmapHeight() const {return m_mapHeight;}
		const int GetgridAt(int i, int j) const {return m_grid[i][j];}
		const std::vector<std::vector<int>> GetupdateList() 
			const {return m_updateList;}
		const RandSeed Getseed() const {return m_seed;}
		Player Getplayer() {return m_player;}
		const std::chrono::system_clock::time_point GetgameStartTime() const {return m_gameStartTime;}
		
		void recursiveDivision2(int recursionLevel=0);
        void recursiveDivision4(int recursionLevel=0);
		friend std::ostream& operator<<(std::ostream& stream, const Map& map);
		void addToUpdateList(int i, int j);
		void addEntireGridToUpdateList();
		void clearUpdateList();
		void tryMovePlayer(int dx, int dy);
		bool canPlayerBeAt(int i, int j);
		void checkForFinish();

    protected:

    private:
        int m_mapWidth;
		int m_mapHeight;
		std::vector<std::vector<int>> m_grid;
		std::vector<std::vector<int>> m_updateList;
		RandSeed m_seed;
		std::chrono::system_clock::time_point m_gameStartTime;
		Player m_player;
};

#endif // MAP_H
