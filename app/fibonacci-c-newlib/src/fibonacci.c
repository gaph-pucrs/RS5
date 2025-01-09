#include <stdio.h>

int fibonacci(int n)
{
    if (n <= 1)
        return n;

    int current = 0;
    int prev1   = 1;
    int prev2   = 0;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2   = prev1;
        prev1   = current;
    }

    return current;
}

int main()
{
    volatile int value = 5;
    int ret = fibonacci(value);
    printf("%d\n", ret);
    return 0;
}
