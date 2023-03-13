#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std ;
	
void CSR(double **a , int n){

        double *V_k_aa ;
	int *V_k_ai , *V_k_aj ;
	int V_k_non_zeros_elements ;
	V_k_non_zeros_elements = 0 ;

    	for (int i = 0 ; i < n ; i ++){
		for (int j = 0 ; j < n ; j++){
			if(a[i][j] != 0.0 ){V_k_non_zeros_elements ++ ;}
		}
	}
	
	V_k_aa = new double[V_k_non_zeros_elements] ;
	V_k_ai = new int[V_k_non_zeros_elements] ;
	V_k_aj = new int[n + 1] ;
	V_k_aj[0] = 0 ;

	int alarm = 0 ;
	int counter = 0 ;

	for (int i = 0 ; i < n ; i ++){
		for (int j = 0 ; j < n ; j ++){
			
			if(a[i][j] != 0 ){
				alarm ++ ;
				V_k_aa[counter] = a[i][j] ; 
				if (alarm == 1) V_k_aj[i] = counter ;
				V_k_ai[counter] = j ; counter ++ ;
			}
		}
		alarm = 0 ;
	}

	V_k_aj[n] = V_k_non_zeros_elements ;
	
	//print the results
	cout << "Array of non zero elements:" << endl ;
	for(int i=0; i<V_k_non_zeros_elements; i++)
	    cout << V_k_aa[i] << endl ;
	cout << endl;
	    
	cout << "Array of column indices:" << endl ;
	for(int i=0; i<V_k_non_zeros_elements; i++)
	    cout << V_k_ai [i] << endl ; 
	cout << endl;
	
	cout << "Array of row indices :" << endl ;
	for(int i=0; i<n+1; i++)
	    cout << V_k_aj[i] << endl ; 

	return ;
}

int main(){
    
        // As an example
	int n = 4;
	double** a = new double*[n] ;
	for (int i = 0 ; i < n ; i++)
		a[i] = new double[n];

        // matrix A
	a[0][0]=5; a[0][1]=0; a[0][2]=0 ; a[0][3]=0 ;
	a[1][0]=0 ; a[1][1]=8 ; a[1][2]=0 ; a[1][3]=0 ;
	a[2][0]=0 ; a[2][1]=0 ; a[2][2]=3 ; a[2][3]=0 ;
	a[3][0]=0 ; a[3][1]=6 ; a[3][2]=0 ; a[3][3]=0 ;

	CSR(a,n) ;

	return 0;
}
