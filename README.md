# CandyCrush

## Proposal

Write a short proposal (<500 words) describing your project. In particular, describe any libraries or frameworks you plan to use. Talk about what features of C++ you expect to use, and how you plan to structure your project (Does it have a class hierarchy? Is it a series of class templates?). 

We plan to develop a terminal board game [CandyCrush](https://www.king.com/game/candycrush). We do not plan to use external libraries since the standard library will suffice. We plan to use functionality such as `stringstream` for user commands and saving function, a simple class hierarchy for storing different types of candies, standard library algorithms for generating random numbers, smart pointers to store the game board, etc.

| Lucas                                         | David                                       |
| --------------------------------------------- | ------------------------------------------- |
| swap command (update the board) 2 hours       | board initialization (start command) 1 hour |
| setting up game for different candies 2 hours | random number generator 1 hour              |
|                                               | I/O to save the game 1 hour                 |



## Functionality

[Reference](https://techboomers.com/t/how-to-play-candy-crush-saga)

1. In doing so, you usually must create a line of at least 3 candies of the same colour (but there are exceptions; see below).  This will eliminate those candies from the board, and they will be filled in by the candies above them (or by random candies from the top of the board).
2. 4 candies of the same color in a line: you will get a **Striped Candy**; whether its stripes are horizontal or vertical depends on the direction that you swapped candies in order to make the line.  Then, if you match a Striped Candy with at least 2 other candies of the same colour, it will eliminate all candies in its current row (if it has horizontal stripes) or column (if it has vertical stripes).
3. If you manage to match 5 candies of the same colour in the shape of an “L” or “T”, like so……you will create a Wrapped Candy.  If you match a Wrapped Candy with at least 2 other candies of the same colour, it will explode twice in succession, eliminating all candies directly adjacent to it (including diagonally).
4. If you manage to match 5 candies of the same colour in a line……you will create a Colour Bomb Candy.  When you swap a Colour Bomb Candy with a regular candy, it will eliminate all candies on the board of that colour.  So, in the example below, all green candies would be eliminated from the board.
5. If you swap two special candies with each other, you can create even greater effects!  So, in the example below, if you combine a Wrapped Candy with a Striped Candy, you will create a giant candy that will eliminate 3 columns and 3 rows of candies!
6. If a swapping doesn't make a row of >= 3 candies, the program does nothing.

