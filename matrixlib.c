#include <stdio.h>
#include <stdlib.h>

// Define maximum dimensions for the matrices, won't allow higher matrices
#define MAX_ROWS 10
#define MAX_COLS 10

// Defining matrix structure with sizex and sizey as dimensions
typedef struct {

    int sizex, sizey;
    double **data;  // Dynamic memory allocation for matrix data, in case it's needed

} Matrix;

// Function to create a new matrix, init dimensions (sizex and sizey) and values
Matrix create_matrix(int sizex, int sizey, double *values) {
    Matrix matrix;
    matrix.sizex = sizex;
    matrix.sizey = sizey;



    // Will trigger if matrix is too big, in case any other data gets fed to it
    if (sizex > MAX_ROWS || sizey > MAX_COLS) {
        printf("ERROR: Matrix dimensions exceed the max size.\n");
        exit(1);
            }

    // Allocate memory dynamically, getting ready to populate the matrix
    matrix.data = (double **)malloc(sizex * sizeof(double *));
    

    //Allocates memory for Matrix data
    for (int i = 0; i < sizex; i++) {
        matrix.data[i] = (double *)malloc(sizey * sizeof(double));  
        }

    // Initialize the matrix, also populating with values
    int k = 0;
    for (int i = 0; i < sizex; i++) {
        for (int j = 0; j < sizey; j++) 
        {
            matrix.data[i][j] = values[k++];


        }

    }

    return matrix;
}

// Function to free the memory allocated for a matrix, this is because its using malloc
// Must have, and must call to avoid memory leaks
void free_matrix(Matrix *matrix) {
        for (int i = 0; i < matrix->sizex; i++) {
            free(matrix->data[i]);
        }

    free(matrix->data);
}

// Basically the readout function from the c++ program, just reads out all the data
void print_matrix(Matrix matrix) {
    printf("Matrix is %d rows by %d columns\n", matrix.sizex, matrix.sizey);
        for (int i = 0; i < matrix.sizex; i++) {
            for (int j = 0; j < matrix.sizey; j++) {
                printf("%.0f ", matrix.data[i][j]);
            }
            printf("\n");
        }
}

// Matrix addition function
Matrix add_matrices(Matrix a, Matrix b) {
    //Makes another matrix and allocates more memory to handle it
        Matrix result = create_matrix(a.sizex, a.sizey, (double *)malloc(a.sizex * a.sizey * sizeof(double)));
    for (int i = 0; i < a.sizex; i++) {
        for (int j = 0; j < a.sizey; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}
// Scalar multiplication function
Matrix scalar_multiply(Matrix a, double scalar) {
    
    //Makes result matrix and allocates memory for it
    Matrix result = create_matrix(a.sizex, a.sizey, (double *)malloc(a.sizex * a.sizey * sizeof(double)));
    for (int i = 0; i < a.sizex; i++) {
        for (int j = 0; j < a.sizey; j++) {
            result.data[i][j] = a.data[i][j] * scalar;
        }
    }
    return result;
}

// Transposition function
Matrix transpose(Matrix a) {
    Matrix result = create_matrix(a.sizey, a.sizex, (double *)malloc(a.sizey * a.sizex * sizeof(double)));
    //Flipping rows and columns 
    for (int i = 0; i < a.sizex; i++) {
        for (int j = 0; j < a.sizey; j++) {
            result.data[j][i] = a.data[i][j];
        }
    }
    //Returns result matrix here
    return result;
}

// Matrix multiplication, takes in two matrices to execute
Matrix multiply_matrices(Matrix a, Matrix b) {
    //Has to verify that the dimensions match, if not then cannot execute
    if (a.sizey != b.sizex) {
        printf("ERROR: Dimensions are not correct for multiplication.\n");
        exit(1);
    }

    //Init result matrix, go through data, multiply and add it all together
    Matrix result = create_matrix(a.sizex, b.sizey, (double *)malloc(a.sizex * b.sizey * sizeof(double)));
    for (int i = 0; i < a.sizex; i++) {
            for (int j = 0; j < b.sizey; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < a.sizey; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

int main() {
    
    //Matrix A
    double a_values[] = {6, 4, 8, 3};
    Matrix a = create_matrix(2, 2, a_values);
    // Matrix B
    double b_values[] = {1, 2, 3, 4, 5, 6};
    Matrix b = create_matrix(2, 3, b_values);
    // Matrix C
    double c_values[] = {2, 4, 6, 1, 3, 5};
    Matrix c = create_matrix(2, 3, c_values);

    // Transpose C
    Matrix ctranspose = transpose(c);
    // Scalar multiply B with 3
    Matrix threeb = scalar_multiply(b, 3);
    // B times c transpose
    Matrix threebtimesct = multiply_matrices(threeb, ctranspose);
    // Add A to that result
    Matrix result = add_matrices(a, threebtimesct);

    // Print the final result
    printf("\nMatrix D: ");
    print_matrix(result);

    // Free the allocated memory used to allocate the data above
    //Must be done to avoid memory leaks in C
    free_matrix(&a);
    free_matrix(&b);
    free_matrix(&c);
    free_matrix(&ctranspose);
    free_matrix(&threeb);
    free_matrix(&threebtimesct);
    free_matrix(&result);

    return 0;
}
