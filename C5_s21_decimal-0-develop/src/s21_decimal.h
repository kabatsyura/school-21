#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int checkNull(s21_decimal value);
s21_decimal divBits(s21_decimal dec1, s21_decimal dec2, s21_decimal *rmd,
                    int *fail);
int subNoScale(s21_decimal value1, s21_decimal value2, s21_decimal *result);
void changeValues(s21_decimal *value1, s21_decimal *value2);
int addNoScale(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int signLower(s21_decimal a);
int getBits(s21_decimal d, int index);
void setBits(s21_decimal *d, int index);
void initBits(s21_decimal *d);
void writeSign(s21_decimal *d, int is_negative);
void writeScaleToDecimal(s21_decimal *d, int scale);
int getScaleToDecimal(s21_decimal dec);
void getBinaryFromInt(int nmb, char *buff);
void getBinaryFromFloat(float src, char *buf);
int getHighBit(s21_decimal dec);
int shiftLeft(s21_decimal *dec, int shift);
int eqToLower(s21_decimal *dec, int scale);
int eqToBigger(s21_decimal *dec, int scale);
int eqScale(s21_decimal *dec1, s21_decimal *dec2, int scale);
int handleScaleEq(s21_decimal *value_1, s21_decimal *value_2, int *final_scale);
int getExpBinFloat(const char *src);
void mantisaDecimal(s21_decimal *d, char *float_bin_buff, int exp);
uint32_t float_bits(const float f);

#endif  // SRC_S21_DECIMAL_H_
