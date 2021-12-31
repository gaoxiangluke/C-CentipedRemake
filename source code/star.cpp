/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "star.h"

//constructor for star destroyer class
Star::Star()
{
    sPosX = -30;
    sPosY = -30;
    sVelY = 4;
    starBox.x = sPosX;
    starBox.y = sPosY;
    starBox.w = Star_Width;
    starBox.h = Star_Height;
    existence = false;
}
//render star destroyer
void Star::render()
{
    if(existence == true)
    {
        starDestroyer.render(sPosX, sPosY);
    }
}
//check if the Star destroyer need to spawn
void Star::setStar(bool spawnStar, GridFactory gridMushroom)
{
    if (spawnStar == true && existence == false)
    {
        bool existence1 = true;
        int numx;
        int numy;
        int x;
        int y;
        numx = rand() % (17 - 3 + 1) + 3;
        numy = rand() % (16 - 8 + 1) + 8;
        //avoid generating same number;
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
            numy = rand() % (15 - 4 + 1) + 4;
        }
        //set position of star destroyer
        gridMushroom.getGrid(sPosX, sPosY, x, y);
        starBox.x = sPosX;
        starBox.y = sPosY;
        existence = true;
    }
}
//MOVE the star destroyer
void Star::moveStar(int height)
{
    if(existence == true)
    {
        sPosY += sVelY;
        starBox.x = sPosX;
        starBox.y = sPosY;
        if( sPosY + Star_Height > height)
        {
            existence = false;
        }
    }
}
