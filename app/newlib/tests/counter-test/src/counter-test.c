#include <stdio.h>
#include <riscv-csr.h>

int main()
{
    csr_write_mcountinhibit(-1); // -1 = inhibit all
    printf("Hello world!\n");

    csr_write_mcountinhibit( 0); // 0 = inhibit none
    printf("Hello world!\n");

    return 0;
}
