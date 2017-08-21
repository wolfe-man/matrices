// Copyright 2017, <Charles>

#include <iostream>
#include <cstdio>
#include <ctime>

#include "matrix.h"  // Code available at www.benvanvliet.com

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    int iterations = 10000;
    int ROWS = 10;
    int MAX = 10;
    std::srand(time(NULL));  // seed with time so it always changes

    for (int i = 0; i < iterations; ++i) {
        // code to benchmark
        try {
            Matrix A(ROWS, 2);
            Matrix b(ROWS, 1);
            // create 2d Matrix
            for (int i = 0; i < ROWS; ++i) {
                A(i, 0) = 1;
                A(i, 1) = std::rand() % MAX;
                b(0, i) = std::rand() % MAX;
            }

            (~A * A).Solve(~A * b);
            // std::cout << "Example Solution1:\n" << s1 << std::endl;
        }
        catch ( std::exception e ) {
            std::cout << e.what() << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast
                    <std::chrono::nanoseconds>(end-begin).count();
    std::cout << duration << "ns total, average : "
              << duration / iterations << "ns." << std::endl;
}
