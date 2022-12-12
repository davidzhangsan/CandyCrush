#include "game.hpp"
#include "random.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>

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

    for(int i = 0; i < 9; i++) 
    {
        for(int j = 0; j < 9; j++) {
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
    for(int i = 0; i < 9; i++) 
    {
        for(int j = 0; j < 9; j++) {
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
    ++moves;
    cout << *this;
    while(!stuck())
    {
        // cerr << "in update" << endl;
        remove();
        // cerr << "after remove" << endl;
        cout << *this;
        usleep(900000);
        fall();
        cout << *this;
        usleep(900000);
    }
}

// Remove function to remove a 3s/4s/5s, leaving a special candy or empty space.
// Returns false if nothing to remove.

// Need to keep track of move and cleared.
void game::remove() {
    if (!checkR(5)) {
        if (!check5LT()) {
            if (!checkR(4)) {
                checkR(3);
            }
        }
    }
}

void game::eraseHelper(int i1, int j1) {
    Candy cur = grid[i1][j1];
    if (grid[i1][j1] == EMPTY) return;
    ++cleared;
    if (cur == COLORBOMB) {
        return;
    }
    else if (cur > 30)
    {
        for (int i {-1}; i <= 1; ++i) {
            for (int j {-1}; j <= 1; ++j)
            {
                if (inBounds(i + i1, j + j1) && !(i==0 && j==0)) eraseHelper(i + i1, j + j1);
                // cerr << "erase wrapped candy" << endl;
            }
        }
    } else if (cur > 20)
    {
        for (int i {0}; i < 9; ++i)
        {
            if (i != i1) eraseHelper(i, j1);
        }
    } else if (cur > 10)
    {
        for (int j {0}; j < 9; ++j)
        {
            if (j != j1) eraseHelper(i1, j);
        }
    }
    grid[i1][j1] = EMPTY;
}

inline bool game::inBounds(int i, int j) {
    return (i >= 0) && (i < 9) && (j >= 0) && (j < 9);
}

// Fall function generates new candies and causes ones to fall if space below is EMPTY
void game::fall()
{
    for (int j = 0; j < 9; ++j)
    {
        for (int i = 8; i >= 0; --i)
        {
            int x = i;
            while (x != 8 && grid[x + 1][j] == EMPTY)
            {
                grid[x + 1][j] = grid[x][j];
                grid[x][j] = EMPTY;
                ++x;
            }
        }

        int k {0};
        while (k < 9 && grid[k][j] == EMPTY)
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


//return true if candies can be eliminated
bool game::stuck() {
    int lastCount = 1;
    // Horizontal Checks
    for (int i = 0; i < 9; ++i)
    {
        lastCount = 1;
        for (int j = 1; j < 9; ++j)
        {
            if ((grid[i][j] % 10 == grid[i][j-1] % 10)) ++lastCount;
            else lastCount = 1;
            if (lastCount >= 3) {
                return false;
            }
        }
    }

    // Vertical Checks
    for (int j = 0; j < 9; ++j)
    {
        lastCount = 1;
        for (int i = 1; i < 9; ++i)
        {
            if ((grid[i][j] % 10 == grid[i-1][j] % 10)) ++lastCount;
            else lastCount = 1;
            if (lastCount >= 3) {
                return false;
            }
        }
    }

    return true;
}

bool game::checkR(int num)
{
    // check 3, 4, or 5 in a row
    // update the grid
    // return the position for the empty space/new candy

    int lastCount = 1;
    // Horizontal Checks
    for (int i = 0; i < 9; ++i)
    {
        lastCount = 1;
        for (int j = 1; j < 9; ++j)
        {
            if (grid[i][j] % 10 == grid[i][j-1] % 10) ++lastCount;
            else lastCount = 1;
            if (lastCount >= num) {
                switch(num) {
                    case 3 : eraseHelper(i, j);
                    break;
                    case 4 : grid[i][j] = static_cast<Candy>(static_cast<int>(grid[i][j]) + 10);
                    ++cleared;
                    break;
                    case 5 : grid[i][j] = COLORBOMB;
                    ++cleared;
                    break;
                }
                for(int k = 1; k < num; k++) {
                    eraseHelper(i, --j);
                }
                return true;
            }
        }
    }

    // Vertical Checks
    for (int j = 0; j < 9; ++j)
    {
        lastCount = 1;
        for (int i = 1; i < 9; ++i)
        {
            if (grid[i][j] % 10 == grid[i-1][j] % 10) ++lastCount;
            else lastCount = 1;
            if (lastCount >= num) {
                switch(num) {
                    case 3 : eraseHelper(i, j);
                    break;
                    case 4 : grid[i][j] = static_cast<Candy>(static_cast<int>(grid[i][j]) + 20);
                    ++cleared;
                    break;
                    case 5 : grid[i][j] = COLORBOMB;
                    ++cleared;
                    break;
                }
                for(int k = 1; k < num; k++) {
                    eraseHelper(--i, j);
                }
                return true;
            }
        }
    }

    return false;
}

inline bool game::checkHelp(int i1, int j1) {
    /*
        two basic shapes:

        ***  *      *    *
         *   ***  ***    *
         *   *      *   ***

        *      *
        *      * 
        ***  ***

        The candy/empty space is at the rightmost of the bottom row.
    */

    int cur = static_cast<int>(grid[i1][j1]);
    for(int i = 0; i < 4; i++) 
    {
        int cnt = 0;
        for(int j = 0; j < 4; j++)
        {
            int I = i1 + t[i][j][0], J = j1 + t[i][j][1];
            if(inBounds(I, J) && static_cast<int>(grid[I][J]) == cur) {
                cnt++;
            }
        }
        if(cnt == 4) {  
            for(int j = 0; j < 4; j++)
            {
                int I = i1 + t[i][j][0], J = j1 + t[i][j][1];
                eraseHelper(I, J);
            }
            grid[i1][j1] = static_cast<Candy>(static_cast<int>(grid[i1][j1]) + 30);
            return true;
        }
    }

    for(int i = 0; i < 2; i++) 
    {
        int cnt = 0;
        for(int j = 0; j < 4; j++)
        {
            int I = i1 + l[i][j][0], J = j1 + l[i][j][1];
            if(inBounds(I, J) && static_cast<int>(grid[I][J]) == cur) {
                cnt++;
            }
        }
        if(cnt == 4) {
            for(int j = 0; j < 4; j++)
            {
                int I = i1 + l[i][j][0], J = j1 + l[i][j][1];
                eraseHelper(I, J);
            }
            grid[i1][j1] = static_cast<Candy>(static_cast<int>(grid[i1][j1]) + 30);
            return true;
        }
    }

    return false; //not found
}

bool game::check5LT()
{
    for (int i = 1; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++)
        {
            if(checkHelp(i, j)) {
                ++cleared;
                return true;
            }
        }
    }
    return false;
}

void game::colorBomb(int x1, int y1, int x2, int y2)
{
    Candy c1 = grid[y1 - 1][x1 - 1];
    Candy c2 = grid[y2 - 1][x2 - 1];
    Candy toRemove;
    if (c1 == COLORBOMB) {
        grid[y1 - 1][x1 - 1] = EMPTY;
        toRemove = c2;
    }
    if (c2 == COLORBOMB) {
        grid[y2 - 1][x2 - 1] = EMPTY;
        toRemove = c1;
    }
    for (int i {0}; i < 9; ++i)
    {
        for (int j {0}; j < 9; ++j)
        {
            if (grid[i][j] == toRemove % 10) eraseHelper(i, j);
        }
    }

    fall();
    update();
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
    return os;
}