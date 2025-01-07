#define PRINTI (*((volatile unsigned int*)0x80002000))

int fibonacci(int n)
{
    if (n <= 1)
        return n;

    int current = 0;
    int prev1   = 1;
    int prev2   = 0;

    for (int i = 2; i <= n; i++) {
        __asm__ (
            "add %0, %1, %2\n"
            "mv  %2, %1\n"
            "mv  %1, %0\n"
            : "+r"(current), "+r"(prev1), "+r"(prev2)
            :
            :
        );
    }

    return current;
}

void main()
{
    volatile int value = 5;
    int ret = fibonacci(value);
    PRINTI = ret;
    return;
}
