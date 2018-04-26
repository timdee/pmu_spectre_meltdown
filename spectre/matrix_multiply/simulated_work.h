#ifndef SIMULATED_WORK_H
#define SIMULATED_WORK_H

#define MSIZE 100
static int initialized=0;
static int matrix_a[MSIZE][MSIZE],matrix_b[MSIZE][MSIZE],matrix_r[MSIZE][MSIZE];

void initialize_matrices();
void multiply_matrices(int mat1[][MSIZE], int mat2[][MSIZE], int res[][MSIZE]);
void transpose_matrices(int mat[][MSIZE], int res[][MSIZE]);
void multiply();
void transpose();

//TODO implement transpose_matrices

#endif
