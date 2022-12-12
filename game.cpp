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
    moves = 0;
}

game::game(string filePath)
{
    ifstream fin(filePath);
    fin >> cleared >> moves;
    grid = randomBoard();

    for(int i = 0; i < (int) grid.size(); i++) 
    {
        for(int j = 0; j < (int) grid[i].size(); j++) {
            int cur; 
            fin >> cur;
            grid[i][j] = static_cast<Candy>(cur);
        }
    }
}

void game::save(string filePath)
{
    ofstream fout(filePath);    
    fout << cleared << " " << moves << endl;
    for(int i = 0; i < (int) grid.size(); i++) 
    {
        for(int j = 0; j < (int) grid[i].size(); j++) {
            Candy cur = grid[i][j];
            fout << static_cast<int>(cur) << " ";
        }
        fout << endl;
    }
}

Candy game::get(int i, int j)
{
    return grid[i][j];
}

int game::getCleared()
{
    return cleared;
}

int game::getMoves()
{
    return moves;
}

void game::setMoves(int m)
{
    moves = m;
}

void game::update()
{
    cout << *this;
    // while(game::remove())
    // {
    //     cout << this;
    //     game::fall();
    //     cout << this;
    // }
}

// Remove function to remove all 3s/4s/5s, leaving a special candy or empty space.
// Returns false if nothing to remove.
bool game::remove() {
    cout << "yayy!!";
    return false;
}

// Fall function generates new candies and causes ones to fall if space below is EMPTY
void game::fall()
{
    for (int j = 0; j < (int) grid[j].size(); ++j)
    {
        for (int i = (int) grid.size() - 1; i >= 0; --i)
        {
            int x = i;
            while (x != (int) grid.size() - 1 && grid[x + 1][j] == EMPTY)
            {
                game::swap(x, j, x + 1, j);
                ++x;
            }
        }

        int k {0};
        while (grid[k][j] == EMPTY)
        {
            grid[k][j] = randomCandy();
            ++k;
        }
    }
}

void game::swap(int x1, int y1, int x2, int y2)
{
    int temp1 {y1};
    int temp2 {y2};
    y1 = x1 - 1;
    x1 = temp1 - 1;
    y2 = x2 - 1;
    x2 = temp2 - 1;
    if (grid[x1][y1] == grid[x2][y2]) return;
    if (x1 != x2 && y1 != y2) return;
    if ((x1 == x2 && abs(y1 - y2) == 1) || (y1 == y2 && abs(x1 - x2) == 1)) {
        Candy temp = grid[x1][y1];
        grid[x1][y1] = grid[x2][y2];
        grid[x2][y2] = temp;
    }
}

bool game::check3()
{
    int lastCount = 1;
    // Horizontal Checks
    for (int i = 0; i < (int) grid.size(); ++i)
    {
        lastCount = 1;
        for (int j = 1; j < (int) grid[0].size(); ++j)
        {
            if (grid[i][j] == grid[i][j-1]) ++lastCount;
            else lastCount = 1;
            if (lastCount >= 3) return true;
        }
    }

    // Vertical Checks
    for (int j = 0; j < (int) grid[0].size(); ++j)
    {
        lastCount = 1;
        for (int i = 1; i < (int) grid.size(); ++i)
        {
            if (grid[i][j] == grid[i-1][j]) ++lastCount;
            else lastCount = 1;
            if (lastCount >= 3) return true;
        }
    }

    return false;
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
    os << "Moves Taken: " << g.moves << endl << "Candies Cleared: " << g.cleared << endl;
    return os;
}