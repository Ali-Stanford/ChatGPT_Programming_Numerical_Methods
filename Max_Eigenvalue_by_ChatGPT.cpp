#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ITERATIONS 1000
#define EPSILON 0.00001

int main()
{
    // Define matrix A
    double A[3][3] = {{2, -1, 0},
                      {-1, 2, -1},
                      {0, -1, 2}};

    // Define initial guess for eigenvector x
    double x[3] = {1, 1, 1};

    // Initialize variables
    int i, j, k;
    double lambda = 0;
    double norm_x, norm_y;
    double y[3];

    // Perform power iteration method
    for (k = 0; k < MAX_ITERATIONS; k++) {
        // Multiply A by x
        for (i = 0; i < 3; i++) {
            y[i] = 0;
            for (j = 0; j < 3; j++) {
                y[i] += A[i][j] * x[j];
            }
        }

        // Find the maximum component of y and normalize
        norm_y = 0;
        for (i = 0; i < 3; i++) {
            if (fabs(y[i]) > norm_y) {
                norm_y = fabs(y[i]);
            }
        }
        for (i = 0; i < 3; i++) {
            x[i] = y[i] / norm_y;
        }

        // Compute the corresponding eigenvalue
        lambda = 0;
        for (i = 0; i < 3; i++) {
            lambda += A[i][0] * x[i];
        }

        // Check for convergence
        norm_x = 0;
        for (i = 0; i < 3; i++) {
            norm_x += pow(x[i], 2);
        }
        norm_x = sqrt(norm_x);
        if (fabs(lambda - norm_y) < EPSILON * norm_x) {
            break;
        }
    }

    // Print the maximum eigenvalue
    printf("Maximum eigenvalue: %f\n", lambda);

    return 0;
}
