#include <stdio.h>

int get_coeffs(float *pa, float *pb, float *pc)
{
    printf("Enter coefficients:\n");
    printf("Input format shiould be\n");
    printf("%%a %%b %%c\n");

    int res = scanf("%f %f %f", pa, pb, pc);
    return res != 0 && res != EOF;
}