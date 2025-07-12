#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

// window surface
// int main()
// {
//     SDL_Window *window = nullptr;
//     SDL_Surface *windowSurface = nullptr;
//     SDL_Surface *imageSurface = nullptr;

//     if(SDL_Init(SDL_INIT_VIDEO) < 0)
//     {
//         cout << "video init error : " << SDL_GetError() << endl;
//     }
//     else
//     {
//         window = SDL_CreateWindow("test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

//         if(window == NULL)
//         {
//             cout << "Window creation error : " << SDL_GetError() << endl;
//         }
//         else
//         {
//             windowSurface = SDL_GetWindowSurface(window);
//             imageSurface = SDL_LoadBMP("blackbuck.bmp");

//             if(imageSurface == NULL)
//                 cout << "Image loading error : " << SDL_GetError() << endl;
//             else
//             {
//                 SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);

//                 bool isRunning = true;
//                 SDL_Event ev;

//                 while (isRunning)
//                 {
//                     while (SDL_PollEvent(&ev) != 0)
//                     {
//                         if(ev.type == SDL_QUIT)
//                             isRunning = false;
//                         else if(ev.type == SDL_MOUSEMOTION)
//                         {
//                             cout << "mouse moving" << endl;
//                             cout << "x : " << ev.button.x << " ";
//                             cout << "y : " << ev.button.y << endl;
//                         }
//                         else if(ev.type == SDL_MOUSEBUTTONUP)
//                             cout << "mouse click" << endl;
//                     }

//                     SDL_UpdateWindowSurface(window);
//                 }
//             }
//         }
//     }

//     SDL_FreeSurface(imageSurface);
//     imageSurface = nullptr;

//     SDL_DestroyWindow(window);
//     window = nullptr;
//     windowSurface = nullptr;

//     SDL_Quit();

//     return 0;
// }

// using renderer
int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderDrawPoint(renderer, 400, 300);
    SDL_RenderPresent(renderer);

    bool isRunning = true;
    bool drawing = false; 
    SDL_Event ev;

    while (isRunning)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            switch (ev.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (ev.button.button == SDL_BUTTON_LEFT)
                    drawing = true;
                break;

            case SDL_MOUSEBUTTONUP:
                if (ev.button.button == SDL_BUTTON_LEFT)
                    drawing = false;
                break;

            case SDL_MOUSEMOTION:
                if (drawing)
                {
                    int x = ev.motion.x;
                    int y = ev.motion.y;
                    SDL_RenderDrawPoint(renderer, x, y);
                    SDL_RenderPresent(renderer);
                }
                break;
            }
        }

        SDL_Delay(0);
    }
}