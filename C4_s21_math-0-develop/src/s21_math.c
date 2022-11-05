#include "s21_math.h"

int s21_abs(int x) { return x > 0 ? x : -x; }

long double s21_acos(double x) {
  long double result;
  if (x < -1 || x > 1)
    result = S21_NAN;
  else if (s21_fabs(x - 1.) < S21_EPS)
    result = 0;
  else if (s21_fabs(x + 1.) < S21_EPS)
    result = S21_PI;
  else
    result = (S21_PI / 2 - s21_asin(x));
  return result;
}

long double s21_asin(double x) {
  long double result = x;
  long double temp = x;
  if (x > 1 || x < -1) {
    result = S21_NAN;
  } else if (s21_fabs(x) == 1) {
    result = S21_PI / 2 * x;
  } else {
    long double n = 1.;
    while (s21_fabs(temp) > S21_EPS) {
      temp *= ((x * x) * (2 * n - 1) * (2 * n - 1)) / ((2 * n) * (2 * n + 1));
      result += temp;
      n++;
    }
  }
  return result;
}

long double s21_atan(double x) {
  long double res;
  if (x == S21_INFINITY) {
    res = S21_PI / 2;
  } else if (x == -S21_INFINITY) {
    res = -S21_PI / 2;
  } else if (x != 0 && x == x) {
    res = s21_asin(x / s21_sqrt(x * x + 1));
  } else {
    res = x;
  }
  return res;
}

long double s21_ceil(double x) {
  long double res;
  if (x == S21_INFINITY || x == -S21_INFINITY || x != x) {
    res = x;
  } else {
    if (x != (int)x) {
      if (x > 0.0) {
        res = (int)x + 1;
      } else if (x < 0.0 && x > -1.0) {
        res = -0.0;
      } else {
        res = (int)x;
      }
    } else {
      res = x;
    }
  }
  return res;
}

long double s21_cos(double x) {
  if (x < -S21_PI || x > S21_PI) x = s21_fmod(x, 2 * S21_PI);
  long double temp = x, result = 1;
  double n = 2.;
  int znak = -1;
  while (s21_fabs(temp) > S21_EPS) {
    temp = znak * (s21_pow(x, n) / (factorial(n)));
    n += 2.;
    result += temp;
    znak *= -1;
  }
  return result;
}

long double s21_fabs(double x) { return (x < 0.0) ? x *= -1 : x; }

long double s21_floor(double x) {
  long double res;
  if (x == S21_INFINITY || x == -S21_INFINITY || x != x) {
    res = x;
  } else {
    if (x != (int)x) {
      if (x > 0.0) {
        res = (int)x;
      } else {
        res = (int)x - 1;
      }
    } else {
      res = x;
    }
  }
  return res;
}

long double s21_fmod(double x, double y) {
  long double result;
  if (y == 0.0 || x == S21_INFINITY || x == -S21_INFINITY) {
    result = S21_NAN;
  } else if (y == S21_INFINITY || y == -S21_INFINITY) {
    result = x;
  } else {
    result = x - (((long int)(x / y)) * y);
  }
  return result;
}

long double s21_sin(double x) {
  if (x < -S21_PI || x > S21_PI) {
    x = s21_fmod(x, 2 * S21_PI);
  }
  long double temp = x, result = x;
  double n = 3.;
  int znak = -1;
  while (s21_fabs(temp) > S21_EPS) {
    temp = znak * (s21_pow(x, n) / (factorial(n)));
    n += 2.;
    result += temp;
    znak *= -1;
  }
  return result;
}

long double factorial(long double n) {
  long double result = 1.;
  for (int i = 1; i <= n; i++) {
    result = result * i;
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = x / 2;
  if (x < 0) {
    result = -S21_NAN;
  } else if (x == S21_INFINITY) {
    result = S21_INFINITY;
  } else {
    long double temp = 0;
    while (s21_fabs(result - temp) > S21_EPS) {
      temp = result;
      result = (temp + x / temp) / 2;
    }
  }
  return result;
}

long double s21_tan(double x) { return s21_sin(x) / s21_cos(x); }

long double s21_pow(double base, double exp) {
  long double res;
  if (base != base || exp != exp) {
    res = S21_NAN;
  } else if (exp == 0) {
    res = 1.0;
  } else if (exp == S21_INFINITY) {
    res = exp;
  } else if (exp == -S21_INFINITY || base == 0) {
    res = 0.0;
  } else if (base == -S21_INFINITY && exp == (long int)exp &&
             (long int)exp % 2 == 1) {
    res = -S21_INFINITY;
  } else if (s21_fabs(base) == S21_INFINITY) {
    res = S21_INFINITY;
  } else if (base == 1) {
    res = 1.0;
  } else if (base < 0) {
    if ((long int)exp == exp) {
      if (exp > 0) {
        res = base;
        for (long int i = 0; i < (long int)exp - 1; i++) res *= base;
      } else {
        res = 1 / base;
        for (long int i = 0; i < (long int)exp * (-1) - 1; i++) res /= base;
      }
    } else {
      res = S21_NAN;
    }
  } else {
    if ((long int)exp == exp) {
      if (exp > 0) {
        res = base;
        for (long int i = 0; i < (long int)exp - 1; i++) res *= base;
      } else {
        res = 1 / base;
        for (long int i = 0; i < (long int)exp * (-1) - 1; i++) res /= base;
      }
    } else {
      res = s21_exp(exp * (double)s21_log(base));
    }
  }
  return res;
}

long double s21_exp(double x) {
  long double res;
  if (x > S21_EXP_MAX) {
    res = S21_INFINITY;
  } else if (x < S21_EXP_MIN) {
    res = 0.0;
  } else {
    res = 1;
    long double temp = 1., n = 1.;
    while (s21_fabs(temp) > S21_EPS) {
      temp = temp * x / n;
      res += temp;
      n++;
    }
  }
  return res;
}

long double s21_log(double x) {
  long double res;
  if (x <= 0.0) {
    res = S21_NAN;
  } else if (x == S21_INFINITY) {
    res = S21_INFINITY;
  } else if (x < 2.0 + S21_EPS) {
    long double temp = x - 1;
    long double n = 1.;
    res = 0;
    while (s21_fabs(temp) > S21_EPS) {
      res += temp;
      n++;
      temp = temp * (-1) * (x - 1) * (n - 1) / n;
    }
  } else {
    long double temp = x;
    res = 0;
    while (temp > 2) {
      temp /= 1.99;
      res += s21_log(1.99);
    }
    res += s21_log(temp);
  }
  return res;
}
