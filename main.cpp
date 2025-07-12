#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <chrono>

using namespace std;
using namespace chrono;

const int32_t ROWS = 500;
const int32_t COLS = 500;

int GRID[ROWS][COLS];
int V[ROWS][COLS];

void simulate()
{
    int GRID2[ROWS][COLS];

    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            GRID2[i][j] = 0;
        }
    }

    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            if(GRID[i][j] == 1)
            {
                if(i == ROWS - 1)
                {
                    GRID2[i][j] = 1;
                } 
                else if(GRID[i + 1][j] == 1)
                {   
                    if(j + 1 < COLS && GRID[i + 1][j + 1] == 0)
                    {
                        GRID2[i + 1][j + 1] = 1;
                    }
                    else if(j - 1 >= 0 && GRID[i + 1][j - 1] == 0)
                    {
                        GRID2[i + 1][j - 1] = 1;
                    }
                    else
                    {
                        GRID2[i][j] = 1;
                    } 
                } 
                else
                {
                    GRID2[i + 1][j] = 1;
                } 
            }
        }
    }

    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            GRID[i][j] = GRID2[i][j];
        }
    }
}

int main()
{
    for (size_t i = 0; i < ROWS; i++)
    {
        for (size_t j = 0; j < COLS; j++)
        {
            GRID[i][j] = 0;
        }
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(COLS, ROWS, SDL_WINDOW_SHOWN, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    bool isRunning = true;
    bool isDrawing = false;
    SDL_Event ev;

    int64_t total = 0;
    int64_t count = 0;

    while (isRunning)
    {
        count++;
        int32_t ut = SDL_GetTicks();

        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) isRunning = false;
            else if(ev.type == SDL_MOUSEBUTTONDOWN) isDrawing = true;
            else if(ev.type == SDL_MOUSEBUTTONUP) isDrawing = false;
            else if(ev.type == SDL_MOUSEMOTION)
            {
                if(isDrawing) GRID[ev.button.y][ev.button.x] = 1;
            }
        }

        for (size_t i = 0; i < ROWS; i++)
        {
            for (size_t j = 0; j < COLS; j++)
            {
                if(GRID[i][j] == 1)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderDrawPoint(renderer, j, i);
                }
            }
        }

        SDL_RenderPresent(renderer);
        simulate();

        int32_t vt = SDL_GetTicks();

        int32_t dt = vt - ut;

        total += dt;
    }

    cout << "average frame time : " << total / count << "ms" << endl;
    cout << "average fps : " << 1000 / (total / count) << endl;

    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    return 0;
}