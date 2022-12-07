#include "game.hpp"
#include "random.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

game::game()
{
    // Implement random board construtor.
}

game::game(std::string filePath)
{
    // Implement constructor from file
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

        // Print either a candy, an empty space, or a frosted piece
        for (int j {1}; j <= 9; ++j) {

        }
    }
}