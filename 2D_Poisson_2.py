import numpy as np
import matplotlib.pyplot as plt

# Define the grid size and spacing
N = 50  # Number of grid points in each direction
L = 1.0  # Length of the square domain
h = L / (N - 1)  # Spacing between grid points

# Define the boundary conditions and source term
u_top = np.zeros(N)
u_bottom = np.zeros(N)
u_left = np.zeros(N)
u_right = np.zeros(N)
x = np.linspace(0, L, N)
y = np.linspace(0, L, N)
X, Y = np.meshgrid(x, y)
f = np.sin(X)*np.cos(Y)

# Define the coefficient matrix and the right-hand side vector
A = np.zeros((N*N, N*N))
b = np.zeros(N*N)

for i in range(N):
    for j in range(N):
        k = i*N + j  # Index of the unknown u_ij
        if i == 0:
            A[k, k] = 1.0
            b[k] = u_top[j]
        elif i == N-1:
            A[k, k] = 1.0
            b[k] = u_bottom[j]
        elif j == 0:
            A[k, k] = 1.0
            b[k] = u_left[i]
        elif j == N-1:
            A[k, k] = 1.0
            b[k] = u_right[i]
        else:
            A[k, k] = -4.0
            A[k, k-1] = 1.0
            A[k, k+1] = 1.0
            A[k, k-N] = 1.0
            A[k, k+N] = 1.0
            b[k] = f[i,j]

# Solve the linear system
u = np.linalg.solve(A, b)

# Reshape the solution vector into a 2D array
U = u.reshape((N, N))

# Plot the solution
plt.contourf(X, Y, U)
plt.colorbar()
plt.xlabel('x')
plt.ylabel('y')
plt.title('2D Poisson equation solution with sin(x)*cos(y) source term')
plt.show()
