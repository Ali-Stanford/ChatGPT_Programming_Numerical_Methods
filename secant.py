def secant_method(f, x0, x1, tol=1e-6, max_iter=100):
    """
    Implements the secant method to find a root of a function f.

    Args:
    f: callable function of one variable
    x0: initial guess for the root
    x1: second initial guess for the root
    tol: tolerance for convergence (default=1e-6)
    max_iter: maximum number of iterations (default=100)

    Returns:
    x: estimate of the root
    """
    i = 0
    while i < max_iter:
        x = x1 - ((f(x1)*(x1 - x0)) / (f(x1) - f(x0)))
        if abs(x - x1) < tol:
            return x
        x0 = x1
        x1 = x
        i += 1
    raise ValueError("Secant method failed to converge.")
