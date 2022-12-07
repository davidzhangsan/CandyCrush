#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

class game
{
private:
    std::vector<vector<int>> grid;
public:
    game();
    game(std::string);
    int get(int, int);
    friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif