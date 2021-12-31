#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include "Bullet.h"
#include "textureSet.h"
#include "Xwing.h"
#include "segment.h"
#include "text.h"
#include "Asteroid.h"
#include "star.h"
#include "fett.h"

extern textureSet gBulletTexture;
extern textureSet gDotTexture;
extern SDL_tools backgroundMusic;
extern SDL_tools explosion;
extern SDL_tools force;
extern SDL_tools death;

class Object
{
private:
    Xwing xwing;
    BulletFactory bullet;
    Centipede centipede1;
    Text screenText;
    GridFactory gridSystem;
    AsteroidFactory asteroidAll;
    Star star;
    Fett fett;
    int gameStep;
    //indicate the level number
    int levelNum;
    int point;
public:
    Object();
    //handle event
    void objectEvent(SDL_Event& e);
    void objectMovement(int h,int w);
    void objectRendering();
    //asteroid & centipede
    void acsecollision();
    //xwing & asteroid
    void xacollision();
    //bullet & asteroid
    void bacollision();
    //xwing & centipede
    void xccollision();
    //bullet & centipede
    void bccollision();
    //grid & star destroyer
    void gscollision();
    //star destroyer & xwing
    void sxcollision();
    //bullet and star destroyer
    void bscollision();
    //boba fett & xwing
    void fxcollision();
    //boba fett & asteroid
    void facollision();
    //boba fett & bullet
    void fbcollision();
    void setLevel();
    int counter;

    void setup();
    //control boba fett direction
    int changeForFett;
    //control boba fett respawn
    int fettCount;
    //respawn boba fett
    void fettCreate();
    //play music
    void musicPlayer();
    //counter for increasing player's life
    int lifeIncrease;
    //string for checking special code
    string specialCode;
    //check special code
    int checkSpecialCode();
    //check if activate power mode
    bool powerMode;
    //check if activate night mare mode
    bool nightmare;
    //check if the special message applied
    bool specialMessage;

};

#endif // OBJECT_H_INCLUDED
