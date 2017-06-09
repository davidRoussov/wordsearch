#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <sstream>
#include <string>
#include <ctime>
#include "InitializeBoard.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int GRID_SIZE = 10;
const int GRID_PADDING = 100;
const int GRID_UNIT_LENGTH = (SCREEN_WIDTH - GRID_PADDING * 2) / GRID_SIZE;
const int NUMBER_SPECIAL_WORDS = 3;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* Sans;

bool quit = false;
char **board;

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
            else {
                Sans = TTF_OpenFont("OpenSans-Regular.ttf", 100); 
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

void printLetter(int x, int y, char letter)
{
    const char *const_char_letter = &letter;

    SDL_Color Color = {0, 0, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Sans, const_char_letter, Color);
    SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = x; 
    Message_rect.y = y; 
    Message_rect.w = GRID_UNIT_LENGTH;
    Message_rect.h = GRID_UNIT_LENGTH; 
    SDL_RenderCopy(gRenderer, message, NULL, &Message_rect);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void draw()
{
    int x = GRID_PADDING;
    int y = GRID_PADDING;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            char letter = board[i][j];

            printLetter(x, y, letter);

            x += GRID_UNIT_LENGTH;
        }

        x = GRID_PADDING;
        y += GRID_UNIT_LENGTH;
    }
}

int main(int argc, char *argv[])
{

    if (!init())
    {
        cout << "Failed to initialize SDL" << endl;
    }
    else
    {




        InitializeBoard *board_initializer = new InitializeBoard(NUMBER_SPECIAL_WORDS, GRID_SIZE);
        board = board_initializer->generate();
        return 0;








        

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