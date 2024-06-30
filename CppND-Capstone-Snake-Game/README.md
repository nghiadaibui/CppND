# CPPND: Capstone Snake Game

This is a Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Change note
1. Use the "Resource Acquisition Is Initialization" (RAII) approach for managing resource lifetimes.The SDL context, window, and renderer be encapsulated in `SDLContext` object, with initialization done in the constructor, and cleanup in the destructor.

2. Split up the Game class because there's no reason for the Game class to know anything about SDL

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Game Instructions

There are now two new types of food available: one makes the snake run faster and the other makes it die.

## Rubric points met
### Loops, Functions, I/O 
(2/4)
  - The project demonstrates understanding of C++ function and control structures
  - The project uses data structures and immutable variables
### Object Oriented Programming
(3/6)
  - One or more classes are add to the project with appropriate access specifier for class member `food.h`
  - Class constructor utilize member initialization lists `food.h`
  - Overloaded functions allow the same function to operate on different parameters `renderer.h:40`
### Memory Management
  - The project makes use of references in function declarations `renderer.h:40`
  - The project uses RAII
### Concurrency
  - The project uses future and async task `game.cpp:10`
  - The project uses mutex `game.cpp:38`