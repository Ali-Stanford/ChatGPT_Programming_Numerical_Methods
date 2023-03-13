#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std ;

void Tridiagonal(int n, double a[], double b[], double c[], double d[], double x[]){

	for(int i = 1 ; i < n ; i ++){
	
		b[i] = b[i] - (a[i]/b[i-1])*c[i-1] ; 
		d[i] = d[i] - (a[i]/b[i-1])*d[i-1] ;
	}

	x[n-1] = d[n-1]/b[n-1] ;
	cout << "x"<< n << "  " << x[n-1] << endl ;

	for(int i = n - 2; i > -1 ; i --){
	}

	return ;
}

int main(){
 
	int n = 4 ;
	double *a, *b, *c, *d, *x ;
	a = new double[n] ;
	b = new double[n] ;
	c = new double[n] ;
	d = new double[n] ;
	x = new double[n] ;

	for(int i = 0 ; i < n ; i ++)
		x[i] = 0 ;

	a[0] = 0. ;
	c[n-1] = 0. ; 

	// As an example
	// Please look at the wiki-page for the definition of a[] b[] c[] d[]
	a[1] = a[2] = a[3] = -1 ;
	c[0] = c[1] = c[2] = -1 ;
	b[0] = b[1] = b[2] = b[3] = 2 ;
	d[0] = d[1] = d[2] = d[3] = 1 ;

	Tridiagonal(n, a, b, c, d, x) ;
	return 0;
}
