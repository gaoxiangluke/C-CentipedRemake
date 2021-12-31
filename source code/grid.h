/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "textureSet.h"

//class for grid system
class Grid
{
public:
    int gPosX;
    int gPosY;
    bool used;
    Grid();
    int grid_width;
    int grid_height;
    SDL_Rect gridBox;
};

class GridFactory
{
public:
    GridFactory();
    Grid grids[24][21];
    bool checkExistence(int gridNumX, int gridNumY);
    void setGrid(int gridNumX, int gridNumY, int num);
    void getGrid(int& x, int&y, int gridNum, int gridNumY);
    void reset();
};

#endif // GRID_H_INCLUDED
