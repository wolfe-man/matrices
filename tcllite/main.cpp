// Copyright 2017, <Charles>

#include <iostream>
#include <cstdio>
#include <ctime>

#include "matrix.h"  // Code available at www.benvanvliet.com

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    int iterations = 10000;

    for (int i = 0; i < iterations; ++i) {
        // code to benchmark
        try {
            Matrix a(3, 2);
            a(0, 0) = 1;
            a(0, 1) = 0;
            a(1, 0) = 1;
            a(1, 1) = 1;
            a(2, 0) = 1;
            a(2, 1) = 2;
            // std::cout << "A= \n" << a << std::endl;

            Matrix b(3, 1);
            b(0, 0)= 6;
            b(0, 1)= 0;
            b(0, 2)= 0;
            // std::cout << "b= \n" << b << std::endl;

            (~a * a).Solve(~a * b);
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
