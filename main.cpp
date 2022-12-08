#include "game.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool won;
int moves;
game current;

bool checkForEmpty ()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (current.get(i, j) == 0) return true;
        }
    }
    return false;
}

int main()
{
    cout << "Welcome to Candy Crush by David and Lucas!\nType \"start\" to begin!\n";
    string s;
    while (getline(cin, s))
    {
        istringstream iss {s};
        string command;

        iss >> command;

        if (command == "start")
        {
            current = game();
            cout << current << endl;
        }

        else if (command == "swap")
        {
            //maybe a score calculator? or set some form of objective of the game
        }

        else if (command == "save")
        {

        }

        else if (command == "load")
        {
            string filePath;
            iss >> filePath;
            current = game(filePath);
        }

        else
        {
            cout << "Type \"start\" to start a new game, or \"swap x1 y1 x2 y2\" to swap the two candies at coordinates (x1, y1) and (x2, y2).\n";
        }
    }
}