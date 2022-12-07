#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

class game
{
private:
    std::unique_ptr<std::unique_ptr<int []> []> grid;
public:
    game();
    game(std::string);
    friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif