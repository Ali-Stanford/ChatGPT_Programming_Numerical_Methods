#include <iostream>
#include <Eigen/Sparse>
#include <Eigen/IterativeLinearSolvers>

using namespace std;
using namespace Eigen;

int main() {
    // Define the size of the matrix
    const int N = 100;

    // Define the sparse matrix A
    SparseMatrix<double> A(N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double val = 0.0;
            if (i == j) {
                val = 2.0;
            }
            else if (i == j-1 || i == j+1) {
                val = -1.0;
            }
            if (val != 0.0) {
                A.insert(i, j) = val;
            }
        }
    }
    A.makeCompressed();

    // Define the right-hand side vector b
    VectorXd b(N);
    b.setOnes();

    // Initialize the solution vector x
    VectorXd x(N);
    x.setZero();

    // Solve the linear system using the GMRES algorithm
    int max_iterations = 1000; // Maximum number of iterations
    double tolerance = 1e-6; // Tolerance for the iterative solver
    BiCGSTAB<SparseMatrix<double>> inner_solver; // Inner linear solver
    inner_solver.setTolerance(tolerance); // Set the tolerance for the inner solver
    GMRES<SparseMatrix<double>> solver; // Outer linear solver
    solver.setMaxIterations(max_iterations); // Set the maximum number of iterations
    solver.setTolerance(tolerance); // Set the tolerance for the solver
    solver.compute(A); // Compute the preconditioner (identity matrix)
    x = solver.solveWithGuess(b, x, inner_solver); // Solve the linear system

    // Print the solution vector
    cout << "Solution vector x:" << endl;
    for (int i = 0; i < N; i++) {
        cout << x(i) << endl;
    }

    return 0;
}
