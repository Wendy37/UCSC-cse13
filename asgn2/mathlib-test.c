#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctel"

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            printf("Run all tests.\n\n");
            printf("  x            Sin              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -2 * M_PI; i < 2 * M_PI; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Sin(i), sin(i), (Sin(i) - sin(i)));
            }
            printf("\n");
            printf("  x            Cos              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -2 * M_PI; i < 2 * M_PI; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Cos(i), cos(i), (Cos(i) - cos(i)));
            }
            printf("\n");
            printf("  x            Tan              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -M_PI / 3; i < M_PI / 3; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Tan(i), tan(i), (Tan(i) - tan(i)));
            }
            printf("\n");
            printf("  x            Exp              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = 1; i < 10; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Exp(i), exp(i), (Exp(i) - exp(i)));
            }
            printf("\n");
            printf("  x            Log              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = 1; i < 10; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), (Log(i) - log(i)));
            }
            break;
        case 's':
            printf("Run sin tests.\n");
            printf("  x            Sin              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -2 * M_PI; i < 2 * M_PI; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Sin(i), sin(i), (Sin(i) - sin(i)));
            }
            break;
        case 'c':
            printf("Run cos tests.\n");
            printf("  x            Cos              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -2 * M_PI; i < 2 * M_PI; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Cos(i), cos(i), (Cos(i) - cos(i)));
            }
            break;
        case 't':
            printf("Run tan tests.\n");
            printf("  x            Tan              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = -M_PI / 3; i < M_PI / 3; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Tan(i), tan(i), (Tan(i) - tan(i)));
            }
            break;
        case 'e':
            printf("Run exp tests.\n");
            printf("  x            Exp              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = 1; i < 10.0; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Exp(i), exp(i), (Exp(i) - exp(i)));
            }
            break;
        case 'l':
            printf("Run log tests.\n");
            printf("  x            Log              Library        Difference  \n");
            printf("  -            ---              -------        ----------  \n");
            for (double i = 1; i < 10.0; i += 0.1) {
                printf(
                    " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Log(i), log(i), (Log(i) - log(i)));
            }
            break;
        default: fprintf(stderr, "Usage: %s -[asctel]\n", argv[0]);
        }
    }
    return 0;
}
