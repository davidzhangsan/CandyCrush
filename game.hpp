#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>

class game
{
private:
    std::vector<std::vector<int>> grid;
public:
    enum candy
    {
        Empty,
        Blue,
        Green,
        Orange,
        Purple,
        Red,
        Yellow,
        HBlue,
        HGreen,
        HOrange,
        HPurple,
        HRed,
        HYellow,
        VBlue,
        VGreen,
        VOrange,
        VPurple,
        VRed,
        VYellow,
        WBlue,
        WGreen,
        WOrange,
        WPurple,
        WRed,
        WYellow,
        ColorBomb
    };
    game();
    game(std::string);
    int get(int, int);
    friend std::ostream & operator<<(std::ostream & os, const game & g);
};

#endif