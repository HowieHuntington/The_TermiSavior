//
//  main.h
//  The_TermiSavior
//
//  Created by Robert Huntington on 12/2/17.
//  Copyright © 2017 Robert Huntington. All rights reserved.
//

#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>



const int totalBullets = 1000;

//Total num of spiders
int spiNum = 20;

int count = 0;
int frames = 0;

//for cycling through portal image
int bgFrame = 0;



typedef struct
{
    float x, y;
    float dx, dy;
    short life;
    char *name;
    int onLedge;
    
    int animFrame, facingLeft;
} Man;


typedef struct
{
    int x, y;
    int animFrame;
}Background;

typedef struct
{
    float x, y;
    float dx, dy;
    float health;
    int animFrame, facingLeft, facingUp;
    
} Sentar;

typedef struct
{
    float x, y;
    float slopeX, slopeY;
    float dx, dy;
    float health;
    int direction;
    int count;
    int animFrame;
    int visible;
    
} Spider;

typedef struct
{
    float x, y;
    
}Bullet;

typedef struct
{
    float x, y;
    int animFrame;
    
}MuzzleFlash;


typedef struct
{
    //Players
    Man man;
    Sentar sentar;
    Spider spider[20];
    Bullet bullet[totalBullets];
    Background background[4];
    MuzzleFlash muzzleFlash[2];
    
    //Images
    SDL_Texture *bulletFrame;
    SDL_Texture *manFrame[2];
    SDL_Texture *spiderFrame[3];
    SDL_Texture *backgroundFrame[4];
    SDL_Texture *sentarFrame[2];
    SDL_Texture *muzzleFrame[2];
    SDL_Texture *label;
    
    //fonts
    
    TTF_Font *font;
    
    Mix_Chunk *music, *gunshot, *hit;
    
    int time;
    int statusState;
    
    SDL_Renderer *renderer;
} GameState;


//void processAnimations(GameState *game);

//int processEvents(SDL_Window *window, GameState *game);

#endif /* main_h */
