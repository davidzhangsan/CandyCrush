#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

enum Candy
    {
        EMPTY = 0,
        BLUE = 1,
        GREEN = 2,
        ORANGE = 3,
        PURPLE = 4,
        RED = 5,
        YELLOW = 6,
        HBLUE = 11,
        HGREEN = 12,
        HORANGE = 13,
        HPURPLE = 14,
        HRED = 15,
        HYELLOW = 16,
        VBLUE = 21,
        VGREEN = 22,
        VORANGE = 23,
        VPURPLE = 24,
        VRED = 25,
        VYELLOW = 26,
        WBLUE = 31,
        WGREEN = 32,
        WORANGE = 33,
        WPURPLE = 34,
        WRED = 35,
        WYELLOW = 36,
        COLORBOMB = 40
    };

const int t[4][4][2] =  {
                            {{-2, -1}, {-2, 0}, {-2, 1}, {-1, 0}},
                            {{-2, 0}, {-1, 0}, {-1, 1}, {-1, 2}},
                            {{-2, 0}, {-1, 0}, {-1, -1}, {-1, -2}},
                            {{-2, -1}, {-1, -1}, {0, -1}, {0, -2}}
                        };

const int l[2][4][2] =  {    
                            {{0, -1}, {0, -2}, {-1, -2}, {-2, -2}},
                            {{0, -1}, {0, -2}, {-1, 0}, {-2, 0}}
                        };

class game
{
private:
    std::vector<std::vector<Candy>> grid;
    int cleared;
    int moves;
    
    bool remove();
    void fall();

public:
    game();
    game(std::string);
    void save(std::string);
    Candy get(int, int);
    int getCleared();
    int getMoves();
    void setMoves(int);
    void update();
    void swap(int, int, int, int);
    std::pair<int, int> checkR(int);
    int checkHelp(int, int);
    std::pair<int, int> check5LT();
    friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif