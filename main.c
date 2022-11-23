#include <stdio.h>
#include "SDL/include/SDL.h"
#include "fast_fluid_dynamics.h"

static fast_fluid_solver_t fluid_solver;

static float dens_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float dens_buf[(N_sim+2) * (N_sim+2)] = {0};
static float u_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float u_buf[(N_sim+2) * (N_sim+1)] = {0};
static float v_prev_buf[(N_sim+2) * (N_sim+2)] = {0};
static float v_buf[(N_sim+2) * (N_sim+2)] = {0};

float visc = 0.5;
float diff = 0.5;

float dt = 1.0f / 100.0f; // 100Hz 

static float src_dens_buf[(N_sim+2) * (N_sim+2)] = {0};
static float src_u_buf[(N_sim+2) * (N_sim+2)] = {0};
static float src_v_buf[(N_sim+2) * (N_sim+2)] = {0};

int main(int argc, char *argv[]) {

    // fast_fluid_solver_init(&fluid_solver, N_sim, dens_prev_buf, dens_buf, u_prev_buf, u_buf, v_prev_buf, v_buf, visc, diff, dt);

    // // create density source
    // src_dens_buf[IX(N_sim / 2, N_sim / 2)] = 1.0f;

    // //create velocty field
    // for(int i = 1; i < N_sim; i++) {
    //     for(int j = 1; j < N_sim; j++) {
    //         src_u_buf[IX(i,j)] = -0.5f;
    //         src_v_buf[IX(i,j)] = 0;
    //     }
    // }

    // //compute initial step with sources
    // fast_fluid_step(&fluid_solver, src_dens_buf, src_u_buf, src_v_buf);

    // // compute 10 steps of fluid dynamics
    // for(int i = 0; i < 10; i++) {
    //     fast_fluid_step(&fluid_solver, dens_prev_buf, u_prev_buf, v_prev_buf);
    // }

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "SDL2Test",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
