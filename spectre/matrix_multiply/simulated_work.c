#include "simulated_work.h"

void initialize_matrices(){
	int i, j;
	for (i = 0; i < MSIZE; i++) {
		for (j = 0; j < MSIZE; j++) {
			matrix_a[i][j] = 1;
			matrix_b[i][j] = 1;
			matrix_r[i][j] = 0;
		}
	}
}

// This function multiplies mat1[][] and mat2[][],
// and stores the result in res[][]
void multiply_matrices(int mat1[][MSIZE], int mat2[][MSIZE], int res[][MSIZE]){
    int i, j, k;
    for (i = 0; i < MSIZE; i++)
    {
        for (j = 0; j < MSIZE; j++)
        {
            res[i][j] = 0;
            for (k = 0; k < MSIZE; k++)
                res[i][j] += mat1[i][k]*mat2[k][j];
        }
    }
}

void multiply(){
	//if(initialized==0){ initialize_matrices(); initialized=1; }
	multiply_matrices(matrix_a,matrix_b,matrix_r);
}

// find the transpose of mat
// store it in res
void transpose_matrices(int mat[][MSIZE], int res[][MSIZE]){
	for(int i=0; i<MSIZE; ++i)
		for(int j=0; j<MSIZE; ++j)
		{
			res[j][i] = mat[i][j];
		}
}

void transpose(){

}
