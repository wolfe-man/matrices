// Copyright 2017, <Charles>

#include <iostream>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>

using namespace std;

int main(int argc, char *argv[]) {
    int i;
    gsl_vector * v = gsl_vector_alloc (100);

    for (i = 0; i < 100; i++)
    {
        gsl_vector_set (v, i, 1.23 + i);
    }

    gsl_vector * w = gsl_vector_alloc (100);

    gsl_vector_memcpy(w, v);
    gsl_vector_add(w, v);

    cout << gsl_vector_get(w, 1) << "\n";
    cout << gsl_vector_max(w) << "\n";
    cout << gsl_vector_min(w) << "\n";


    gsl_vector_free (v);
    gsl_vector_free (w);


    gsl_matrix * m = gsl_matrix_alloc (100, 100);

    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            gsl_matrix_set (m, i, j, 0.23 + i + j);

    gsl_matrix * mT = gsl_matrix_alloc (100, 100);

    gsl_matrix_transpose_memcpy(mT, m);

    cout << gsl_matrix_get(m, 49, 49) << "\n";
    cout << gsl_matrix_get(m, 99, 0) << "\n";

    cout << gsl_matrix_get(mT, 49, 49) << "\n";
    cout << gsl_matrix_get(mT, 99, 0) << "\n";

    cout << gsl_matrix_max(m) << "\n";
    cout << gsl_matrix_min(m) << "\n";

    return 0;
}
