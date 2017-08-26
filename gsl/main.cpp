// Copyright 2017, <Charles>

#include <iostream>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>

using namespace std;

int main(int argc, char *argv[]) {

    auto begin = std::chrono::high_resolution_clock::now();
    int ITERATIONS = 10000;
    int ROWS = 10;
    int MAX = 10;
    std::srand(time(NULL));  // seed with time so it always changes

    for (int i = 0; i < ITERATIONS; ++i) {
        // code to benchmark
        try {
            gsl_matrix * a = gsl_matrix_alloc(ROWS, 2);
            gsl_vector * b = gsl_vector_alloc(ROWS);

            // Create A and b
            for (int i = 0; i < ROWS; i++) {
                gsl_matrix_set(a, i, 0, std::rand() % MAX);
                gsl_matrix_set(a, i, 1, std::rand() % MAX);
                gsl_vector_set(b, i, std::rand() % MAX);
            }

            gsl_vector * aTb = gsl_vector_alloc(2);
            gsl_blas_dgemv(CblasTrans, 1, a, b, 0, aTb);

            // aTa
            gsl_matrix * aTa = gsl_matrix_alloc(2, 2);
            gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1, a, a, 0, aTa);

            // SOLVE
            gsl_vector * x = gsl_vector_alloc(2);
            int s;
            gsl_permutation * p = gsl_permutation_alloc(2);
            gsl_linalg_LU_decomp(aTa, p, &s);
            gsl_linalg_LU_solve(aTa, p, aTb, x);

            /*
              printf ("x = \n");  // LEAST SQUARES ANSWER
              gsl_vector_fprintf (stdout, x, "%g");
            */
        }
        catch ( std::exception e ) {
            std::cout << e.what() << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast
                    <std::chrono::nanoseconds>(end-begin).count();
    std::cout << duration << "ns total, average : "
              << duration / ITERATIONS << "ns." << std::endl;


    return 0;
}
