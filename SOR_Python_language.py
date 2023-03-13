import numpy as np

def sor(A, b, x0, omega, tol, max_iter):
    """
    Solves the linear system of equations Ax = b using the method of successive over-relaxation (SOR).
    
    Parameters:
    A (numpy.ndarray): the coefficient matrix of the linear system.
    b (numpy.ndarray): the right-hand side vector of the linear system.
    x0 (numpy.ndarray): the initial guess for the solution vector.
    omega (float): the relaxation parameter.
    tol (float): the tolerance for the residual.
    max_iter (int): the maximum number of iterations.
    
    Returns:
    numpy.ndarray: the solution vector.
    int: the number of iterations performed.
    """
    
    x = np.copy(x0)
    n = len(x)
    iter_count = 0
    residual = np.linalg.norm(b - A @ x)
    
    while residual > tol and iter_count < max_iter:
        iter_count += 1
        for i in range(n):
            old_x_i = x[i]
            x[i] += omega * ((b[i] - A[i, :] @ x) / A[i, i] - x[i])
            residual = np.linalg.norm(b - A @ x)
            if residual <= tol:
                break
        if np.allclose(x, old_x_i):
            break
    
    return x, iter_count

# Define the coefficient matrix A, the right-hand side vector b, and the initial guess x0
A = np.array([[4, 1, 1], [1, 4, 1], [1, 1, 4]])
b = np.array([1, 2, 3])
x0 = np.array([0, 0, 0])

# Solve the linear system using SOR
omega = 1.5
tol = 1e-6
max_iter = 1000
x, iter_count = sor(A, b, x0, omega, tol, max_iter)

# Print the solution and the number of iterations
print("Solution:", x)
print("Number of iterations:", iter_count)
