    // Solve tridiagonal system for u_star
    for (int j = 1; j < Ny - 1; j++)
    {
        for (int i = 1; i < Nx - 1; i++)
        {
            e[i * Ny + j] = a[i * Ny + j] / b[(i - 1) * Ny + j];
            f[i * Ny + j] = c[i * Ny + j] / b[(i + 1) * Ny + j];
            g[i * Ny + j] = d[i * Ny + j] / b[i * Ny + j];
        }
        for (int i = 2; i < Nx - 1; i++)
        {
            e[i * Ny + j] = e[i * Ny + j] * f[(i - 1) * Ny + j];
            g[i * Ny + j] = g[i * Ny + j] - e[i * Ny + j] * g[(i - 1) * Ny + j];
        }
        u_star[(Nx - 2) * Ny + j] = g[(Nx - 2) * Ny + j];
        for (int i = Nx - 3; i >= 1; i--)
        {
            u_star[i * Ny + j] = g[i * Ny + j] - f[i * Ny + j] * u_star[(i + 1) * Ny + j];
        }
    }

    // Solve for v_star
    for (int i = 1; i < Nx - 1; i++)
    {
        for (int j = 1; j < Ny - 1; j++)
        {
            alpha = 0.5 * nu / (dx * dx);
            beta = 0.5 * nu / (dy * dy);
            gamma = -rho / dt;

            a[i * Ny + j] = -beta;
            b[i * Ny + j] = 1.0 + 2.0 * alpha + 2.0 * beta;
            c[i * Ny + j] = -beta;
            d[i * Ny + j] = gamma - rhs_v[i * Ny + j];
        }
    }

    // Set boundary conditions for v_star
    for (int i = 1; i < Nx - 1; i++)
    {
        a[i * Ny] = 0.0;
        b[i * Ny] = 1.0;
        c[i * Ny + (Ny - 2)] = 0.0;
        b[i * Ny + (Ny - 1)] = 1.0;
    }
    for (int j = 1; j < Ny - 1; j++)
    {
        a[j] = 0.0;
        b[j] = 1.0;
        c[(Nx - 2) * Ny + j] = 0.0;
        b[(Nx - 1) * Ny + j] = 1.0;
    }

    // Solve tridiagonal system for v_star
    for (int i = 1; i < Nx - 1; i++)
    {
        for (int j = 1; j < Ny - 1; j++)
        {
            e[i * Ny + j] = a[i * Ny + j] / b[i * Ny + (j - 1)];
            f[i * Ny + j] = c[i * Ny + j] / b[i * Ny + (j + 1)];
