#include "Maze.h"

#include <vector>
#include <set>
#include <time.h>
//using namespace std;

struct wall {
	int one;
	int two;
};
typedef std::set<int> chamber;

#define LEFT 0x02
#define RIGHT 0x01
#define UP 0x08
#define DOWN 0x04

void GenerateWalls(std::vector<chamber>& cellSet, std::vector<wall>& walls, int width, int height)
{
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			int cO = x+y*width;
			chamber initChamber;
			initChamber.insert(cO);
			cellSet.push_back(initChamber);
			//Check to make sure walls only extend to the mazeSize-1 count on each axis.
			//This prevents the maze from over-extending and blocking all exits.
			if(x+1 < width)
			{
				wall wX;
				wX.one = cO;
				wX.two = cO+1; //Same as (x+1)+y*width
				walls.push_back(wX);
			}
			if(y+1 < height)
			{
				wall wY;
				wY.one = cO;
				wY.two = cO+width; //Same as x+(y+1)*width
				walls.push_back(wY);
			}
		}
	}
}

void RemoveWall(int *grid, wall w, int width, int height)
{
	int x0 = w.one % width;
	int x1 = w.two % width;
	int y0 = w.one / width;
	int y1 = w.two / width;
	
	if(y1 >= height || x1 >= width)
		return;

	if(y0 == y1)
	{
		grid[w.one] &= ~RIGHT;
		grid[w.two] &= ~LEFT;	
	}
	else
	{
		grid[w.one] &= ~DOWN;
		grid[w.two] &= ~UP;
	}
}

int* CreateMaze(int width, int height)
{
	std::vector<chamber> chambers;
	std::vector<wall> walls;

	GenerateWalls(chambers, walls, width, height);
	
	srand ( (unsigned int)time(NULL) );
	int wallsSize = (int)walls.size();
	for(int i = 0; i < wallsSize; i++)
	{
		int randIdx = (rand() + i) % wallsSize;//(i+1);
		wall temp1 = walls[i];
		walls[i] = walls[randIdx];
		walls[randIdx] = temp1;
	}

	int size = width * height;
	int *grid = new int[size];
	for(int i = 0; i < size; i++)
		grid[i] = 0x0f;

	int cell1Idx = 0;
	int cell2Idx = 0;
	for(int j = 0; j < (int)walls.size(); j++)
	{
		for(int i = 0; i < (int)chambers.size(); i++)
		{
			if(chambers[i].find(walls[j].one) != chambers[i].end())
				cell1Idx = i;
			if(chambers[i].find(walls[j].two) != chambers[i].end())
				cell2Idx = i;
		}
		//Determine whether or not the two
		//chambers have already been merged
		if(cell1Idx != cell2Idx)
		{
			chambers[cell1Idx].insert(chambers[cell2Idx].begin(), chambers[cell2Idx].end());
			RemoveWall(grid, walls[j], width, height);
			chambers.erase(chambers.begin()+cell2Idx);
		}
	}

	return grid;
}
