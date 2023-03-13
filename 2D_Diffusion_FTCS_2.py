import numpy as np
import matplotlib.pyplot as plt

# Define the parameters
D = 1.0  # diffusion coefficient
L = 1.0  # size of the square box
Nx = 51  # number of grid points in the x direction
Ny = 51  # number of grid points in the y direction
dx = L/(Nx-1)  # grid spacing in the x direction
dy = L/(Ny-1)  # grid spacing in the y direction
dt = 0.0001  # time step
T = 1.0  # final time

# Define the initial conditions
u = np.zeros((Nx,Ny))
u[:,0] = 1.0  # Dirichlet boundary condition at the bottom
u[:,-1] = 1.0  # Dirichlet boundary condition at the top
u[0,:] = 0.0  # Dirichlet boundary condition on the left
u[-1,:] = 0.0  # Dirichlet boundary condition on the right

# Define the FTCS scheme
def ftcs(u, D, dx, dy, dt):
    Nx, Ny = u.shape
    u_new = u.copy()
    for i in range(1, Nx-1):
        for j in range(1, Ny-1):
            u_new[i,j] = u[i,j] + D*dt*(u[i+1,j] - 2*u[i,j] + u[i-1,j])/dx**2 \
                         + D*dt*(u[i,j+1] - 2*u[i,j] + u[i,j-1])/dy**2
    return u_new

# Solve the diffusion equation using the FTCS scheme
t = 0.0
while t < T:
    u = ftcs(u, D, dx, dy, dt)
    t += dt

# Plot the results
x = np.linspace(0, L, Nx)
y = np.linspace(0, L, Ny)
X, Y = np.meshgrid(x, y)
plt.contourf(X, Y, u, cmap='coolwarm')
plt.colorbar()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Diffusion in a Square Box')
plt.show()
