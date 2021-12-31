/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "grid.h"

//set up grid system
Grid::Grid()
{
    used = false;
    grid_width = 30;
    grid_height = 30;
    gridBox.w = 30;
    gridBox.h = 30;
    gridBox.x = 30;
    gridBox.y = 30;
}
GridFactory::GridFactory()
{
    int x;
    int y;

    for (int i = 0; i < 24; i++)
    {
        for (int k = 0; k < 21; k++)
        {
            y = i * 30;
            x = k * 30;
            grids[i][k].gPosX = x;
            grids[i][k].gPosY = y;
            grids[i][k].gridBox.x = grids[i][k].gPosX;
            grids[i][k].gridBox.y = grids[i][k].gPosY;
        }
    }
}

//check if the point is empty
bool GridFactory::checkExistence(int gridNumX, int gridNumY)
{
    bool existence;
    if(grids[gridNumY][gridNumX].used == false)
    {
        existence = false;
    }
    else
    {
        existence = true;
    }
    return existence;
}

//set the existence of grid
void GridFactory::setGrid(int gridNumX, int gridNumY, int num)
{
    if(num == 1)
    {
        grids[gridNumY][gridNumX].used = true;
    }
    else if (num == 0)
    {
        grids[gridNumY][gridNumX].used = false;
    }
}

//get the grid coordinate
void GridFactory::getGrid(int& x, int&y, int gridNumX, int gridNumY)
{
    x = grids[gridNumY][gridNumX].gPosX;
    y = grids[gridNumY][gridNumX].gPosY;
}

//reset everything
void GridFactory::reset()
{
    int x;
    int y;

    for (int i = 0; i < 24; i++)
    {
        for (int k = 0; k < 21; k++)
        {
            y = i * 30;
            x = k * 30;
            grids[i][k].gPosX = x;
            grids[i][k].gPosY = y;
            grids[i][k].gridBox.x = grids[i][k].gPosX;
            grids[i][k].gridBox.y = grids[i][k].gPosY;
            grids[i][k].used = false;
        }
    }
}
