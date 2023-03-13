import numpy as np
import matplotlib.pyplot as plt

# Define grid parameters
Lx = 1.0     # length of domain in x direction
Ly = 1.0     # length of domain in y direction
Nx = 101     # number of grid points in x direction
Ny = 101     # number of grid points in y direction
dx = Lx/(Nx-1)   # grid spacing in x direction
dy = Ly/(Ny-1)   # grid spacing in y direction
x = np.linspace(0, Lx, Nx)
y = np.linspace(0, Ly, Ny)
X, Y = np.meshgrid(x, y)

# Define time parameters
T = 0.1     # total simulation time
dt = 0.0001     # time step
nt = int(T/dt)  # number of time steps

# Define diffusion coefficient and initial condition
D = 0.1     # diffusion coefficient
u0 = np.exp(-((X-0.5)**2 + (Y-0.5)**2)/0.01)

# Define BTCS matrix
alpha = D*dt/dx**2
beta = D*dt/dy**2
A = np.zeros((Nx*Ny, Nx*Ny))
for i in range(1, Nx-1):
    for j in range(1, Ny-1):
        k = i*Ny + j
        A[k,k] = 1 + 2*alpha + 2*beta
        A[k,k-1] = -alpha
        A[k,k+1] = -alpha
        A[k,k-Ny] = -beta
        A[k,k+Ny] = -beta
A = np.linalg.inv(A)

# Initialize solution array
u = u0.flatten()

# Time stepping loop
for n in range(nt):
    un = u.copy()
    for i in range(1, Nx-1):
        for j in range(1, Ny-1):
            k = i*Ny + j
            u[k] = A[k,:] @ un
    # Apply zero-flux boundary conditions
    u[:Ny] = u[Ny:2*Ny]
    u[-Ny:] = u[-2*Ny:-Ny]
    u[::Ny] = u[Ny:Ny*(Nx-1):Ny]
    u[Ny*(Nx-1)::Ny] = u[Ny*(Nx-2):-Ny:Ny]

# Reshape solution array to match grid and plot
u = u.reshape((Nx, Ny)).T
plt.contourf(x, y, u, levels=np.linspace(u.min(), u.max(), 101))
plt.colorbar()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution to 2D Diffusion Equation')
plt.show()
