#include "game.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool inGame;
game current;

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
            while (current.check3())
            {
                current = game();
            }

            cout << current << endl;
            inGame = true;

        }

        else if (command == "swap")
        {
            if (!inGame)
            {
                cout << "Type start to begin a new game!\n";
                continue;
            }
            // Check to make sure that swap works
            int x1, y1, x2, y2;
            iss >> x1;
            iss >> y1;
            iss >> x2;
            iss >> y2;
            current.swap(x1, y1, x2, y2);
            if (!current.check3()) {
                cout << "Please swap two valid candies!" << endl;
                current.swap(x1, y1, x2, y2);
                continue;
            }

            // Iterate through swapping, calculating the blocks broken
            current.update();

            // Check for cleared or too many moves
            cout << "Cleared: " << current.getCleared() << "\n";
            if (current.getMoves() > 0)
            {
            cout << "Moves Left: " << 15 - current.getMoves() << "\n";
            }

            if (current.getCleared() >= 100)
            {
                cout << "Congrats! You win! You may continue playing or type start to start over!\n";
                current.setMoves(-999999);
            }

            if (current.getMoves() >= 15)
            {
                inGame = false;
                cout << "Game over! No moves left! Type start to try again!\n";
            }

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