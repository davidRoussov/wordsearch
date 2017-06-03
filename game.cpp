#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool quit = false;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        cout << "SDL could not initialize! SDL error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Word Search", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
            cout << "Window could not be created! SDL error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
                cout << "Renderer could not be created! SDL error: " << SDL_GetError() << endl;
				success = false;
			}

            if( TTF_Init() == -1 )
            {
                cout << "SDL_ttf could not initialize! SDL_ttf error: " << TTF_GetError() << endl;
                success = false;
            }
		}
	}

	return success;	
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    SDL_Quit();
}

void draw()
{
    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 100); 
    SDL_Color White = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, "G", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0; 
    Message_rect.y = 0; 
    Message_rect.w = 40;
    Message_rect.h = 30; 
    SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
}

int main(int argc, char *argv[])
{

    if (!init())
    {
        cout << "Failed to initialize SDL" << endl;
    }
    else
    {
        while (!quit) {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        cout << "***" << endl;
                    }
                }
                else 
                {      
                    string key_name = SDL_GetKeyName(event.key.keysym.sym);
                    if (key_name == "Escape")
                    {
                        quit = true;
                    }
                }
            }

            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderClear(gRenderer);

            draw();

            SDL_RenderPresent(gRenderer);
        }
    }

    close();

    return 0;
}