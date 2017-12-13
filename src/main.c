//
//  main.c
//  The_TermiSavior
//
//  Created by Robert Huntington on 11/17/17.
//  Copyright © 2017 Robert Huntington. All rights reserved.
//
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"





void initializeGame(GameState *game)
{
    
   
    
    SDL_Surface *surface = NULL;
    
    //Load images and create rendering textures from them
    surface = IMG_Load("jesusA.png");
    if(surface == NULL)
    {
        printf("Cannot find jesusA.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->manFrame[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("jesusB.png");
    if(surface == NULL)
    {
        printf("Cannot find jesusB.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->manFrame[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    game->man.x = 500;
    game->man.y = 300;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.facingLeft = 1;
    game->man.animFrame = 0;
    game->man.facingLeft = 1;
    
    
    //load bullet
   surface = IMG_Load("bullet.png");
    if(surface == NULL)
    {
        printf("Cannot find bullet.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->bulletFrame = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    //Load muzzle flash
    
    surface = IMG_Load("muzzle1.png");
    if(surface == NULL)
    {
        printf("Cannot find muzzle1.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->muzzleFrame[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("muzzle2.png");
    if(surface == NULL)
    {
        printf("Cannot find muzzle2.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->muzzleFrame[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);


    //Load Enemy
    

    //spider initialization
    surface = IMG_Load("spider.png");
    if(surface == NULL)
    {
        printf("Cannot find spider.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->spiderFrame[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("spiderb.png");
    if(surface == NULL)
    {
        printf("Cannot find spiderb.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->spiderFrame[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("spiderc.png");
    if(surface == NULL)
    {
        printf("Cannot find spiderc.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->spiderFrame[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
   
    int slopeY[20] = {-3, -2, -1, 0, 1, 2, 3,-3, -2, -1, 0, 1, -2, 3,-2, -1, -2, 1, 2, 3};
    int slopeX[20] = {1, 2, 3, 1, 2, 3, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};
    
    for(int i =0; i <spiNum; i ++){
      
       
        
        game->spider[i].visible = 1;
        game->spider[i].x = -300 - i*20;
        game->spider[i].y = game->man.y+ (10*i);
        game->spider[i].slopeX = slopeX[i];
        game->spider[i].slopeY = slopeY[i];
        game->spider[i].dx = 0;
        game->spider[i].dy = 0;
        game->spider[i].animFrame = 0;
        
    
    
    
        
    }
    
    
   
    
   game->time = 0;
    

   //Load Background
    surface = IMG_Load("backgroundPortalA.png");
    if(surface == NULL)
    {
        printf("Cannot find backgrounda.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->backgroundFrame[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("backgroundPortalb.png");
    if(surface == NULL)
    {
        printf("Cannot find backgrounda.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->backgroundFrame[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("backgroundPortalc.png");
    if(surface == NULL)
    {
        printf("Cannot find backgrounda.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->backgroundFrame[2] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("backgroundPortald.png");
    if(surface == NULL)
    {
        printf("Cannot find backgrounda.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->backgroundFrame[3] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    

    //Load Sounds
    game->music = Mix_LoadWAV("8bitgame.wav");
    if(game->music != NULL){
        Mix_VolumeChunk(game->music, 64);
        Mix_PlayChannel(-1, game->music, -1);
    }
    
    game->gunshot = Mix_LoadWAV("gunshot.wav");
    if(game->gunshot != NULL){
        Mix_VolumeChunk(game->gunshot, 4  );
        
    }
}

void processAnimations(GameState *game)
{
    //add time
    game->time++;
    
    //man movement
    Man *man = &game->man;
    
    
    //Spider Animations
    for(int i = 0; i <spiNum; i++){
    if((game->time + (int)game->spider[i].slopeX*10) %7 == 0){
        
            if(game->spider[i].animFrame == 0){
                game->spider[i].animFrame=1;
            }else
                if(game->spider[i].animFrame==1){
                    game->spider[i].animFrame=2;
                }else{
                    game->spider[i].animFrame=0;
                }
        }
    }
    
    
   
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP] ||state[SDL_SCANCODE_DOWN])
    {
        if(game->time % 8 == 0)
        {
            if(man->animFrame == 0)
            {
                man->animFrame = 1;
            }
            else
            {
                man->animFrame = 0;
            }
        }
        
        
    }
   
}


void playerMovement(GameState *game){
    // player movement and boundaries
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP])
    {
        game->man.x -= 2;
        
    }else
        if(state[SDL_SCANCODE_DOWN])
        {
            game->man.x += 2;
            
        }else{
            game->man.animFrame=1;
        }
    
    if(game->man.y < 216 ){
        game->man.y = 216;
    }
    
    if(game->man.x<443){
        game->man.x=443;
    }
    
    if(game->man.x>443){
        game->man.y = (game->man.x-443)*(1.77) + 216;
    }
    
    if(game->man.y> 450){
        game->man.y = 450;
    }
    
    if(game->man.x>575){
        game->man.x = 575;
    }
    
   
    
}


void spiderMovement(GameState *game){
    //Spider movement
    int i;
    for(i = 0; i < spiNum; i++){
        if(game->spider[i].y < 280 || game->spider[i].y > 500){
            game->spider[i].slopeY *= -1;
        }
        game->spider[i].y += game->spider[i].slopeY;
        game->spider[i].x += game->spider[i].slopeX;
        
        if(game->time > 10000){
            game->spider[i].x += game->spider[i].slopeX;;
        }
    }
    
}


void bulletCreation(GameState *game){
    // bullet creation
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(frames%7 == 0){
    if(state[SDL_SCANCODE_SPACE]){
       
        Mix_PlayChannel(-1, game->gunshot, 0);
        
        
        game->bullet[count].x = game->man.x + 10;
        game->bullet[count].y= game->man.y ;
        count++;
        if(count == totalBullets){
            count = 0;
        }
    }
    }

}

int processEvents(SDL_Window *window, GameState *game)
{
    
    SDL_Event event;
    int done = 0;
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = 1;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        done = 1;
                        break;
                }
            }
                break;
            case SDL_QUIT:
                //quit out of the game
                done = 1;
                break;
        }
    }
    
    playerMovement(game);
    spiderMovement(game);
    bulletCreation(game);
    
    
    
   // printf("Spider x: %f\n Spider y: %f\n man x: %f\n man y: %f\n\n Count = %f\n", game->spider[spiNum].x, game->spider[spiNum].y, game->man.x, game->man.y);
    
    return done;
}


void spiderCollision(GameState *game){

    
    for(int bul = 0; bul< totalBullets; bul++){
        for(int spi = 0; spi< spiNum; spi++){
            if(game->spider[spi].x > 600){
                game->spider[spi].x = -20;
            }
            if (game->bullet[bul].x < game->spider[spi].x + 40 &&
                game->bullet[bul].x > game->spider[spi].x - 40 &&
                game->bullet[bul].y < game->spider[spi].y + 40 &&
                game->bullet[bul].y > game->spider[spi].y - 40){
                
                game->bullet[bul].y = 1000;
                game->spider[spi].x = -50;
                
                
                /*game->spider[spi].visible = 0;
               
                if(game->spider[spi].visible == 0){
                    printf("Bullet x: %f\nBullet y: %f\n spider x: %f\n spider y: %f\n",game->bullet[0].x ,game->bullet[0].y ,
                           game->spider[0].x , game->spider[0].y);
                }*/
            }
        }
    }
    
   
}





void drawSprites(SDL_Renderer *renderer, GameState *game)
{
    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    //Clear the screen (to blue)
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //draw background
    
    SDL_Rect backg = {0, 0, 640, 530};
    SDL_RenderCopy(renderer, game->backgroundFrame[bgFrame], NULL, &backg);
    if(game->time % 6 == 0){
    if(bgFrame > 2){
        bgFrame =0;
    }else{
        bgFrame++;
    }
    }

    
    //draw a rectangle at man's position
    SDL_Rect rect = { game->man.x, game->man.y, 100, 100 };
    SDL_RenderCopyEx(renderer, game->manFrame[game->man.animFrame],
                     NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    
    //draw muzzleflash
    
    int muzzleNum = 0;
    game->muzzleFlash[0].x=game->man.x-10;
    game->muzzleFlash[0].y=game->man.y+30;
    game->muzzleFlash[1].x=game->man.x-10;
    game->muzzleFlash[1].y=game->man.y+30;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_SPACE])
    {
    if(game->time % 5 == 0){
        if(muzzleNum == 0){
        SDL_Rect muzzle = { game->muzzleFlash[muzzleNum].x, game->muzzleFlash[muzzleNum].y, 30, 30 };
        SDL_RenderCopy(renderer, game->muzzleFrame[muzzleNum], NULL, &muzzle);
            muzzleNum=1;
        }else{
            SDL_Rect muzzle = { game->muzzleFlash[muzzleNum].x, game->muzzleFlash[muzzleNum].y, 36, 36 };
            SDL_RenderCopy(renderer, game->muzzleFrame[muzzleNum], NULL, &muzzle);
            muzzleNum = 0;
        }
        
    }
    }
    //draw spiders
   
    for(int i = 0; i < spiNum; i++){
        if(game->spider[i].visible == 1){
            SDL_Rect spiderRect = { game->spider[i].x, game->spider[i].y, 40, 40 };
            //SDL_RenderFillRect(renderer, &spiderRect);
            SDL_RenderCopy(renderer, game->spiderFrame[game->spider[i].animFrame], NULL, &spiderRect);
        }
    }

    
    //draw bullet
   
   
    for(int i = 0; i < count; i++){
     
        SDL_Rect bulletRect = {game->bullet[i].x-=10, game->bullet[i].y+33, 8, 8};
        SDL_RenderCopy(renderer, game->bulletFrame, NULL, &bulletRect);
        
    }
 

    
    
    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    GameState gameState;
    SDL_Window *window = NULL;                    // Declare a window
    SDL_Renderer *renderer = NULL;                // Declare a renderer
    
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    
    srandom((int)time(NULL));
    
    //Create an application window with the following settings:
    window = SDL_CreateWindow("Game Window",                     // window title
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              640,                               // width, in pixels
                              530,                               // height, in pixels
                              0                                  // flags
                              );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    gameState.renderer = renderer;
    
    
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    initializeGame(&gameState);
    
    // The window is open: enter program loop (see SDL_PollEvent)
    int done = 0;
    
    //Event loop
    while(!done)
    {
        //Check for events
        done = processEvents(window, &gameState);
        
        processAnimations(&gameState);
        
        //Render display
        drawSprites(renderer, &gameState);
        
        spiderCollision(&gameState);
        
        
        //don't burn up the CPU
        //SDL_Delay(10);
        frames++;
    }
    
    
    //Shutdown game and unload all memory
    SDL_DestroyTexture(gameState.manFrame[0]);
    SDL_DestroyTexture(gameState.manFrame[1]);
    SDL_DestroyTexture(gameState.background);
    
    SDL_DestroyTexture(gameState.spiderFrame);
    SDL_DestroyTexture(gameState.bulletFrame);
    
    
    Mix_FreeChunk(gameState.gunshot);
    Mix_FreeChunk(gameState.music);
    // Close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    // Clean up
    SDL_Quit();
    return 0;
}
