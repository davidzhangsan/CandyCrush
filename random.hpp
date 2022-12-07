#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <memory>
#include <vector>

// returns null if height <= width * height - 1
std::vector<std::vector<int> > randomBoard(int, int, int numFrosting);

int randomCandy();

#endif