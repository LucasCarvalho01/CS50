#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    // typedef uint8_t  BYTE;
    typedef struct {
        int tmp;
    } Num;

    Num num1;
    num1.tmp = 1;

    Num num2;
    num2.tmp=2;

    Num num4;
    num4.tmp = 4;

    Num num0;
    num0.tmp = 0;

    Num num3;
    num3.tmp = 3;

    Num arr[] = {num0, num1, num2, num3, num4};

    int aux = 0;

    Num *ptr = malloc(sizeof(Num));
    ptr->tmp = 9;

    printf("%d\n", ptr->tmp);
}