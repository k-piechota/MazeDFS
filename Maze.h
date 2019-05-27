#pragma once
#include <string>
#include <vector>  
#include "Cell.h"

class Maze
{
	int dimension;
	bool** visited;
	std::string** labirynth;

public:
	Maze(int dimension);
	void generate_maze();
	bool has_not_visited_neighbor(Cell cell);
	void show_maze();
	std::vector<int> random_direction();
	~Maze();
};