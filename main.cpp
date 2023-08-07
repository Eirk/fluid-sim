#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
// #include <stdbool.h>
// #include "SDL/include/SDL.h"
#include "fast_fluid_dynamics.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
// //The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

// //The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

static fast_fluid_solver_t fluid_solver;

static float dens_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float dens_buf[(N_sim+2) * (N_sim+2)] = {0};
static float u_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float u_buf[(N_sim+2) * (N_sim+2)] = {0};
static float v_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float v_buf[(N_sim+2) * (N_sim+2)] = {0};

float visc = 0.5;
float diff = 0.5;

float dt = 1.0f / 50.0f; // 100Hz 

static float src_dens_buf[(N_sim+2) * (N_sim+2)] = {0};
static float src_u_buf[(N_sim+2) * (N_sim+2)] = {0};
static float src_v_buf[(N_sim+2) * (N_sim+2)] = {0};

static void draw_rectangle(SDL_Surface* surface, int x, int y, int width, int height)
{
    SDL_LockSurface(surface);
    // std::vector<uint8_t> pixels(surface->h * surface->pitch, 0);
    int size_pixels = surface->h * surface->pitch;
    uint8_t *pixels = (uint8_t *)malloc(size_pixels * sizeof(uint8_t));
    memset(pixels, 0, size_pixels * sizeof(uint8_t));

    int dy, dx;
    int maxwidth = x + width;
    int maxheight = y + height;
    for (dy = y; dy < maxheight; dy++) {
        for (dx = x; dx < maxwidth; dx++) {
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch)] = 0;
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch) + 1] = 255;
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch) + 2] = 0;
        }
    }
    memcpy(surface->pixels, pixels, size_pixels);
    free(pixels);

    SDL_UnlockSurface(surface);
}

static void draw_fluid(SDL_Surface* surface, float *p_dens, int square_size)
{
    SDL_LockSurface(surface);

    int size_pixels = surface->h * surface->pitch;
    uint8_t *pixels = (uint8_t *)malloc(size_pixels * sizeof(uint8_t));
    memset(pixels, 0, size_pixels * sizeof(uint8_t));

    int dy, dx;
    for (dy = 0; dy < square_size; dy++) {
        for (dx = 0; dx < square_size; dx++) {
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch)] = (int)(p_dens[IX(dx, dy)] * 255);
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch) + 1] = (int)(p_dens[IX(dx, dy)] * 255);
            pixels[(dx * surface->format->BytesPerPixel) + (dy * surface->pitch) + 2] = (int)(p_dens[IX(dx, dy)] * 255);
        }
    }
    memcpy(surface->pixels, pixels, size_pixels);
    free(pixels);

    SDL_UnlockSurface(surface);
}

int init()
{
    //Initialization flag
    // bool success = true;
    int success;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *argv[]) {

    fast_fluid_solver_init(&fluid_solver, N_sim, dens_prev_buf, dens_buf, u_prev_buf, u_buf, v_prev_buf, v_buf, visc, diff, dt);

    // create density source
    for(int i = -5; i < 5; i++) {
        for(int j = -5; j < 5; j++) {
            src_dens_buf[IX(N_sim / 2 + i, N_sim / 2 + j)] = 1.0f;
        }
    }

    //create velocity field
    for(int i = -2; i < 2; i++) {
        for(int j = -2; j < 2; j++) {
            src_u_buf[IX(N_sim / 2 + i, N_sim / 2 + j)] = 10.0f;
        }
    }
    // for(int i = 1; i < N_sim; i++) {
    //     for(int j = 1; j < N_sim; j++) {
    //         src_u_buf[IX(i,j)] = -0.5f;
    //         src_v_buf[IX(i,j)] = 0;
    //     }
    // }

    // //compute initial step with sources
    fast_fluid_step(&fluid_solver, src_dens_buf, src_u_buf, src_v_buf);

    // // compute 10 steps of fluid dynamics
    // for(int i = 0; i < 10; i++) {
    //     fast_fluid_step(&fluid_solver, dens_prev_buf, u_prev_buf, v_prev_buf);
    // }

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        // draw rectangle
        // draw_rectangle(gScreenSurface, 50, 50, 100, 100);

        //draw to surface
        draw_fluid(gScreenSurface, dens_prev_buf, N_sim);

        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
        
        // compute 50 steps of fluid dynamics
        for(int i = 0; i < 500; i++) {
            // fast_fluid_step(&fluid_solver, dens_prev_buf, u_prev_buf, v_prev_buf);
            fast_fluid_step(&fluid_solver, src_dens_buf, src_u_buf, v_prev_buf);

            //draw to surface
            draw_fluid(gScreenSurface, dens_prev_buf, N_sim);

            //Update the surface
            SDL_UpdateWindowSurface( gWindow );
        }

        //Update the surface
        // SDL_UpdateWindowSurface( gWindow );

        //Hack to get window to stay up
        SDL_Event e; 
        bool quit = false; 
        while( quit == false ) { 
            while( SDL_PollEvent( &e ) ) { 
                if( e.type == SDL_QUIT ) quit = true; 
            } 
        }
    }

    //Free resources and close SDL
    close();

    // SDL_Init(SDL_INIT_VIDEO);

    // SDL_Window *window = SDL_CreateWindow(
    //     "SDL2Test",
    //     SDL_WINDOWPOS_UNDEFINED,
    //     SDL_WINDOWPOS_UNDEFINED,
    //     640,
    //     480,
    //     0
    // );

    // SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    // SDL_RenderClear(renderer);
    // SDL_RenderPresent(renderer);

    // SDL_Delay(3000);

    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 0;
}
