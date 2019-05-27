#include<iostream>
#include <ctime>
#include "Maze.h"

int main() 
{
	srand((unsigned int)time(NULL));
	
	int dimension;
	std::cout << "For given M program generates square maze of dimension M x M. " << std::endl;
	std::cin >> dimension;
		
	Maze maze = Maze(dimension);
	maze.generate_maze();
	maze.show_maze();

	system("pause");

}