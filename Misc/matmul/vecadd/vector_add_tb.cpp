#include "vector_add.h"
#include <iostream>

#define SIZE 16

int main() {
    int a[SIZE], b[SIZE], c[SIZE];

    for(int i=0; i<SIZE; ++i) {
        a[i] = i;
        b[i] = i*2;
    }

    vector_add(a, b, c, SIZE);

    bool success = true;
    for(int i=0; i<SIZE; ++i) {
        int expected = a[i] + b[i];
        std::cout << "c[" << i << "] = " << c[i] << ", expected: " << expected << std::endl;
        if(c[i] != expected) {
            success=false;
        }
    }

    if(success) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }

    return success ? 0 : 1;
}
