
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 700
double R=0;
SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;
bool gameIsRunning=false;

int initializing(){
if(SDL_Init(SDL_INIT_VIDEO)!=0){
std::cout<<"Error: SDL failed to initialize\n"<<"SDL Error:"<<" "<<SDL_GetError()<<'\n';
return 0;
}


 win = SDL_CreateWindow("Drawing Circle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT, 0);
if (!win)
    {
       std::cout<<"Error: SDL failed to open window\n"<<"SDL Error:"<<" "<<SDL_GetError()<<'\n';
       return 0;;
    }



    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!rend)
    {
        std::cout<<"Error: SDL failed to create renderer\n"<<"SDL Error:"<<" "<<SDL_GetError()<<'\n';
        return 0;;
    }

	return 1;
}
void updating_radious()
{
R+=2;
if(R>=SCREEN_HEIGHT/2) R=0;
}

void  event_loop()
{
  SDL_Event ev;

  while(SDL_PollEvent(&ev))
     {
       if(ev.type==SDL_QUIT) {gameIsRunning=false; break;}
     }

}


void draw_Circle( int centerX, int centerY, int r) {
    for (int x = -r; x <= r; x++) {
        for (int y = -r; y <= r; y++) {
            if (x*x + y*y <= r*r) {
                SDL_RenderDrawPoint(rend, centerX + x, centerY + y);
            }
        }
    }
}
void Draw()
{

    SDL_SetRenderDrawColor(rend, 0, 255, 0, 0);
	SDL_RenderClear(rend);
    updating_radious();
	SDL_SetRenderDrawColor(rend, 250, 0, 0, 0);
    draw_Circle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,R);
	SDL_RenderPresent(rend);

}


int main(int argc,char *argv[])
{
gameIsRunning=initializing();

while(gameIsRunning)
{
	event_loop();
    Draw();
}
SDL_DestroyWindow(win);
SDL_Quit();
return 0;
}