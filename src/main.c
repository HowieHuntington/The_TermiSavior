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
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int totalBullets = 100;
const int spiNum = 5;
int count = 0;



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
}background;

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
    int animFrame, facingLeft, facingUp;
    
} Spider;

typedef struct
{
    float x, y;
    
}Bullet;



typedef struct
{
    //Players
    Man man;
    Sentar sentar;
    Spider spider[5];
    Bullet bullet[totalBullets];
    
    
    SDL_Texture *bulletFrame;
    SDL_Texture *manFrame[2];
    SDL_Texture *spiderFrame;
    SDL_Texture *background;
    SDL_Texture *sentarFrame[2];
    
    int time;
    
    SDL_Renderer *renderer;
} GameState;



void loadGame(GameState *game)
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

    //Load Enemy
    surface = IMG_Load("sentar.png");
    if(surface == NULL)
    {
        printf("Cannot find sentar.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->sentarFrame[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("sentar2.png");
    if(surface == NULL)
    {
        printf("Cannot find sentar.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->sentarFrame[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    game->sentar.x = 0;
    game->sentar.y = game->man.y;
    game->sentar.dx = 0;
    game->sentar.dy = 0;
    game->sentar.animFrame = 0;
    game->sentar.facingLeft = 0;
    
    

    //spider initialization
    surface = IMG_Load("spider.png");
    if(surface == NULL)
    {
        printf("Cannot find spider.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->spiderFrame = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    int slopeY[5] = {-3, -2, -1, 0, 1};
    int slopeX[5] = {1, 2, 3, 2, 3};
    for(int i =0; i <5; i ++){
        game->spider[i].x = 0;
        game->spider[i].y = game->man.y+ (10*i);
        game->spider[i].slopeX = slopeX[i];
        game->spider[i].slopeY = slopeY[i];
        game->spider[i].dx = 0;
        game->spider[i].dy = 0;
        game->spider[i].animFrame = 0;
    }
  
    
    game->time = 0;
    

   //Load Background
    surface = IMG_Load("backgroundCheck640.png");
    if(surface == NULL)
    {
        printf("Cannot find background.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    
    game->background = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    
}

void process(GameState *game)
{
    //add time
    game->time++;
    
    //man movement
    Man *man = &game->man;
    
    Sentar *sentar = &game->sentar;
    
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

   
    if(game->time % 8 == 0)
    {
        if(sentar->animFrame == 0)
        {
            sentar->animFrame = 1;
        }
        else
        {
            sentar->animFrame = 0;
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
    
    if(game->man.x>443){ //&& game->man.y<((game->man.x-443)*(1.77) + 216)){
        game->man.y = (game->man.x-443)*(1.77) + 216;
    }
    
    if(game->man.y> 450){
        game->man.y = 450;
    }
    
    if(game->man.x>575){
        game->man.x = 575;
    }
    
    // bullet creation
    if(state[SDL_SCANCODE_SPACE]){
        game->bullet[count].x = game->man.x + 40;
        game->bullet[count].y= game->man.y;
        count++;
        if(count == totalBullets){
            count = 0;
        }
        
    }
    
    
  
    //Spider movement
    int i;
    for(i = 0; i < spiNum; i++){
        if(game->spider[i].y < 280 || game->spider[i].y > 500){
            game->spider[i].slopeY *= -1;
        }
        game->spider[i].y += game->spider[i].slopeY;
        game->spider[i].x += game->spider[i].slopeX;
    }
   
    
    printf("Spider x: %f\n Spider y: %f\n man x: %f\n man y: %f\n\n Count = %f\n", game->spider[spiNum].x, game->spider[spiNum].y, game->man.x, game->man.y);
    return done;
}

/*
Spider collision(GameState *game){
    for (int spi = 0; spi < spiNum; spi++){
        for(int bul = 0; bul < totalBullets; bul++){
         if (game->bullet[bul].x < game->spider[spi].x + 40 &&
             game->bullet[bul].x > game->spider[spi].x - 40 &&
             game->bullet[bul].y < game->spider[spi].y + 40 &&
             game->bullet[bul].y > game->spider[spi].y - 40)
             return game->spider[spi];
             }
        }
    return NULL;
}*/


void doRender(SDL_Renderer *renderer, GameState *game)
{
    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    //Clear the screen (to blue)
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //draw background
    SDL_Rect backg = {0, 0, 640, 530};
    SDL_RenderCopy(renderer, game->background, NULL, &backg);
    
    //draw a rectangle at man's position
    SDL_Rect rect = { game->man.x, game->man.y, 100, 100 };
    SDL_RenderCopyEx(renderer, game->manFrame[game->man.animFrame],
                     NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
/*
   SDL_Rect sentarRect = { game->sentar.x, game->sentar.y, 150, 150 };
   SDL_RenderCopyEx(renderer, game->sentarFrame[game->sentar.animFrame], NULL, &sentarRect, 0, NULL, (game->sentar.facingLeft==0));
*/
    for(int i = 0; i < spiNum; i++){
        SDL_Rect spiderRect = { game->spider[i].x, game->spider[i].y, 40, 40 };
        SDL_RenderCopy(renderer, game->spiderFrame, NULL, &spiderRect);
    }

    
//draw bullet
    for(int i = 0; i < count; i++){
    SDL_Rect bulletRect = {game->bullet[i].x-=30, game->bullet[i].y+50, 5, 5};
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
    
    loadGame(&gameState);
    
    // The window is open: enter program loop (see SDL_PollEvent)
    int done = 0;
    
    //Event loop
    while(!done)
    {
        //Check for events
        done = processEvents(window, &gameState);
        
        process(&gameState);
        
        //Render display
        doRender(renderer, &gameState);
        
        //don't burn up the CPU
        //SDL_Delay(10);
    }
    
    
    //Shutdown game and unload all memory
    SDL_DestroyTexture(gameState.manFrame);
     SDL_DestroyTexture(gameState.background);
    
    // Close and destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    // Clean up
    SDL_Quit();
    return 0;
}
