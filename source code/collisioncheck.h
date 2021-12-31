/*
    Authors: Xiang Gao, Justin Lui, Mackensi Holt
    Program Title: Centipede: Star Wars Edition
    Program Descrption: Plays Centipede.
    Date Created: 4/18/2017
    Due Date: 5/1/2017
    Date Last Modified: 4/30/2017
*/

#ifndef COLLISIONCHECK_H_INCLUDED
#define COLLISIONCHECK_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

bool CollisionChecker( SDL_Rect a, SDL_Rect b );

#endif // COLLISIONCHECK_H_INCLUDED
