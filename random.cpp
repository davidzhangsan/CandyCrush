#include <iostream>
#include <chrono>
#include <random>

using namespace std;

vector<vector<int> > randomBoard(int w, int h, int numFrosting) 
{
	//normal candies: 0, 1, 2, 3, 4, 5
	//frosting: -1

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed);
	vector<int> cells;

	for(int i = 0; i < numFrosting; i++) cells.push_back(-1);

	unsigned int l = w*h;

	while(cells.size() < l)
	{
		cells.push_back(g1() % 6);
	}

	int k = 0;

	vector<vector<int> > board(w, vector<int>(h));

	for (int i = 0; i < w; i++) 
	{
		for(int j = 0; j < h; j++, k++) 
		{
			board[i][j] = cells[k];
		}
	}

	return board;
}

int randomCandy()
{
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed);
	return g1() % 6;
}