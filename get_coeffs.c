#include <stdio.h>

void get_coeffs_in_loop(float *pa, float *pb, float *pc, int (*pfunction)(float *pa, float *pb, float *pc))
{
    int parsing_status = 0;

    while (1)
    {
        parsing_status = (*pfunction)(pa, pb, pc);
        if (parsing_status)
            return;
        while (getchar() != '\n')
            ;
        printf("Enter correct coefficients!\n\n");
    }
}

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