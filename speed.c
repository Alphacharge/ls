#include <stdio.h>
#include <time.h>

void test_less_than() {
    clock_t start = clock();
    for (int j = 0; j < 1000000000; ++j) {
        for (int i = 0; i < 10; ++i) {
            if (i < 9) {
                // Do something
            }
        }
    }
    clock_t end = clock();
    printf("Time taken for i < 9: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void test_equal_to() {
    clock_t start = clock();
    for (int j = 0; j < 1000000000; ++j) {
        for (int i = 0; i < 10; ++i) {
            if (i == 8) {
                // Do something
            }
        }
    }
    clock_t end = clock();
    printf("Time taken for i == 8: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
}

int main() {
    test_less_than();
    test_equal_to();
    return 0;
}
