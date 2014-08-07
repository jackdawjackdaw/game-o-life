## Game of Life

It's just the game of life, that's it

## Rules

Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or
diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overcrowding.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

To avoid decisions and branches in the counting loop, the rules can be rearranged from an egocentric approach
of the inner field regarding its neighbors to a scientific observers point: if the sum of all nine fields is
3, the inner field state for the next generation will be life (no matter of its previous contents); if the
all-field sum is 4, the inner field retains its current state and every other sum sets the inner field to
death.
