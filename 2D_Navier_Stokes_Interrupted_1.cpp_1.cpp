#include <iostream>
#include <cmath>

using namespace std;

const int Nx = 64;               // Number of grid points in x-direction
const int Ny = 64;               // Number of grid points in y-direction
const double Lx = 2.0 * M_PI;    // Domain size in x-direction
const double Ly = 2.0 * M_PI;    // Domain size in y-direction
const double dx = Lx / (Nx - 1); // Grid spacing in x-direction
const double dy = Ly / (Ny - 1); // Grid spacing in y-direction
const double dt = 0.01;          // Time step
const double T = 10.0;           // Total simulation time
const double Re = 100.0;         // Reynolds number
const double nu = 1.0 / Re;      // Kinematic viscosity
const double rho = 1.0;          // Density

// Function to compute initial condition for velocity
void initialize_velocity(double* u, double* v)
{
    double x, y;
    for (int i = 0; i < Nx; i++)
    {
        for (int j = 0; j < Ny; j++)
        {
            x = i * dx;
            y = j * dy;
            u[i * Ny + j] = cos(x) * sin(y);
            v[i * Ny + j] = -sin(x) * cos(y);
        }
    }
}

// Function to solve the implicit system for intermediate velocity
void implicit_solve(double* rhs_u, double* rhs_v, double* u_star, double* v_star)
{
    double* a = new double[Nx * Ny];
    double* b = new double[Nx * Ny];
    double* c = new double[Nx * Ny];
    double* d = new double[Nx * Ny];
    double* e = new double[Nx * Ny];
    double* f = new double[Nx * Ny];
    double* g = new double[Nx * Ny];

    double alpha, beta, gamma;

    // Solve for u_star
    for (int i = 1; i < Nx - 1; i++)
    {
        for (int j = 1; j < Ny - 1; j++)
        {
            alpha = 0.5 * nu / (dx * dx);
            beta = 0.5 * nu / (dy * dy);
            gamma = -rho / dt;

            a[i * Ny + j] = -alpha;
            b[i * Ny + j] = 1.0 + 2.0 * alpha + 2.0 * beta;
            c[i * Ny + j] = -alpha;
            d[i * Ny + j] = gamma - rhs_u[i * Ny + j];
        }
    }

    // Set boundary conditions for u_star
    for (int j = 1; j < Ny - 1; j++)
    {
        a[j] = 0.0;
        b[j] = 1.0;
        c[(Nx - 2) * Ny + j] = 0.0;
        b[(Nx - 1) * Ny + j] = 1.0;
    }
    for (int i = 
