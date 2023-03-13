#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <omp.h>

using namespace std;

void MaxEval(double **a, int n){

    double eval = 0;
    double *v = new double[n];
    double *q = new double[n];
    for(int i = 0; i < n; i++)
        q[i] = rand();

    double sum = 0;
    for(int i = 0; i < n; i++)
        sum += q[i] * q[i];

    for(int i = 0; i < n; i++)
        q[i] = q[i] / sqrt(sum);

    #pragma omp parallel
    {
        double* local_v = new double[n];
        double* local_q = new double[n];
        double local_sum = 0;
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        for(int k = 0; k < 100; k++){
            #pragma omp for
            for(int i = 0; i < n; i++){
                double sum = 0;
                for(int j = 0; j < n; j++)
                    sum += a[i][j] * q[j];
                local_v[i] = sum;
            }

            #pragma omp barrier

            #pragma omp for reduction(+:local_sum)
            for(int i = 0; i < n; i++)
                local_sum += local_v[i] * q[i];

            #pragma omp critical
            {
                eval += local_sum;
            }

            #pragma omp single
            {
                double diff = fabs(local_sum - eval);
                if(diff < pow(10., -6.)){
                    cout << eval << endl;
                    break;
                }
                eval = local_sum;
                local_sum = 0;
            }

            #pragma omp barrier

            #pragma omp for reduction(+:local_sum)
            for(int i = 0; i < n; i++)
                local_sum += local_v[i] * local_v[i];

            #pragma omp for
            for(int i = 0; i < n; i++)
                local_q[i] = local_v[i] / sqrt(local_sum);

            #pragma omp for
            for(int i = 0; i < n; i++)
                q[i] = local_q[i];
        }

        delete[] local_v;
        delete[] local_q;
    }
    delete[] v;
    delete[] q;
}

int main(){

    int n = 3;
    double** a = new double*[n];
    for(int i = 0; i < n; i++)
        a[i] = new double[n];

    a[0][0] = 0; a[0][1] = -17; a[0][2] = 21;
    a[1][0] = 0; a[1][1] = 13; a[1][2] = -15;
    a[2][0] = 0; a[2][1] = 10; a[2][2] = -12;

    MaxEval(a, n);

    for(int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
