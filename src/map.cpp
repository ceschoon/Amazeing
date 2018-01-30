#include "../include/map.h"
#include "../include/randSeed.h"
#include <cstdlib>

/*
 * Convention:  0 = empty space
 *				1 = wall
 */


Map::Map(int mapHeight, int mapWidth, RandSeed seed)
{
	if (mapWidth%2==1)
	{
		m_mapWidth = mapWidth;
	}
	else
	{
		m_mapWidth = mapWidth+1;
		std::cout << "Width of labyrinth must be an odd number";
		// GENERER UNE ERREUR
	}
	if (mapHeight%2==1)
	{
		m_mapHeight = mapHeight;
	}
	else
	{
		m_mapHeight = mapHeight+1;
		std::cout << "Height of labyrinth must be an odd number";
		// GENERER UNE ERREUR
	}

	std::vector<int> tempVector(mapWidth, 0);
	std::vector<std::vector<int>> tempGrid(mapHeight, tempVector);
	m_grid = tempGrid;
	m_seed = seed;
	m_gameStartTime = std::chrono::system_clock::now();
	m_player = Player(m_gameStartTime, mapHeight-1, 0, 0, mapWidth-1);
}

Map::~Map(){};

std::ostream& operator<<(std::ostream& stream, const Map& map) 
{
	for (int i=0; i<map.GetmapHeight(); i++)
	{
		for (int j=0; j<map.GetmapWidth(); j++)
		{
			std::cout << map.GetgridAt(i,j);
		}
		if (i<map.GetmapHeight()-1){std::cout << std::endl;}
	}  
	
    return stream;
}

void Map::addToUpdateList(int i, int j)
{
	m_updateList.push_back({i,j});
}
void Map::clearUpdateList()
{
	m_updateList.clear();
}
void Map::addEntireGridToUpdateList()
{
	for (int i=0; i<GetmapHeight(); i++)
	{
		for (int j=0; j<GetmapWidth(); j++)
		{
			addToUpdateList(i,j);
		}
	}
}

void Map::recursiveDivision2(int recursionLevel)
{
	int N = (m_mapHeight)/2;
	int M = (m_mapWidth)/2;
	
	if (N==0 || M==0)
	{
		// do nothing
	}
	else
	{
		// create a wall
		
		int randIndex = 0;
		
		if (recursionLevel%2==0)
		{
			randIndex = m_seed.randomWithSeed()%M;
			for (int i=0; i<2*N+1; i++)
			{
				m_grid[i][2*randIndex+1]=1;
			}		
		}
		else
		{
			randIndex = m_seed.randomWithSeed()%N;
			for (int i=0; i<2*M+1; i++)
			{
				m_grid[2*randIndex+1][i]=1;
			}
		}

		// make a hole in the wall
		
		int randIndex2 = 0;

		if (recursionLevel%2==0)
		{
			randIndex2 = m_seed.randomWithSeed()%(N+1);
			m_grid[2*randIndex2][2*randIndex+1] = 0;
		}
		else
		{
			randIndex2 = m_seed.randomWithSeed()%(M+1);
			m_grid[2*randIndex+1][2*randIndex2] = 0;
		}

		// recursion

		if (recursionLevel%2==0) 
		{
			Map map1(2*N+1,2*randIndex+1,m_seed);
			Map map2(2*N+1,2*(M-randIndex-1)+1,m_seed);

			map1.recursiveDivision2(recursionLevel+1);
			map2.recursiveDivision2(recursionLevel+1);

			for (int i=0; i<2*N+1; i++)
			{
				for (int j=0; j<2*randIndex+1; j++)
				{
					m_grid[i][j] = map1.GetgridAt(i,j);
				}
			}
			for (int i=0; i<2*N+1; i++)
			{
				for (int j=2*randIndex+2; j<2*M+1; j++)
				{
					m_grid[i][j] = map2.GetgridAt(i,j-2*randIndex-2);
				}
			}
		}
		else
		{
			Map map1(2*randIndex+1,2*M+1,m_seed);
			Map map2(2*(N-randIndex-1)+1,2*M+1,m_seed);

			map1.recursiveDivision2(recursionLevel+1);
			map2.recursiveDivision2(recursionLevel+1);

			for (int i=0; i<2*randIndex+1; i++)
			{
				for (int j=0; j<2*M+1; j++)
				{
					m_grid[i][j] = map1.GetgridAt(i,j);
				}
			}
			for (int i=2*randIndex+2; i<2*N+1; i++)
			{
				for (int j=0; j<2*M+1; j++)
				{
					m_grid[i][j] = map2.GetgridAt(i-2*randIndex-2,j);
				}
			}
		}
	}

	if (recursionLevel==0)
	{
		clearUpdateList();
		addEntireGridToUpdateList();
	}
}

void Map::recursiveDivision4(int recursionLevel)
{
	int N = (m_mapHeight)/2;
	int M = (m_mapWidth)/2;
	
	if (N==0 || M==0)
	{
		// do nothing
	}
	else
	{
		// create two walls
		
		int randI = m_seed.randomWithSeed()%N;
		int randJ = m_seed.randomWithSeed()%M;

		for (int i=0; i<2*M+1; i++)
		{
			m_grid[2*randI+1][i]=1;
		}
		for (int i=0; i<2*N+1; i++)
		{
			m_grid[i][2*randJ+1]=1;
		}

		// make holes in the walls
		
		int randI2 = m_seed.randomWithSeed()%(N+1);
		int randJ2 = m_seed.randomWithSeed()%(M+1);
		int randI3 = randI2;
		int randJ3 = randJ2;

		while (randI3==randI2)
		{
			randI3 = m_seed.randomWithSeed()%(N+1);
		}
		while (randJ3==randJ2)
		{
			randJ3 = m_seed.randomWithSeed()%(M+1);
		}
		
		m_grid[2*randI+1][2*randJ2] = 0;
		m_grid[2*randI2][2*randJ+1] = 0;
		m_grid[2*randI+1][2*randJ3] = 0;
		m_grid[2*randI3][2*randJ+1] = 0;

		// recursion		
		
		Map map11(2*randI+1,2*randJ+1,m_seed);
		Map map12(2*randI+1,2*(N-randJ-1)+1,m_seed);
		Map map21(2*(N-randI-1)+1,2*randJ+1,m_seed);
		Map map22(2*(N-randI-1)+1,2*(N-randJ-1)+1,m_seed);

		map11.recursiveDivision4(recursionLevel+1);
		map12.recursiveDivision4(recursionLevel+1);
		map21.recursiveDivision4(recursionLevel+1);
		map22.recursiveDivision4(recursionLevel+1);

		for (int i=0; i<2*randI+1; i++)
		{
			for (int j=0; j<2*randJ+1; j++)
			{
				m_grid[i][j] = map11.GetgridAt(i,j);
			}
		}
		for (int i=0; i<2*randI+1; i++)
		{
			for (int j=2*randJ+2; j<2*M+1; j++)
			{
				m_grid[i][j] = map12.GetgridAt(i,j-2*randJ-2);
			}
		}
		for (int i=2*randI+2; i<2*N+1; i++)
		{
			for (int j=0; j<2*randJ+1; j++)
			{
				m_grid[i][j] = map21.GetgridAt(i-2*randI-2,j);
			}
		}
		for (int i=2*randI+2; i<2*N+1; i++)
		{
			for (int j=2*randJ+2; j<2*M+1; j++)
			{
				m_grid[i][j] = map22.GetgridAt(i-2*randI-2,j-2*randJ-2);
			}
		}
	}

	if (recursionLevel==0)
	{
		clearUpdateList();
		addEntireGridToUpdateList();
	}
}

void Map::tryMovePlayer(int dx, int dy)
{
	int i = m_player.getPosX()+dx;
	int j = m_player.getPosY()+dy;
	if (i>=0 && i<m_mapHeight && j>=0 && j<m_mapWidth)
	{
		if (!m_player.hasFinished() && canPlayerBeAt(i,j))
		{
			m_player.move(dx,dy);
		}
	}
}

bool Map::canPlayerBeAt(int i, int j)
{
	bool canIt = true;
	
	if (m_grid[i][j]==1) {canIt=false;}
		
	return canIt;
}

void Map::checkForFinish()
{
	m_player.hasFinished();
}
