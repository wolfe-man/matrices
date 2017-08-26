// Copyright 2017, <Eigen3>

#include <iostream>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {

    auto begin = std::chrono::high_resolution_clock::now();
    int ITERATIONS = 10000;
    int ROWS = 10;
    int MAX = 10;
    std::srand(time(NULL));  // seed with time so it always changes

    for (int i = 0; i < ITERATIONS; ++i) {
        // code to benchmark
        try {
            MatrixXd A(ROWS, 2);
            VectorXd b(ROWS);
            // Create A and b
            for (int i = 0; i < ROWS; ++i) {
                A(i, 0) = 1;
                A(i, 1) = std::rand() % MAX;
                b(i) = std::rand() % MAX;
            }

            (A.transpose() * A).ldlt().solve(A.transpose() * b);
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
