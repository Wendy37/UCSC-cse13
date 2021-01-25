#include "mathlib.h"

#include <math.h>
#include <stdio.h>

#define EPSILON 1e-14 // 0 * 10^(-14)

static inline double Abs(double x) {
    return x < 0 ? -x : x;
}

double Sin(double x) {
    double result = 0.0;
    double old = x;
    double denominator;
    for (int i = 1; i < 25; i++) {
        denominator = (2 * i) * (2 * i + 1);
        result += old;
        old *= (-x * x) / denominator;
    }
    return result;
}

double Cos(double x) {
    double result = 0.0;
    double old = 1.0;
    double denominator;
    for (int i = 1; i < 25; i++) {
        denominator = (2 * i - 1) * (2 * i);
        result += old;
        old *= (-x * x) / denominator;
    }

    return result;
}

double Tan(double x) {
    if (Cos(x) == 0 * EPSILON) {
        printf("undefine");
        return 0.0;
    }
    double result = Sin(x) / Cos(x);
    return result;
}

double Exp(double x) {
    double result = 0.0;
    int index = 1;
    long double old = 1.0;
    while (fabsl(old) > EPSILON) {
        result += old;
        old *= x / index;
        index++;
    }
    return result;
}

double Log(double x) {
    double y = 1.0;
    double exp = Exp(y);
    while (Abs(x - exp) > EPSILON) {
        y += (x - exp) / exp;
        exp = Exp(y);
    }
    return y;
}
// Cite program [Log(double x)] from the PowerPoint "Numerical Computation" --
// slide 16, made by Professor Long.
