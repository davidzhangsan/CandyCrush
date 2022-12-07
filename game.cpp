#include "game.hpp"
#include "random.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

game::game()
{    
    // Implement random board construtor.
    grid = randomBoard();
    cleared = 0;
}

game::game(string filePath)
{
    ifstream fin(filePath);

    
}

void save(string filePath)
{
    ofstream fout(filePath);    
}

Candy game::get(int i, int j)
{
    return grid[i][j];
}

int game::getCleared()
{
    return cleared;
}

ostream & operator<<(ostream & os, const game & g)
{
    os << setw(3) << " " << setw(3) << " "; // Leave a space for the column of y coordinate labels and the border
    for (int i {1}; i <= 9; ++i)
    {
        os << setw(3) << i;
    }
    os << "\n";

    // Print top border
    os << setw(3) << " " << setw(3) << " "; // Leave a space for the column of y coordinate labels and the border
    for (int i {1}; i <= 9; ++i)
    {
        os << setw(3) << "_";
    }
    os << "\n";

    // Print each row
    for (int i {1}; i <= 9; ++i)
    {
        // Print y coordinate
        os << setw(3) << i;

        // Print border
        os << setw(3) << "|";

        // Print either a candy or an empty space
        for (int j {0}; j < 9; ++j) {
            // If else logic for the candy printing
            // switch(g.grid[i][j])
            // {
            //     case game::Candy::EMPTY: 
            // }
        }
    }
    return os; //just to compile
}