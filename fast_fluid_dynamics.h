#define N_sim 128 // simulate grid of size NxN
#define IX(i,j) ((i)+(N_sim+2)*(j)) // macro to index into 2d grid represented by 1d arrays
#define SWAP(x0,x) {float *tmp = x0; x0 = x; x = tmp;}

typedef struct {
    float x;
    float y;
    float z;
} fVector3_t;

typedef struct {
    int N;              //square area for now
    float *dens_prev;   // scalar density field previous
    float *u_prev;      // 'u' component of velocity field previous
    float *v_prev;      // 'v' component of velocity field previous
    float *dens;        // scalar density field
    float *u;           // 'u' component of velocity field
    float *v;           // 'v' component of velocity field
    float visc;         // viscosity
    float diff;         // diffusion rate
    float dt;           // time step (seconds)
} fast_fluid_solver_t;

#ifdef __cplusplus
extern "C"{
#endif

void fast_fluid_solver_init(fast_fluid_solver_t *solver, int N, float *dens_prev_buf, float *dens_buf, float *u_prev_buf, float *u_buf, float *v_prev_buf, float *v_buf, float visc, float diff, float dt);
void fast_fluid_step(fast_fluid_solver_t *solver);

#ifdef __cplusplus
}
#endif