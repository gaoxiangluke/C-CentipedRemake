/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#include "textureSet.h"
#include "Xwing.h"
#include "object.h"
#include "segment.h"
#include "collisioncheck.h"

//initial object
Object::Object()
{
    gameStep = 1;
    asteroidAll.setPosAll(gridSystem);
    levelNum = 1 ;
    point = 0;
    counter = 0;
    changeForFett = 0;
    fettCount = 0;
    lifeIncrease = 1;
    specialCode = "0";
    powerMode = false;
    nightmare = false;
    specialMessage = false;
}
void Object::objectEvent(SDL_Event& e)
{
    if(gameStep == 2)
    {
        xwing.handleEvent(e);
        bullet.handleEvent(e);
    }
    screenText.handleEvent(e, gameStep, specialCode, specialMessage);
}
//movement for all object in game
void Object::objectMovement(int h, int w)
{
    screenText.changePosition(gameStep);
    //control bullet shooting speed
    if (gameStep == 2)
    {
        specialCode = "0";
        star.setStar(asteroidAll.checkAsteroid(levelNum), gridSystem);
        setLevel();
        fettCreate();
        //set all collision
        bccollision();
        acsecollision();
        bacollision();
        xacollision();
        xccollision();
        sxcollision();
        gscollision();
        bscollision();
        fbcollision();
        fxcollision();
        facollision();
        //set up centipede speed
        centipede1.velocityCheck();
        //Move the everything
        bullet.bulletControl(xwing);
        xwing.move(h, w);
        bullet.moveBullet(h);
        centipede1.moveAll(h, w);
        star.moveStar(h);
        fett.move();
        //change direction of boba fett
        if(fett.existence == true)
        {
            if(changeForFett % 120 == 0)
            {
                fett.changeDirection();
            }
            changeForFett++;
        }
    }
}

//rendering for all object in game
void Object::objectRendering()
{
    if (gameStep == 2)
    {
        xwing.render();
        bullet.bulletRendering();
        centipede1.renderAll();
        asteroidAll.renderAll();
        star.render();
        fett.render();
        screenText.setInfo(xwing.lifeCount, levelNum, point);
    }
    screenText.renderText(gameStep);
}

//check collision between asteroid and centipede
void Object::acsecollision()
{
    for (int i = 0; i < 12; i++)
    {
        for (int k = 0; k < 100; k++)
        {
            if(CollisionChecker(asteroidAll.asteroids[k].asteroidBox, centipede1.parts[i].segmentBox))
            {
                if(asteroidAll.asteroids[k].existence == true && centipede1.parts[i].IsCreated == true)
                {
                    centipede1.parts[i].collsiona = true;
                    break;
                }
            }
            else
            {
                centipede1.parts[i].collsiona = false;

            }
        }
    }
}

//check collision between x-wing and asteroid
void Object::xacollision()
{
    for (int k = 0; k < 100; k++)
    {
        if(CollisionChecker(asteroidAll.asteroids[k].asteroidBox, xwing.xwingCollider))
        {
            if(asteroidAll.asteroids[k].existence == true)
            {
                xwing.xacollison = true;

                break;
            }
            else
            {
                xwing.xacollison = false;

            }
        }
        else
        {
            xwing.xacollison = false;
        }
    }
}

//check collision between bullets and asteroid
void Object::bacollision()
{
    for (int i = 0; i < 100; i++)
    {
        for (int k = 0; k < 100; k++)
        {

            if(CollisionChecker(asteroidAll.asteroids[k].asteroidBox, bullet.bullets[i].bulletBox))
            {

                if((asteroidAll.asteroids[k].existence == true && asteroidAll.asteroids[k].lifeCounter > 0) && bullet.bullets[i].bExistence == true)
                {

                    //bullet.bullets[i].collision = true;
                    bullet.bullets[i].bExistence = false;
                    bullet.bullets[i].bPosY -= bullet.bullets[i].bVelY;
                    bullet.bullets[i].bVelY += 5;
                    //check if special code applied

                    if(powerMode)
                    {
                        asteroidAll.asteroids[k].lifeCounter = 0;
                    }
                    else
                    {
                        asteroidAll.asteroids[k].lifeCounter--;
                    }

                    point = point + 5;
                    if(asteroidAll.asteroids[k].lifeCounter == 0)
                    {
                        asteroidAll.asteroids[k].existence = false;
                        gridSystem.setGrid(asteroidAll.asteroids[k].APosX / 30, asteroidAll.asteroids[k].APosY / 30, 0);

                    }
                }
            }
        }
    }
}

//check xwing and centipede collision
void Object::xccollision()
{
    for (int i = 0; i < 12; i++)
    {
        if(centipede1.parts[i].IsCreated == true)
        {
            if (CollisionChecker(centipede1.parts[i].segmentBox, xwing.xwingCollider))
            {
                centipede1.reset(levelNum);
                fett.resetFett();
                changeForFett = 0;
                xwing.lifeCount--;
                death.playSound("assets/death.wav");
                if(xwing.lifeCount == 0)
                {
                    gameStep = 3;
                }

                break;
            }
        }
    }
}

//check collision between centipede and bullet
void Object::bccollision()
{

    for (int i = 0; i < 12; i++)
    {
        for (int k = 0; k < 100; k++)
        {

            if(CollisionChecker(centipede1.parts[i].segmentBox, bullet.bullets[k].bulletBox))
            {

                if(centipede1.parts[i].IsCreated == true && bullet.bullets[k].bExistence == true && centipede1.parts[i].sPosY != 30)
                {
                    asteroidAll.createAsteroid(centipede1.parts[i].sPosX, centipede1.parts[i].sPosY, gridSystem);
                    gridSystem.setGrid(centipede1.parts[i].sPosX / 30, centipede1.parts[i].sPosY / 30, 1);
                    //bullet.bullets[k].collision=true;
                    bullet.bullets[k].bExistence = false;
                    bullet.bullets[k].bPosY -= bullet.bullets[i].bVelY;
                    bullet.bullets[k].bVelY += 5;
                    centipede1.parts[i].IsCreated = false;
                    centipede1.parts[i].bccollision = true;
                    centipede1.collisionbc(i);
                    explosion.playSound("assets/explosion.wav");

                    point = point + 50;
                }
                else
                {
                    centipede1.parts[k].bccollision = false;
                }
            }
            else
            {
                centipede1.parts[k].bccollision = false;
            }
        }
    }
}

//set collision between star destroyer and grid system
void Object::gscollision()
{
    int x;
    for (int i = 0; i < 22; i++)
    {
        for (int k = 0; k < 21; k++)
        {
            if(CollisionChecker(gridSystem.grids[i][k].gridBox, star.starBox))
            {
                if (gridSystem.grids[i][k].used == false && star.existence == true)
                {
                    counter++;
                    if(counter == 8)
                    {
                        x = rand() % (3 - 0 + 1) + 0;
                        counter = 0;
                        //create asteroid is true
                        if(x == 1)
                        {
                            asteroidAll.createAsteroid(star.sPosX, star.sPosY, gridSystem);
                            gridSystem.setGrid(star.sPosX / 30, star.sPosY / 30, 1);
                        }
                        break;
                    }
                }
            }
        }
    }
}
//set collision between xwing and star destroyer
void Object::sxcollision()
{
    if(xwing.lifeCount != 0 && star.existence == true)
    {
        if(CollisionChecker(xwing.xwingCollider, star.starBox))
        {

            star.existence = false;
            xwing.lifeCount--;
            centipede1.reset(levelNum);
            death.playSound("assets/death.wav");
            if(xwing.lifeCount == 0)
            {
                gameStep = 3;
            }
        }
    }
}

//set collision between bullet and star destroyer
void Object::bscollision()
{
    for (int i = 0; i < 100; i++)
    {
        if(CollisionChecker(bullet.bullets[i].bulletBox,star.starBox))
        {
            if(star.existence == true && bullet.bullets[i].bExistence == true)
            {
                explosion.playSound("assets/explosion.wav");
                bullet.bullets[i].bExistence = false;
                star.existence = false;
                //bullet.bullets[i].collision=true;
                bullet.bullets[i].bPosY -= bullet.bullets[i].bVelY;
                bullet.bullets[i].bVelY += 5;
                point += 100;
                break;
            }
        }
    }
}

//set collision between fett and xwing
void Object::fxcollision()
{
    if(fett.existence == true)
    {
        if(CollisionChecker(fett.fettBox, xwing.xwingCollider))
        {
            fett.existence = false;
            xwing.lifeCount--;
            death.playSound("assets/death.wav");
            centipede1.reset(levelNum);
            changeForFett = 0;

            if(xwing.lifeCount == 0)
            {
                gameStep = 3;
            }
        }
    }
}

//set collision between fett and asteroid
void Object::facollision()
{
    for(int i = 0; i < 100; i++)
    {
        if(fett.existence == true && asteroidAll.asteroids[i].existence == true)
        {
            if(CollisionChecker(fett.fettBox, asteroidAll.asteroids[i].asteroidBox))
            {
                asteroidAll.asteroids[i].lifeCounter = 0;
                if(asteroidAll.asteroids[i].lifeCounter == 0)
                {
                    asteroidAll.asteroids[i].existence = false;
                    gridSystem.setGrid(asteroidAll.asteroids[i].APosX / 30, asteroidAll.asteroids[i].APosY / 30, 0);
                    break;
                }
            }
        }
    }
}

void Object::fbcollision()
{
    for(int i = 0; i < 100; i++)
    {
        if(fett.existence == true && bullet.bullets[i].bExistence == true)
        {
            if(CollisionChecker(fett.fettBox, bullet.bullets[i].bulletBox))
            {
                fett.existence = false;
                bullet.bullets[i].bExistence = false;
                bullet.bullets[i].bPosY -= bullet.bullets[i].bVelY;
                bullet.bullets[i].bVelY += 5;
                point += 300;
                break;
            }
        }
    }
}

//increase level number after defeat all centipede segment
void Object::setLevel()
{
    bool levelplus = true;
    for(int i = 0; i < 12; i++)
    {
        if(centipede1.parts[i].IsCreated == true)
        {
            levelplus = false;
        }
    }
    if(levelplus == true)
    {
        levelNum++;
        centipede1.reset(levelNum);

    }
    if(levelNum == 13)
    {
        gameStep == 4;
        specialMessage = true;
    }
    if(nightmare == true)
    {
        if(point > lifeIncrease * 2000)
        {
            xwing.lifeCount++;
            lifeIncrease++;
        }
    }
    else
    {
        if(point > lifeIncrease * 10000)
        {
            xwing.lifeCount++;
            lifeIncrease++;
        }
    }

}
void Object::setup()
{
    if(gameStep == 1)
    {
        levelNum = 1;
        gridSystem.reset();
        asteroidAll.setPosAll(gridSystem);
        xwing.reset();
        centipede1.reset(levelNum);
        point = 0;
        counter = 0;
        changeForFett = 0;
        fett.resetFett();
        lifeIncrease = 1;
        powerMode = false;
        nightmare = false;
        if(checkSpecialCode() == 1)
        {
            xwing.lifeCount = 30;
        }
        else if(checkSpecialCode() == 2)
        {
            xwing.lifeCount = 1;
        }

    }
}

void Object::fettCreate()
{
    if(fett.existence == false)
    {
        fettCount++;
        if(fettCount == 500)
        {
            fett.existence = true;
            fettCount = 0;
            fett.resetFett();
            changeForFett = 0;
        }
    }
}

void Object::musicPlayer()
{
    if(gameStep == 1)
    {
        backgroundMusic.playSound("assets/background.wav");

    }
    else
    {
        backgroundMusic.quitSound("assets/background.wav");

    }
}

int Object::checkSpecialCode()
{
    int codeActivate = 0;
    if(specialCode == "011223344abab")
    {
        codeActivate = 1;
    }
    else if (specialCode == "0pfia")
    {
        powerMode = true;
    }
    else if (specialCode == "0mfabwy")
    {
        bullet.loadChanger(5);
    }
    else if(specialCode == "0nma")
    {
        codeActivate = 2;
        nightmare = true;
    }
    return codeActivate;
}
