#include <iostream>
#include <cmath>

#define MAX_ITER 1000

using namespace std;

void sor(double **A, double *b, double *x, int n, double omega, double tol) {
    int iter_count = 0;
    double residual = 0.0;
    double *old_x = new double[n];
    
    do {
        iter_count++;
        residual = 0.0;
        
        for (int i = 0; i < n; i++) {
            old_x[i] = x[i];
            double sigma = 0.0;
            
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sigma += A[i][j] * x[j];
                }
            }
            
            x[i] = (1.0 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sigma);
            residual += pow(b[i] - A[i][0] * x[0] - A[i][1] * x[1] - A[i][2] * x[2], 2.0);
        }
        
        residual = sqrt(residual);
        
    } while (residual > tol && iter_count < MAX_ITER);
    
    cout << "Solution:\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }
    cout << endl;
    
    cout << "Number of iterations: " << iter_count << endl;
    
    delete[] old_x;
}

int main() {
    double **A = new double*[3];
    for (int i = 0; i < 3; i++) {
        A[i] = new double[3];
    }
    
    A[0][0] = 4.0;
    A[0][1] = 1.0;
    A[0][2] = 1.0;
    A[1][0] = 1.0;
    A[1][1] = 4.0;
    A[1][2] = 1.0;
    A[2][0] = 1.0;
    A[2][1] = 1.0;
    A[2][2] = 4.0;
    
    double b[3] = {1.0, 2.0, 3.0};
    double x[3] = {0.0, 0.0, 0.0};
    
    double omega = 1.5;
    double tol = 1e-6;
    
    sor(A, b, x, 3, omega, tol);
    
    for (int i = 0; i < 3; i++) {
        delete[] A[i];
    }
    delete[] A;
    
    return 0;
}
