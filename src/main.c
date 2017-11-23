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


typedef struct
{
    float x, y;
    float dx, dy;
    short life;
    char *name;
    int onLedge;
    
    int animFrame, facingLeft, facingUp;
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
    //Players
    Man man;
    Sentar sentar;
    
    SDL_Texture *manFrame[2];
    SDL_Texture *sentarFrame[2];
    SDL_Texture *background;
    
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
    
    game->man.x = 1100;
    game->man.y = 300;
    game->man.dx = 0;
    game->man.dy = 0;
    game->man.facingLeft = 1;
    game->man.animFrame = 0;
    game->man.facingLeft = 1;
    
    
    
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
    
  
    
    game->time = 0;
    

   //Load Background
    surface = IMG_Load("backgroundwithpent.png");
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
    //man->x=0;
    //man->y =0;
    
    Sentar *sentar = &game->sentar;
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT] ||state[SDL_SCANCODE_RIGHT] ||state[SDL_SCANCODE_UP] ||state[SDL_SCANCODE_DOWN])
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
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT])
    {
        game->man.x -= 3;
        game->man.facingLeft = 1;
        
        
    }else
    if(state[SDL_SCANCODE_RIGHT])
    {
        game->man.x += 3;
        game->man.facingLeft = 0;
       
    }else
    if(state[SDL_SCANCODE_UP])
    {
        game->man.y -= 3;
        
        
    }else
    if(state[SDL_SCANCODE_DOWN])
    {
        game->man.y += 3;
        
        
    }else{
        game->man.animFrame=1;
    }
    
    
    //Sentar AI
    
    if(game->man.y > game->sentar.y)
    {
        game->sentar.y++;
        game->sentar.y++;
        game->sentar.y++;
    }else
        if(game->man.y < game->sentar.y)
        {
            game->sentar.y--;
             game->sentar.y--;
             game->sentar.y--;
            
        }else
            if(game->man.x > game->sentar.x)
            {
        
                game->sentar.x++;
        game->sentar.x++;
       game->sentar.x++;
    }else{
        game->sentar.x--;
         game->sentar.x--;
         game->sentar.x--;
    }
    
    
    printf("Sentar x: %f\n Sentar y: %f\n man x: %f\n man y: %f\n", game->sentar.x, game->sentar.y, game->man.x, game->man.y);
    return done;
}

void doRender(SDL_Renderer *renderer, GameState *game)
{
    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    //Clear the screen (to blue)
    SDL_RenderClear(renderer);
    
    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    //draw background
    SDL_Rect backg = {0, 0, 1280, 1060};
    SDL_RenderCopy(renderer, game->background, NULL, &backg);
    
    //draw a rectangle at man's position
    SDL_Rect rect = { game->man.x, game->man.y, 150, 150 };
    SDL_RenderCopyEx(renderer, game->manFrame[game->man.animFrame],
                     NULL, &rect, 0, NULL, (game->man.facingLeft == 0));
    
    
    SDL_Rect sentarRect = { game->sentar.x, game->sentar.y, 150, 150 };
    SDL_RenderCopyEx(renderer, game->sentarFrame[game->sentar.animFrame], NULL, &sentarRect, 0, NULL, (game->sentar.facingLeft==0));
    
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
                              1280,                               // width, in pixels
                              1060,                               // height, in pixels
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
