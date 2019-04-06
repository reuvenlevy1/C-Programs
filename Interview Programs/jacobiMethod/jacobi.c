#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

/**
 * Uses the Jacobi method (A*x = b) with a randomized array of numbers to locate the vector x.
 *
 * Definition:
 * Jacobi Method - An iterative algorithm for determining the solutions of a diagonally dominant
 * system of linear equations.
 *
 * Run by passing in 2 command line arguments: the number of iterations and the margin of error.
 * Ex:
 * 5 0.0001
 * 10 0.000001
 *
 * @author Reuven
 */

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();

float a[N][N], b[N];
float x[N], buf[N];
int n;
float error;

int main(int argc, char **argv){
	n = atoi(argv[1]);
	error = atof(argv[2]);				/* error threshold; tolerance */
	init();		   						/* initialize a, x0 and b */
	int n_iter = jacobi();				/* number of iterations */
	print_vector(x);					/* prints entire matrix of values */
	return 0;
}

int jacobi(){
	int i, j, k;
	float sum;
	k = 0;

	while (!convergence() && k < MAX_ITER){
		for (i = 0; i < n; i++){
			sum = 0.0;
			
			for (j = 0; j < n; j++){
				if (i != j){
					sum += (a[i][j] * x[j]);
				}
			}
			buf[i] = (b[i] - sum) / a[i][i];
		}

		for (i = 0; i < n; i++){
			x[i] = buf[i];
		}
		k++;
	}
	return k;
}

/* returns 1 if converged else 0 */
int convergence(int iter){
	int i, j, flag = 1;
	float sum;
	
	for (i = 0; i < n; i++){
		sum = 0.0;
		
		for (j = 0; j < n; j++){
			sum += (a[i][j] * x[j]);
		}
		buf[i] = (b[i] - sum);
		
		if (fabs(buf[i]) >= error){
			flag = 0;
			return flag;
		}
	}
	return flag;
}

void init(char **argv){
	int i, j, flag = 0;
	float sum;
	int seed = time(0) % 100;			/* seconds since 1/1/1970 */
	srand(seed);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			a[i][j] = rand() & 0x7;
			if (rand() & 0x1) a[i][j] = -a[i][j];
		}
		sum = 0;
		
		for (j = 0; j < n; j++) if(i != j) sum = sum + abs(a[i][j]);
			if (a[i][i] < sum) a[i][i] = sum + a[i][i];
	}

	for (i = 0; i < n; i++){
		x[i] = 1;
	}
	srand(seed);
	
	for (i = 0; i < n; i++){
		b[i] = rand() & 0x7;
		
		if (rand() & 0x1) b[i] = -b[i];
	}
	print_equation();
}

void print_equation(){
	int i, j;
	printf("A*x=b\n");
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) printf("%2d ", (int)(a[i][j]));
		printf(" * x%d = %d\n", i, (int)(b[i]));
	}
	printf("\n");
}

void print_vector(float *l){
	int i;
	printf("Vectors: ");
	
	for (i = 0; i < n; i++) printf("[x%d]%.6f ", i, l[i]);
	printf("\n");
}
