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

void swap(int x1, int y1, int x2, int y2)
{
    
}

ostream & operator<<(ostream & os, const game & g)
{
    os << setw(3) << " " << setw(3) << " "; // Leave a space for the column of y coordinate labels and the border
    for (int i {1}; i <= 9; ++i)
    {
        os << setw(3) << i << " ";
    }
    os << "\n";

    // Print top border
    os << setw(3) << " " << setw(3) << " "; // Leave a space for the column of y coordinate labels and the border
    for (int i {1}; i <= 9; ++i)
    {
        os << setw(3) << "__" << " ";
    }
    os << "\n";

    // Print each row
    for (int i {0}; i < 9; ++i)
    {
        // Print y coordinate
        os << setw(3) << i+1;

        // Print border
        os << setw(3) << "|";

        // Print either a candy or an empty space
        for (int j {0}; j < 9; ++j) {
            // If else logic for the candy printing
            os << setw(3);
            switch(g.grid[i][j])
            {
                case Candy::EMPTY   : os << "  "; break;
                
                case Candy::BLUE    : os << "BB"; break;
                case Candy::GREEN   : os << "GG"; break;
                case Candy::ORANGE  : os << "OO"; break;
                case Candy::PURPLE  : os << "PP"; break;
                case Candy::RED     : os << "RR"; break;
                case Candy::YELLOW  : os << "YY"; break;
                
                case Candy::HBLUE   : os << "HB"; break;
                case Candy::HGREEN  : os << "HG"; break;
                case Candy::HORANGE : os << "HO"; break;
                case Candy::HPURPLE : os << "HP"; break;
                case Candy::HRED    : os << "HR"; break;
                case Candy::HYELLOW : os << "HY"; break;
                
                case Candy::VBLUE   : os << "VB"; break;
                case Candy::VGREEN  : os << "VG"; break;
                case Candy::VORANGE : os << "VO"; break;
                case Candy::VPURPLE : os << "VP"; break;
                case Candy::VRED    : os << "VR"; break;
                case Candy::VYELLOW : os << "VY"; break;

                case Candy::WBLUE   : os << "WB"; break;
                case Candy::WGREEN  : os << "WG"; break;
                case Candy::WORANGE : os << "WO"; break;
                case Candy::WPURPLE : os << "WP"; break;
                case Candy::WRED    : os << "WR"; break;
                case Candy::WYELLOW : os << "WY"; break;
                
                case Candy::COLORBOMB: os << "**";
            }
            os << " ";
        }
        os << endl;
    }
    return os; //just to compile
}