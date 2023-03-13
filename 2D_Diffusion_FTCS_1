import numpy as np
import matplotlib.pyplot as plt

# Define the parameters
D = 0.1  # Diffusion coefficient
L = 1.0  # Length of the square box
N = 100  # Number of grid points in each direction
dx = L / (N - 1)  # Grid spacing
dy = L / (N - 1)
dt = 0.0001  # Time step
t_final = 1.0  # Final time

# Define the initial condition
u = np.zeros((N, N))
u[:, 0] = 1.0  # Bottom boundary
u[:, -1] = 1.0  # Top boundary
u[0, :] = 0.0  # Left boundary
u[-1, :] = 0.0  # Right boundary

# Define the coefficients for the FTCS method
alpha = D * dt / dx**2
beta = D * dt / dy**2

# Iterate in time
t = 0.0
while t < t_final:
    # Compute the next time step
    u[1:-1, 1:-1] += alpha * (u[2:, 1:-1] - 2*u[1:-1, 1:-1] + u[:-2, 1:-1]) + beta * (u[1:-1, 2:] - 2*u[1:-1, 1:-1] + u[1:-1, :-2])

    # Update the boundary conditions
    u[:, 0] = 1.0  # Bottom boundary
    u[:, -1] = 1.0  # Top boundary
    u[0, :] = 0.0  # Left boundary
    u[-1, :] = 0.0  # Right boundary

    # Increase the time
    t += dt

# Plot the solution
x = np.linspace(0, L, N)
y = np.linspace(0, L, N)
X, Y = np.meshgrid(x, y)
plt.pcolormesh(X, Y, u, cmap='coolwarm')
plt.colorbar()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Diffusion equation in a square box')
plt.show()
