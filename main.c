#include <stdio.h>
#include "fast_fluid_dynamics.h"

static fast_fluid_solver_t fluid_solver;

static float dens_prev_buf[N_sim] = {0};
static float dens_buf[N_sim] = {0};
static float u_prev_buf[N_sim] = {0};
static float u_buf[N_sim] = {0};
static float v_prev_buf[N_sim] = {0};
static float v_buf[N_sim] = {0};

float visc = 0.5;
float diff = 0.5;

float dt = 1.0f / 100.0f; // 100Hz 

int main(void) {

    fast_fluid_solver_init(&fluid_solver, N_sim, dens_prev_buf, dens_buf, u_prev_buf, u_buf, v_prev_buf, v_buf, visc, diff, dt);

    return 0;
}
