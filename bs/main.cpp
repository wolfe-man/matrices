// Copyright <2017>, Charles

#include <iostream>
#include <cstdio>
#include <ctime>

#include "matrix.h"
#include "matrixio.h"

using Numeric_lib::Index;

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;

void classical_elimination(Matrix& A, Vector& b) {
    const Index n = A.dim1();

    // traverse from 1st column to the next-to-last filling zeros into all
    // elements under the diagonal
    for (Index j = 0; j < n-1; ++j) {
        const double pivot = A(j, j);

        // fill zeros into each element under the diagonal of the ith row
        for (Index i = j+1; i < n; ++i) {
            const double mult = A(i, j) / pivot;
            A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
            b(i) -= mult * b(j);    // make the corresponding change to b
        }
    }
}

Vector back_substitution(Matrix& A, Vector& b) {
    const Index n = A.dim1();
    Vector x(n);

    for (Index i = n-1; i >= 0; --i) {
        double s = b(i) - dot_product(A[i].slice(i+1), x.slice(i+1));

        double m = A(i, i);
        x(i) = s / m;
        b(i) = x(i);
        A(i, i) = 1;
        A[i].slice(i+1) = scale_and_add(A[i].slice(i+1), -1.0, A[i].slice(i+1));
    }
    return x;
}

Vector classical_gaussian_elimination(Matrix A, Vector b) {
    classical_elimination(A,b);
    return back_substitution(A,b);
}

Matrix transpose(Matrix A) {
    Matrix temp(A.dim2(), A.dim1());
    for (int i = 0; i < A.dim1(); ++i) {
        for (int j = 0; j < A.dim2(); ++j) {
            temp(j, i) = A(i, j);
        }
    }

    return temp;
}

Vector multiply_mv(Matrix A, Vector b)
{
    const Index n = A.dim1();
    Vector x(n);

    for (int i = 0; i < A.dim1(); ++i) {
        x[i] = dot_product(A[i], b);
    }
    return x;
}

Matrix multiply_mm(Matrix l, Matrix r)
{
    Matrix temp(l.dim1(), r.dim2());
    int sum = 0;
    for (int i = 0; i < l.dim1(); ++i) {
        for (int j = 0; j < r.dim2(); ++j) {
            sum = 0;
            for (int x = 0; x < l.dim2(); ++x) {
                sum += l[i][x] * r[x][j];
            }
            temp(i, j) = sum;
        }
    }
    return temp;
}

//------------------------------------------------------------------------------

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    int iterations = 1;
    int ROWS = 10;
    int MAX = 10;
    std::srand(time(NULL));  // seed with time so it always changes

    for (int i = 0; i < iterations; ++i) {
        // code to benchmark
        try
        {
            Matrix A(ROWS, 2);
            Vector b(ROWS);
            for (int i = 0; i < ROWS; ++i) {
                A(i, 0) = 1;
                A(i, 1) = std::rand() % MAX;
                b(i) = std::rand() % MAX;
            }
            classical_gaussian_elimination(
                multiply_mm(transpose(A), A),
                multiply_mv(transpose(A), b));
            /*
              cout << "x:\n" << classical_gaussian_elimination(
              multiply_mm(transpose(A), A), multiply_mv(transpose(A), b))
              << '\n';
            */

        }
        catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << '\n';
        }
        catch (...) {
            std::cerr << "Exception\n";
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast
                    <std::chrono::nanoseconds>(end-begin).count();
    std::cout << duration << "ns total, average : "
              << duration / iterations << "ns." << std::endl;
}
