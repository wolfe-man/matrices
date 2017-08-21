// Copyright 2017, <Eigen3>

#include <iostream>

#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int main() {

    auto begin = std::chrono::high_resolution_clock::now();
    int ITERATIONS = 10000;
    int MAX = 10000;
    std::srand(time(NULL));  // seed with time so it always changes

    for (int i = 0; i < ITERATIONS; ++i) {
        // code to benchmark
        try {
            MatrixXd A(MAX, 2);
            VectorXd b(MAX);
            // create 2d Matrix
            for (int i = 0; i < MAX; ++i) {
                A(i, 0) = std::rand() % MAX;
                A(i, 1) = std::rand() % MAX;
                b(i) = std::rand() % MAX;
            }

            (A.transpose() * A).ldlt().solve(A.transpose() * b);

            //A.colPivHouseholderQr().solve(b);
            // std::cout << "Here is the right hand side b:\n" << b << std::endl;
            // std::cout << "The least-squares solution is:\n"
            //           << A.jacobiSvd(Eigen::ComputeThinU |
            //                          Eigen::ComputeThinV).solve(b) << std::endl;

            // std::cout << "The solution using the QR decomposition is:\n"
            //           << A.colPivHouseholderQr().solve(b) << std::endl;

            // std::cout << "The solution using normal equations is:\n"
            //           << (A.transpose() * A).ldlt().solve(A.transpose() * b)
            //           << std::endl;
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
