
// Dynamic programming for 0/1 knapsack
// (C) Joshua Knowles
// The variable names here follow standard usage in formulating
// dynamic programming via recursive definitions

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // list of temporary item indexes for sorting items by value/weight
int QUIET=1; // this can be set to 1 to suppress output


// function prototypes
extern void read_knapsack_instance(char *filename);
int DP(int *v,int *wv, int n, int W, int *solution);
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);

int main(int argc, char *argv[1])
{
  int *solution;    // binary vector indicating items to pack
  int total_value, total_weight;  // total value and total weight of items packed
  
  read_knapsack_instance(argv[1]);

  if((solution = (int *)malloc((Nitems+1)*sizeof(int)))==NULL)
    {      
      fprintf(stderr,"Problem allocating table for DP\n");
      exit(1);
    }

  DP(item_values,item_weights,Nitems,Capacity,solution);
  check_evaluate_and_print_sol(solution,&total_weight,&total_value);
  return(0);
}

int Max(int a, int b) {
    return a > b ? a : b;
}
 
int DP(int *v,int *wv, int n, int W, int *solution){
  // the dynamic programming function for the knapsack problem
  // the code was adapted from p17 of http://www.es.ele.tue.nl/education/5MC10/solutions/knapsack.pdf

  // v array holds the values / profits / benefits of the items
  // wv array holds the sizes / weights of the items
  // n is the total number of items
  // W is the constraint (the weight capacity of the knapsack)
  // solution: a 1 in position n means pack item number n+1. A zero means do not pack it.

  	int **V, **keep;  // 2d arrays for use in the dynamic programming solution
  // keep[][] and V[][] are both of size (n+1)*(W+1)

  // Dynamically allocate memory for variables V and keep
  /* ADD CODE HERE */
  	int i, j, k;  // for loops and show results
	V = (int**)malloc(sizeof(int*) * (n+1));  // allocate the memory space of n+1 rows for int* in V[][]
	keep = (int**)malloc(sizeof(int*) * (W+1));  // allocate the memory space of W+1 columns for int* in keep[][]
  	for (i = 0; i<=n; i++) {
      	V[i] = (int*)calloc((W+1), sizeof(int));  // allocate the memory space of W+1 columns for int in V[][]
  	}
  	for (i = 0; i<=W; i++) {
      	keep[i] = (int*)calloc((n+1), sizeof(int));  // allocate the memory space of n+1 rows for int in keep[][]
  	}
 
 //  set the values of the zeroth row of the partial solutions table to zero
  /* ADD CODE HERE */
  	for(i = 1; i<=n; i++)  // initialize the solution like the "00...00"
        solution[i] = 0;  
    
    for(i = 0; i <=W; i++)
        V[0][i] = 0;  // zeroth row was initialized as the zero satisfying requirements

 // main dynamic programming loops , adding one item at a time and looping through weights from 0 to W
  /* ADD CODE HERE */
	for(i = 1; i<=n; i++) {           // for:items
      	for(j = 0; j <= W; j++) {     // for:weight of knapsack
        	V[i][j] = V[i-1][j];  // the previous and temporary value, but the real value depended on whether the item could fit in the backpack
        	if(wv[i] <= j) {  // if the item could be contained in knapsack
            	V[i][j] = Max(V[i-1][j], V[i-1][j - wv[i]] + v[i]); // Max(situation1, situation2)
        	}
      	}
  	}

  // now discover which items were in the optimal solution
  /* ADD CODE HERE */
	k = W;  // knapsack capacity
	// backtrack from the bottom-right of the solution table to the top-left
    for(i = n;i >= 1; i--){  
		// if the value of first i items was equal to the first i-1 items,
		// the i-th item was actually not in the knapsack since there was no change on the total value
		// but if larger:
        if(V[i][k] > V[i-1][k]) {  
            solution[i] = 1;  // change the initial solution as "1" on the related position in the solution vector
            k -= wv[i];  // remove the weight of this contained item
        }
    }

  	return V[n][W];
}
