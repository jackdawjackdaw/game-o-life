game-o-life
===========

CCS 07.08.2014
(chris.colemansmith@gmail.com)

Exploring Conway's game of life, curses and maybe some real graphics. 

## Basic Rules [1]

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




## Requires:

* CMAKE [2]
* A C compiler
* The Gnu Scientific Library (GLS) [3]
* Ncurses [4]

## Building, Installing and Testing

This project uses CMAKE to generate Makefiles and run tests, it is canonical to do out of place builds using cmake. An "out of place" builds puts all the temporary files and compiler junk into a directory that is outside the source tree.

From the project root do:

    mkdir ./build
    cd ./build
    cmake ..
    make && make install

Cmake defaults to installing things in /usr/local, if you don't want that you should set invoke cmake as

    cmake -DCMAKE_INSTALL_PREFIX:PATH=/your/install/path ..

Check backed unit tests can also be built by enabling the `BUILD_TESTING` cmake option, from the build directory 

    cmake -DBUILD_TESTING=on ..

The tests can be run from the `make test` target or by directly invoking `ctest` .


## Todo

1. Tests!
2. Make game board size dynamic
3. Separate the game logic and lifecycle from the main loop of the program
4. Use curses for drawing a viewport into the game world that fills the terminal (http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/)
5. Allow some user navigation and interaction with the world
6. Try smooth life: http://arxiv.org/abs/1111.1567

[1]: http://en.wikipedia.org/wiki/Conway's_Game_of_Life
[2]: http://www.cmake.org/
[3]: http://www.gnu.org/software/gsl/
[4]: https://www.gnu.org/software/ncurses/
