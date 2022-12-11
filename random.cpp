#include <iostream>
#include <chrono>
#include <random>
#include "game.hpp"

using namespace std;

vector<vector<Candy>> randomBoard() 
{
	//normal candies: 1, 2, 3, 4, 5, 6
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g(seed);
	vector<int> cells;

	for(int i = 0; i < 81; i++) cells.push_back(g() % 6 + 1);

	int k = 0;

	vector<vector<Candy> > board(9, vector<Candy>(9));

	for (int i = 0; i < 9; i++) 
	{
		for(int j = 0; j < 9; j++, k++) 
		{
			board[i][j] = static_cast<Candy>(cells[k]);
		}
	}

	return board;
}

Candy randomCandy()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g(seed);
	return static_cast<Candy>(g() % 6 + 1);
}