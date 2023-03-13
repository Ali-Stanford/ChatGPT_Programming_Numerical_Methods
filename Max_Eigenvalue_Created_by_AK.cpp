#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std ;

void MaxEval(double **a , int n){

	double eval = 0 ;
	double *v = new double[n] ;
	double *q = new double[n] ;
	for(int i = 0 ; i < n ; i ++)
		q[i] = rand() ;

	double sum = 0 ; 
	for(int i = 0 ; i < n ; i ++)
		sum += q[i]*q[i] ;

	for(int i = 0 ; i < n ; i ++)
		q[i] = q[i]/sqrt(sum) ;

	for(int k = 0 ; k < 100 ; k ++){
	
		for(int i = 0 ; i < n ; i++){
			double sum = 0 ; 
		
			for(int j =0 ; j < n ; j++)
				sum += a[i][j]*q[j] ;
			v[i] = sum ;	
		}

		double sum = 0 ; 
		for(int i = 0 ; i < n ; i++)
				sum += v[i]*q[i] ;
		
		if(abs(sum-eval) < pow(10.,-6.)){cout << sum << endl ; break ;}
	
		eval = sum ;	
		
		sum = 0 ; 
		for(int i = 0 ; i < n ; i ++)
			sum += v[i]*v[i] ;

		for(int i = 0 ; i < n ; i ++)
			q[i] = v[i]/sqrt(sum) ;
			
	}		
	return ;
}

int main(){
    
	// For example, consider matrix A
	int n = 3 ;
	double** a = new double*[n] ;
	for (int i = 0 ; i < n ; i++)
		a[i] = new double[n];

        // As an example, let's find the maximum eigenvalue of the following matrix
	a[0][0]=0; a[0][1]=-17; a[0][2]=21; 
	a[1][0]=0; a[1][1]=13; a[1][2]=-15; 
	a[2][0]=0; a[2][1]=10; a[2][2]=-12; 
	
	MaxEval(a , n);
	return 0;
}
