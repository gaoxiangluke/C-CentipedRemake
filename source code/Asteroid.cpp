/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "Asteroid.h"
#include "collisioncheck.h"

//initial asteroid
Asteroid::Asteroid()
{
    lifeCounter = 0;
    APosX = 0;
    APosY = 60;
    collisionOther = false;
    existence = false;
    asteroidBox.w = asteroid_WIDTH;
    asteroidBox.h = asteroid_HEIGHT;
}

//set position of asteroid
void Asteroid::setPos(GridFactory& gridMushroom)
{
    int numx;
    int numy;
    numx = rand() % (17 - 1 + 1) + 1;
    numy = rand() % (20 - 2 + 1) + 2;
    bool existence1 = true;
    //avoid generate same number;
    while (existence1 == true)
    {
        x = numx;
        y = numy;
        existence1 = gridMushroom.checkExistence(numx, numy);
        if(existence1 == false)
        {
            break;
        }
        numx = rand() % (17 - 1 + 1) + 1;
        numy = rand() % (21 - 2 + 1) + 2;
    }
    //set position of Asteroid
    gridMushroom.getGrid(APosX, APosY, x, y);
    //change grid to used
    gridMushroom.setGrid(x, y, true);
    asteroidBox.x = APosX;
    asteroidBox.y = APosY;

}

//render asteroid
void Asteroid::render()
{

    if(existence == true)
    {
        //render different picture and check the remaining life of asteroid
        if (lifeCounter == 4)
        {
            asteroid1.render(APosX, APosY);
        }
        else if (lifeCounter == 3)
        {
            asteroid2.render(APosX, APosY);
        }
        else if (lifeCounter == 2)
        {
            asteroid3.render(APosX, APosY);
        }
        else if (lifeCounter == 1)
        {
            asteroid4.render(APosX, APosY);
        }
    }
}

//initialize all asteroid
AsteroidFactory::AsteroidFactory()
{
    for (int i = 0; i < 35; i++)
    {
        asteroids[i].existence = true;
        asteroids[i].lifeCounter = 4;
    }
}

//render all
void AsteroidFactory::renderAll()
{
    for (int i = 0; i < 100; i++)
    {
        asteroids[i].render();
    }
}
//set Position
void AsteroidFactory::setPosAll(GridFactory& gridMushroom)
{

    for (int i = 0; i < 35; i++)
    {
        asteroids[i].lifeCounter = 4;
        asteroids[i].existence = true;
        asteroids[i].setPos(gridMushroom);
    }


}
void AsteroidFactory::createAsteroid(int x,int y,GridFactory& gridMushroom)
{

    int xGridNum = x / 30;
    int yGridNum = y / 30;
    bool already = false;
    for (int i=0; i<100; i++)
    {

        if (asteroids[i].existence == false && already == false)
        {
            asteroids[i].existence = true;
            //mark the asteroid as used
            asteroids[i].lifeCounter = 4;
            gridMushroom.getGrid(asteroids[i].APosX, asteroids[i].APosY, xGridNum, yGridNum);
            asteroids[i].asteroidBox.x = asteroids[i].APosX;
            asteroids[i].asteroidBox.y = asteroids[i].APosY;
            gridMushroom.setGrid(xGridNum, yGridNum, 1);

            break;
        }
    }
}

//check the  number of asteroid in the player area
bool AsteroidFactory::checkAsteroid(int levelNum)
{
    bool createStarD;
    int numAsteroid = 0;
    for (int i = 0; i < 100; i++)
    {
        if(asteroids[i].existence == true)
        {
            if(asteroids[i].APosY >= 480)
            {
                numAsteroid++;
            }
        }
    }

    if(numAsteroid <= 4 + levelNum / 2)
    {
        createStarD = true;
    }
    else
    {
        createStarD = false;
    }


    return createStarD;
}
