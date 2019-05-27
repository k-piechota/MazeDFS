#include "Maze.h"
#include <stack>
#include <algorithm>
#include <iostream>

Maze::Maze(int dimension)
{
	this->dimension = dimension;
	visited = new bool* [dimension + 2];
	labirynth = new std::string * [2 * dimension + 1];

	for (int i = 0; i < dimension + 2; i++)
		visited[i] = new bool[dimension + 2];

	for (int i = 0; i < 2 * dimension + 1; i++)
		labirynth[i] = new std::string[2 * dimension + 1];

	for (int x = 0; x < dimension + 2; x++)
		for (int y = 0; y < dimension + 2; y++)
			visited[x][y] = 0;

	for (int x = 0; x < dimension + 2; x++)
	{
		visited[0][x] = true;
		visited[x][0] = true;
		visited[dimension + 1][x] = true;
		visited[x][dimension + 1] = true;
	}

	for (int x = 0; x < 2 * dimension + 1; x++)
		for (int y = 0; y < 2 * dimension + 1; y++)
		{
			if (x % 2 == 0 && y % 2 == 0) labirynth[x][y] = "+";
			if (x % 2 == 0 && y % 2 == 1) labirynth[x][y] = "---";
			if (x % 2 == 1 && y % 2 == 0) labirynth[x][y] = "|";
			if (x % 2 == 1 && y % 2 == 1) labirynth[x][y] = "   ";
		}

	labirynth[1][0] = " ";											//START
	labirynth[dimension * 2][dimension * 2 - 1] = "   ";			//EXIT
}


//--------------------------------------------------------------------------------------------------------------------


void Maze::generate_maze()
{
	std::stack <Cell> myStack;
	int xRand = std::rand() % dimension+1;
	int yRand = std::rand() % dimension+1;

	Cell cell = Cell(xRand, yRand);							//Starting from random Cell
	myStack.push(cell);
	visited[xRand][yRand] = 1;

	int iterator = 1;
	while (!myStack.empty())
	{
		cell = myStack.top();
		if (has_not_visited_neighbor(cell))
		{
			std::vector<int> randomDirections = random_direction();
			bool success = false;
			for (int i = 0; i < 4; i++)
			{
				int direction = randomDirections[i];
				switch (direction)
				{
				case 0:											//GO UP

					if (visited[cell.get_x()][cell.get_y() - 1] == 0)
					{
						Cell newCell = Cell(cell.get_x(), cell.get_y() - 1);
						myStack.push(newCell);
						visited[newCell.get_x()][newCell.get_y()] = 1;
						success = true;
						labirynth[cell.get_x() * 2 - 1][(cell.get_y() * 2 - 2)] = " ";
					}

					break;
				
				case 1:											//GO RIGHT

					if (visited[cell.get_x() + 1][cell.get_y()] == 0)
					{
						Cell newCell = Cell(cell.get_x() + 1, cell.get_y());
						myStack.push(newCell);
						visited[newCell.get_x()][newCell.get_y()] = 1;
						success = true;
						labirynth[(cell.get_x() * 2)][cell.get_y() * 2 - 1] = "   ";
					}

					break;

				case 2:											// GO DOWN

					if (visited[cell.get_x()][cell.get_y() + 1] == 0)
					{
						Cell newCell = Cell(cell.get_x(), cell.get_y() + 1);
						myStack.push(newCell);
						visited[newCell.get_x()][newCell.get_y()] = 1;
						success = true;
						labirynth[cell.get_x() * 2 - 1][(cell.get_y() * 2)] = " ";
					}

					break;

				case 3:											//GO LEFT

					if (visited[cell.get_x() - 1][cell.get_y()] == 0)
					{
						Cell newCell = Cell(cell.get_x() - 1, cell.get_y());
						myStack.push(newCell);
						visited[newCell.get_x()][newCell.get_y()] = 1;
						success = true;
						labirynth[(cell.get_x() * 2 - 2)][cell.get_y() * 2 - 1] = "   ";
					}

					break;

				}
				if (success)
					break;
			}
			iterator++;
		}
		else
			myStack.pop();

		system("CLS");
		std::cout << "Generating maze. Progress = " << (100 * iterator) / (dimension * dimension) << "%.";
		std::cout << std::endl;
	}

}


//--------------------------------------------------------------------------------------------------------------------


bool Maze::has_not_visited_neighbor(Cell cell)
{
	int x = cell.get_x();
	int y = cell.get_y();

	if (visited[x - 1][y] == 0 || visited[x + 1][y] == 0
		|| visited[x][y - 1] == 0 || visited[x][y + 1] == 0)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------------------------------------------------------

//Printing function
void Maze::show_maze()
{
	system("CLS");

	for (int x = 0; x < 2 * dimension + 1; x++)
	{
		std::cout << std::endl;
		for (int y = 0; y < 2 * dimension + 1; y++)
		{
			std::cout << labirynth[x][y];
		}
	}

	std::cout << std::endl;
}

//--------------------------------------------------------------------------------------------------------------------

//Returns vector with 4 directions in random order
std::vector<int> Maze::random_direction()
{
	std::vector<int> myVector;

	for (int i = 0; i < 4; i++)
		myVector.push_back(i);

	std::random_shuffle(myVector.begin(), myVector.end());

	return myVector;
}

//--------------------------------------------------------------------------------------------------------------------


Maze::~Maze()
{
	for (int i = 0; i < dimension + 2; i++)
		delete[] visited[i];
	for (int i = 0; i < 2 * dimension + 1; i++)
		delete[] labirynth[i];

	delete[] visited;
	delete[] labirynth;
}
