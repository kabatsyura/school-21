#include <check.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "s21_math.h"

START_TEST(s21_abs_test) {
  ck_assert_int_eq(s21_abs(5), abs(5));
  ck_assert_int_eq(s21_abs(-3), abs(-3));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(1), abs(1));
}
END_TEST

START_TEST(s21_acos_test) {
  ck_assert_ldouble_eq_tol(s21_acos(0), acosl(0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_acos(1), acosl(1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_acos(-1), acosl(-1), 1e-7);
  ck_assert_double_ne(s21_acos(INFINITY), acos(INFINITY));
  ck_assert_ldouble_eq_tol(s21_acos(0.777777), acosl(0.777777), 1e-7);
  ck_assert_ldouble_eq_tol(s21_acos(-0.27), acosl(-0.27), 1e-7);
  ck_assert_double_eq_tol(s21_acos(0.123456789987654321),
                          acosl(0.123456789987654321), 1e-7);
  ck_assert_double_eq_tol(s21_acos(-0.123456789987654321),
                          acosl(-0.123456789987654321), 1e-7);
}
END_TEST

START_TEST(s21_asin_test) {
  ck_assert_ldouble_eq_tol(s21_asin(1), asinl(1), 1e-7);
  ck_assert_double_ne(s21_asin(INFINITY), asin(INFINITY));
  ck_assert_ldouble_eq_tol(s21_asin(0.777777), asinl(0.777777), 1e-7);
  ck_assert_ldouble_eq_tol(s21_asin(-0.27), asinl(-0.27), 1e-7);
  ck_assert_double_eq_tol(s21_asin(0.123456789987654321),
                          asinl(0.123456789987654321), 1e-7);
  ck_assert_double_eq_tol(s21_asin(-0.123456789987654321),
                          asinl(-0.123456789987654321), 1e-7);
}
END_TEST

START_TEST(s21_atan_test) {
  ck_assert_ldouble_eq_tol(s21_atan(0), atanl(0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_atan(0.9), atanl(0.9), 1e-7);
  ck_assert_double_eq(s21_atan(INFINITY), atanl(INFINITY));
  ck_assert_double_eq(s21_atan(-INFINITY), atanl(-INFINITY));
  ck_assert_ldouble_eq_tol(s21_atan(-0.1), atanl(-0.1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_atan(3), atanl(3), 1e-7);
  ck_assert_ldouble_eq_tol(s21_atan(-5), atanl(-5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_atan(50), atanl(50), 1e-7);
}
END_TEST

START_TEST(s21_ceil_test) {
  ck_assert_ldouble_eq_tol(s21_ceil(-0.11), ceil(-0.11), 1e-7);
  ck_assert_ldouble_eq_tol(s21_ceil(0.0001), ceil(0.0001), 1e-7);
  ck_assert_ldouble_eq_tol(s21_ceil(1.), ceil(1.), 1e-7);
  ck_assert_ldouble_eq(s21_ceil(INFINITY), ceil(INFINITY));
  ck_assert_ldouble_eq(s21_ceil(-INFINITY), ceil(-INFINITY));
  ck_assert_ldouble_ne(s21_ceil(NAN), ceil(NAN));
  ck_assert_ldouble_eq_tol(s21_ceil(11.99), ceil(11.99), 1e-7);
  ck_assert_ldouble_eq_tol(s21_ceil(-15.55555), ceil(-15.55555), 1e-7);
}
END_TEST

START_TEST(s21_cos_test) {
  for (double test1 = -S21_PI; test1 <= S21_PI; test1 += 0.01)
    ck_assert_ldouble_eq_tol(s21_cos(test1), cosl(test1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_cos(123456), cosl(123456), 1e-7);
  ck_assert_ldouble_eq_tol(s21_cos(777777), cosl(777777), 1e-7);
  ck_assert_ldouble_eq_tol(s21_cos(944.27), cosl(944.27), 1e-7);
  ck_assert_ldouble_eq_tol(s21_cos(-944.27), cosl(-944.27), 1e-7);
}
END_TEST

START_TEST(s21_exp_test) {
  ck_assert_ldouble_eq_tol(s21_exp(0), exp(0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_exp(12.5), exp(12.5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_exp(-0.5), exp(-0.5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_exp(-30), expl(-30), 1e-7);
  ck_assert_ldouble_ne(s21_exp(S21_NAN), exp(S21_NAN));
  ck_assert_double_eq(s21_exp(S21_INFINITY), expl(S21_INFINITY));
  ck_assert_double_eq(s21_exp(-S21_INFINITY), expl(-S21_INFINITY));
}
END_TEST

START_TEST(s21_fabs_test) {
  ck_assert_ldouble_eq_tol(s21_fabs(-0.11), fabs(-0.11), 1e-7);
  ck_assert_ldouble_eq_tol(s21_fabs(-0.0), fabs(-0.0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_fabs(0.), fabs(0.), 1e-7);
  ck_assert_ldouble_eq_tol(s21_fabs(20.), fabs(20.), 1e-7);
  ck_assert_ldouble_eq(s21_fabs(INFINITY), fabs(INFINITY));
  ck_assert_ldouble_eq(s21_fabs(-INFINITY), fabs(-INFINITY));
  ck_assert_ldouble_ne(s21_fabs(NAN), fabs(NAN));
}
END_TEST

START_TEST(s21_floor_test) {
  ck_assert_ldouble_eq_tol(s21_floor(-0.11), floor(-0.11), 1e-7);
  ck_assert_ldouble_eq_tol(s21_floor(0.0001), floor(0.0001), 1e-7);
  ck_assert_ldouble_eq_tol(s21_floor(1.), floor(1.), 1e-7);
  ck_assert_ldouble_eq(s21_floor(INFINITY), floor(INFINITY));
  ck_assert_ldouble_eq(s21_floor(-INFINITY), floor(-INFINITY));
  ck_assert_ldouble_ne(s21_floor(NAN), floor(NAN));
  ck_assert_ldouble_eq_tol(s21_floor(11.99), floor(11.99), 1e-7);
  ck_assert_ldouble_eq_tol(s21_floor(-15.55555), floor(-15.55555), 1e-7);
}
END_TEST

START_TEST(s21_fmod_test) {
  ck_assert_ldouble_eq_tol(s21_fmod(34.453, 0.96), fmod(34.453, 0.96), 1e-7);
  ck_assert_ldouble_eq_tol(s21_fmod(1576546.777, 77.7), fmod(1576546.777, 77.7),
                           1e-7);
  ck_assert_ldouble_eq_tol(s21_fmod(23.456, -4.355), fmod(23.456, -4.355),
                           1e-7);
  ck_assert_int_eq(s21_fmod(INFINITY, -INFINITY), fmod(INFINITY, -INFINITY));
  ck_assert_int_eq(s21_fmod(INFINITY, 3), fmod(INFINITY, 3));
  ck_assert_int_eq(s21_fmod(3, INFINITY), fmod(3, INFINITY));
}
END_TEST

START_TEST(s21_log_test) {
  ck_assert_ldouble_eq(s21_log(INFINITY), log(INFINITY));
  ck_assert_ldouble_ne(s21_log(-INFINITY), log(-INFINITY));
  ck_assert_ldouble_eq_tol(s21_log(1), log(1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_log(0.5), log(0.5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_log(1.99), log(1.99), 1e-7);
  ck_assert_ldouble_eq_tol(s21_log(3.), log(3.), 1e-7);
  ck_assert_ldouble_eq_tol(s21_log(50.1), log(50.1), 1e-7);
}
END_TEST

START_TEST(s21_pow_test) {
  ck_assert_ldouble_eq(s21_pow(INFINITY, 2), pow(INFINITY, 2));
  ck_assert_ldouble_eq(s21_pow(2, INFINITY), pow(2, INFINITY));
  ck_assert_ldouble_eq(s21_pow(2, -INFINITY), pow(2, -INFINITY));
  ck_assert_ldouble_eq(s21_pow(-INFINITY, 3), pow(-INFINITY, 3));
  ck_assert_ldouble_eq(s21_pow(-INFINITY, INFINITY), pow(-INFINITY, INFINITY));
  ck_assert_ldouble_ne(s21_pow(1, NAN), pow(1, NAN));
  ck_assert_ldouble_ne(s21_pow(-2, 3.3), pow(-2, 3.3));
  ck_assert_ldouble_eq_tol(s21_pow(-2, 3), pow(-2, 3), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(-10, 2), pow(-10, 2), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(2, 0), pow(2, 0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(0, 0), pow(0, 0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(1, -6.5), pow(1, -6.5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(5.1, -6.5), pow(5.1, -6.5), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(10, 2), pow(10, 2), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(-10, -2), pow(-10, -2), 1e-7);
  ck_assert_ldouble_eq_tol(s21_pow(10, -2), pow(10, -2), 1e-7);
}
END_TEST

START_TEST(s21_sin_test) {
  for (double test1 = -S21_PI; test1 <= S21_PI; test1 += 0.01)
    ck_assert_ldouble_eq_tol(s21_sin(test1), sinl(test1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sin(123456), sinl(123456), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sin(777777), sinl(777777), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sin(944.27), sinl(944.27), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sin(-944.27), sinl(-944.27), 1e-7);
}
END_TEST

START_TEST(s21_sqrt_test) {
  ck_assert_ldouble_eq_tol(s21_sqrt(2.3), sqrt(2.3), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1e-7);
  ck_assert_ldouble_eq_tol(s21_sqrt(10), sqrt(10), 1e-7);
  ck_assert_ldouble_eq(s21_sqrt(INFINITY), sqrt(INFINITY));
  ck_assert_ldouble_ne(s21_sqrt(-INFINITY), sqrt(-INFINITY));
}
END_TEST

START_TEST(s21_tan_test) {
  for (double test1 = -S21_PI; test1 <= S21_PI; test1 += 0.01)
    ck_assert_ldouble_eq_tol(s21_tan(test1), tanl(test1), 1e-7);
  ck_assert_ldouble_eq_tol(s21_tan(123456), tanl(123456), 1e-7);
  ck_assert_ldouble_eq_tol(s21_tan(777777), tanl(777777), 1e-7);
  ck_assert_ldouble_eq_tol(s21_tan(944.27), tanl(944.27), 1e-7);
  ck_assert_ldouble_eq_tol(s21_tan(-944.27), tanl(-944.27), 1e-7);
}
END_TEST

int main() {
  Suite *suite = suite_create("S21_TESTS");
  SRunner *srunner = srunner_create(suite);

  TCase *s21_abs_case = tcase_create("s21_abs_case");
  suite_add_tcase(suite, s21_abs_case);
  tcase_add_test(s21_abs_case, s21_abs_test);

  TCase *s21_acos_case = tcase_create("s21_acos_case");
  suite_add_tcase(suite, s21_acos_case);
  tcase_add_test(s21_acos_case, s21_acos_test);

  TCase *s21_asin_case = tcase_create("s21_asin_case");
  suite_add_tcase(suite, s21_asin_case);
  tcase_add_test(s21_asin_case, s21_asin_test);

  TCase *s21_atan_case = tcase_create("s21_atan_case");
  suite_add_tcase(suite, s21_atan_case);
  tcase_add_test(s21_atan_case, s21_atan_test);

  TCase *s21_ceil_case = tcase_create("s21_ceil_case");
  suite_add_tcase(suite, s21_ceil_case);
  tcase_add_test(s21_ceil_case, s21_ceil_test);

  TCase *s21_cos_case = tcase_create("s21_cos_case");
  suite_add_tcase(suite, s21_cos_case);
  tcase_add_test(s21_cos_case, s21_cos_test);

  TCase *s21_exp_case = tcase_create("s21_exp_case");
  suite_add_tcase(suite, s21_exp_case);
  tcase_add_test(s21_exp_case, s21_exp_test);

  TCase *s21_fabs_case = tcase_create("s21_fabs_case");
  suite_add_tcase(suite, s21_fabs_case);
  tcase_add_test(s21_fabs_case, s21_fabs_test);

  TCase *s21_floor_case = tcase_create("s21_floor_case");
  suite_add_tcase(suite, s21_floor_case);
  tcase_add_test(s21_floor_case, s21_floor_test);

  TCase *s21_fmod_case = tcase_create("s21_fmod_case");
  suite_add_tcase(suite, s21_fmod_case);
  tcase_add_test(s21_fmod_case, s21_fmod_test);

  TCase *s21_log_case = tcase_create("s21_log_case");
  suite_add_tcase(suite, s21_log_case);
  tcase_add_test(s21_log_case, s21_log_test);

  TCase *s21_pow_case = tcase_create("s21_pow_case");
  suite_add_tcase(suite, s21_pow_case);
  tcase_add_test(s21_pow_case, s21_pow_test);

  TCase *s21_sin_case = tcase_create("s21_sin_case");
  suite_add_tcase(suite, s21_sin_case);
  tcase_add_test(s21_sin_case, s21_sin_test);

  TCase *s21_sqrt_case = tcase_create("s21_sqrt_case");
  suite_add_tcase(suite, s21_sqrt_case);
  tcase_add_test(s21_sqrt_case, s21_sqrt_test);

  TCase *s21_tan_case = tcase_create("s21_tan_case");
  suite_add_tcase(suite, s21_tan_case);
  tcase_add_test(s21_tan_case, s21_tan_test);

  srunner_run_all(srunner, CK_VERBOSE);
  int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (number_failed == 0) ? 0 : 1;
}
