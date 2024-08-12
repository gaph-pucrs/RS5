#include <stdio.h>

#define HALT (*((volatile unsigned int*)0x80000000))
#define UART (*((volatile unsigned int*)0x80001000))

int main()
{
    printf("Hello World!\n");

    return 0;
}
