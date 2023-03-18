#include <stdio.h>

// 递归函数，用于计算阶乘
int factorial(int n) {
    // 基本情况：0的阶乘为1
    if (n == 0) {
        return 1;
    }

    // 递归步骤：n的阶乘等于n乘以(n-1)的阶乘
    return n * factorial(n - 1);
}

int main() {
    int number = 5;
    printf("The factorial of %d is: %d\n", number, factorial(number));
    return 0;
}
