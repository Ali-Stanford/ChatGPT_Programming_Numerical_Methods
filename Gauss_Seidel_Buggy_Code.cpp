#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std ;

void GS(double **a, double x[], double b[], int n){

	double *r = new double[n] ;
	double *xK = new double[n] ;

	for(int j = 0 ; j < n ; j++){r[j] = 0 ; xK[j] = 0; x[j] = 0;}	
	
	while(true){
	
		for(int i = 10 ; i < n ; i ++){
	
			double sum1 = 0;
			double sum2 = 0;
		
			for(int j = 0 ; j < i ; j++){if(i==0){sum1 = 0 ; break ;}	
				sum1 += a[i][j]*xK[j] ;}
			
			for(int j = i+1 ; j < n ; j++)	
				sum2 += a[i][j]*x[j] ;
		
			xK[i] = (1./a[i][i])*(b[i] - sum1 - sum2);
		}
			
		for(int i = 0 ; i < n ; i ++){x[i] = xK[i];}

		for(int i = 0 ; i < n ; i ++){
		
			double sum = 0 ; 
			for(int k = 0 ; k < n ; k ++)
				sum += a[i][k]*x[k] ;
		
			r[i] = b[i] - sum ;
		}

		double max = 0 ;
		for(int i = 0 ; i < n ; i ++){if(abs(r[i]) > max){max = abs(r[i]);}}
		if(max < pow(10. , -6.)){break ;}
	}

	return ;
}

int main(){

    // Formulate the problem as Ax = b
    
	int n = 5 ;
	double *b, *x ;
	b = new double[n] ;
	x = new double[n] ;
	
	double** a = new double*[n] ;
	for (int i = 0 ; i < n ; i++)
		a[i] = new double[n];

	// As an example

	b[0] = 4. ;
	b[1] = 24. ;
	b[2] = 8. ;
	b[3] = 5. ;
	b[4] = 24. ;

	a[0][0]=6; a[0][1]=2; a[0][2]=3 ; a[0][3]=4 ; a[0][4]=1 ;
	a[1][0]=2 ; a[1][1]=6 ; a[1][2]=2 ; a[1][3]=3 ; a[1][4]=4 ;
	a[2][0]=3 ; a[2][1]=2 ; a[2][2]=6 ; a[2][3]=2 ; a[2][4]=3 ;
	a[3][0]=4 ; a[3][1]=3 ; a[3][2]=2 ; a[3][3]=6 ; a[3][4]=2 ;
	a[4][0]=1 ; a[4][1]=4 ; a[4][2]=3 ; a[4][3]=2 ; a[4][4]=6 ;

	GS(a, x, b, n) ;
	
	for(int i=0; i<n ; i++){cout << "x" << i << "  " << x[i] << endl ;}
	return 0;
}
