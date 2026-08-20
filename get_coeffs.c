#include <stdio.h>

int get_coeffs(float *pa, float *pb, float *pc)
{
    printf("Enter coefficients\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n");

    int res = scanf("%f %f %f", pa, pb, pc);
    return res != 0 && res != EOF;
}

int get_coeffs_from_equation(float *pa, float *pb, float *pc)
{
    printf("Enter quadratic equation\n");
    printf("Format: [a]x2 + [b]x + [c] = 0\n");
    printf("Example: 2x2 + 10x + 7 = 0\n");

    int res = scanf("%fx2 + %fx + %f = 0", pa, pb, pc);
    return res != 0 && res != EOF;
}