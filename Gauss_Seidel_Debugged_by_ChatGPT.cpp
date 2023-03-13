#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

const double THRESHOLD = pow(10. , -6.);

void GS(double **a, double x[], double b[], int n) {
    double *r = new double[n];
    double *xK = new double[n];
    for (int j = 0; j < n; j++) {
        r[j] = 0;
        xK[j] = 0;
        x[j] = 0;
    }
    while (true) {
        for (int i = 0; i < n; i++) {
            double sum1 = 0;
            double sum2 = 0;
            for (int j = 0; j < i; j++) {
                sum1 += a[i][j] * xK[j];
            }
            for (int j = i + 1; j < n; j++) {
                sum2 += a[i][j] * x[j];
            }
            xK[i] = (1. / a[i][i]) * (b[i] - sum1 - sum2);
        }
        for (int i = 0; i < n; i++) {
            x[i] = xK[i];
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * x[k];
            }
            r[i] = b[i] - sum;
        }
        double max = 0;
        for (int i = 0; i < n; i++) {
            if (abs(r[i]) > max) {
                max = abs(r[i]);
            }
        }
        if (max < THRESHOLD) {
            break;
        }
    }
    delete[] r;
    delete[] xK;
    return;
}

void printSolution(double x[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "x" << i << "  " << x[i] << endl;
    }
}
