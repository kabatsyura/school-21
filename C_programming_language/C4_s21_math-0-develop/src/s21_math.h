#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_E 2.7182818284590452353602874713527
#define S21_NAN 0.0 / 0.0
#define S21_INFINITY 1.0 / 0.0
#define S21_EPS 1e-17
#define S21_PI 3.14159265358979323846264338327950288
#define S21_LN10 2.30258509299404590109
#define S21_EXP_MAX 709.7827
#define S21_EXP_MIN -708.3964

#include <limits.h>

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

long double factorial(long double n);

#endif  // SRC_S21_MATH_H_
