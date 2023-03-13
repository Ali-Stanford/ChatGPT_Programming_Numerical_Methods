            g[i * Ny + j] = d[i * Ny + j] / b[i * Ny + j];
        }
        for (int j = 2; j < Ny - 1; j++)
        {
            e[i * Ny + j] = e[i * Ny + j] * f[i * Ny + (j - 1)];
            g[i * Ny + j] = g[i * Ny + j] - e[i * Ny + j] * g[i * Ny + (j - 1)];
        }
        v_star[i * Ny + (Ny - 2)] = g[i * Ny + (Ny - 2)];
        for (int j = Ny - 3; j >= 1; j--)
        {
            v_star[i * Ny + j] = g[i * Ny + j] - f[i * Ny + j] * v_star[i * Ny + (j + 1)];
        }
    }

    // Calculate u_n+1 and v_n+1
    for (int i = 1; i < Nx - 1; i++)
    {
        for (int j = 1; j < Ny - 1; j++)
        {
            u[i * Ny + j] = u_star[i * Ny + j] - dt / dx * (p[(i + 1) * Ny + j] - p[i * Ny + j]);
            v[i * Ny + j] = v_star[i * Ny + j] - dt / dy * (p[i * Ny + (j + 1)] - p[i * Ny + j]);
        }
    }

    // Apply periodic boundary conditions to u and v
    for (int i = 0; i < Nx; i++)
    {
        u[i * Ny] = u[i * Ny + (Ny - 2)];
        u[i * Ny + (Ny - 1)] = u[i * Ny + 1];
        v[i * Ny] = v[i * Ny + (Ny - 2)];
        v[i * Ny + (Ny - 1)] = v[i * Ny + 1];
    }
    for (int j = 0; j < Ny; j++)
    {
        u[j] = u[(Nx - 2) * Ny + j];
        u[(Nx - 1) * Ny + j] = u[Ny + j];
        v[j] = v[(Nx - 2) * Ny + j];
        v[(Nx - 1) * Ny + j] = v[Ny + j];
    }

    // Output results to file
    if (t % output_freq == 0)
    {
        std::ofstream file("output_" + std::to_string(t) + ".txt");
        for (int j = 0; j < Ny; j++)
        {
            for (int i = 0; i < Nx; i++)
            {
                file << i * dx << " " << j * dy << " " << u[i * Ny + j] << " " << v[i * Ny + j] << "\n";
            }
            file << "\n";
        }
        file.close();
    }
}

int main()
{
    // Simulation parameters
    const int Nx = 64;              // Number of grid points in the x-direction
    const int Ny = 64;              // Number of grid points in the y-direction
    const double Lx = 2.0 * M_PI;   // Length of the domain in the x-direction
    const double Ly = 
