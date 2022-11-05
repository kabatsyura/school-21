#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  if (!result) {
    res = 1;
  } else {
    initBits(result);
    int scaleWrite;
    res = handleScaleEq(&value_1, &value_2, &scaleWrite);
    if (res == 0) {
      res = addNoScale(value_1, value_2, result);
      writeScaleToDecimal(result, scaleWrite);
    }
  }
  return res;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int scaleWrite;
  int ret = handleScaleEq(&value_1, &value_2, &scaleWrite);
  if (ret == 0) {
    initBits(result);
    ret = subNoScale(value_1, value_2, result);
    writeScaleToDecimal(result, scaleWrite);
  }
  return ret;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int bitval1 = getScaleToDecimal(value_1);
  int bitval2 = getScaleToDecimal(value_2);
  int sign = 0;
  if ((getBits(value_1, 127) && !getBits(value_2, 127)) ||
      (!getBits(value_1, 127) && getBits(value_2, 127)))
    sign = 1;
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  initBits(result);
  for (int i = 0; i <= getHighBit(value_2); i++) {
    int bit_2 = getBits(value_2, i);
    if (bit_2) {
      s21_decimal tmp = value_1;
      err = shiftLeft(&tmp, i);
      if (err) break;
      err = addNoScale(*result, tmp, result);
      if (err) break;
    }
  }
  int scale = bitval1 + bitval2;
  if (scale > 28)
    err = 2;
  else
    writeScaleToDecimal(result, scale);
  if (sign && !err) setBits(result, 127);
  if (err == 1 && sign) {
    err = 2;
  }
  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  initBits(result);
  if (checkNull(value_2)) {
    res = 3;
  } else {
    int sing1 = getBits(value_1, 127);
    int sing2 = getBits(value_2, 127);
    int scale1 = getScaleToDecimal(value_1);
    int scale2 = getScaleToDecimal(value_2);
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    s21_decimal remainder, dec_int_part;
    int division_counter = 0;
    dec_int_part = divBits(value_1, value_2, &remainder, &res);
    *result = dec_int_part;
    while (!checkNull(remainder) && division_counter <= 10) {
      eqToBigger(&remainder, 1);
      division_counter++;
      dec_int_part = divBits(remainder, value_2, &remainder, &res);
      writeScaleToDecimal(&dec_int_part, division_counter);
      res = s21_add(*result, dec_int_part, result);
      if (res != 0) break;
    }
    if (sing1 != sing2) setBits(result, 127);
    int scale_result = scale1 - scale2;
    if (scale_result < 0 && !res) {
      res = eqToBigger(result, 0 - scale_result);
    }
    if (getBits(value_1, 127) != getBits(value_2, 127)) setBits(result, 127);
    if (checkNull(*result) && !checkNull(value_1)) res = 2;
  }
  return res;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  float float2;
  int res = 0;
  s21_from_decimal_to_float(value_2, &float2);
  int signValue_1 = getBits(value_1, 127);
  int signValue_2 = getBits(value_2, 127);
  if (float2 == 0) {
    res = 3;
  }
  if (signValue_1) {
    s21_negate(value_1, &value_1);
  }
  if (signValue_2) {
    s21_negate(value_2, &value_2);
  }
  if (s21_is_less(value_1, value_2)) {
    *result = value_1;
  }
  if (s21_is_equal(value_2, value_1)) {
    initBits(result);
  }
  if (s21_is_greater(value_1, value_2)) {
    s21_decimal sumDec = {{0, 0, 0, 0}};
    s21_decimal temp = value_2;
    while (s21_is_greater_or_equal(value_1, temp)) {
      sumDec = temp;
      s21_add(value_2, temp, &temp);
    }
    s21_sub(value_1, sumDec, result);
  }
  if (signValue_1 && signValue_2) {
    s21_negate(*result, result);
  }
  return res;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 0;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 1;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 0;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 1;
        break;
      } else {
        continue;
      }
    }
    if (getBits(value_1, 127)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 0;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 1;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 0;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 0;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 1;
        break;
      } else {
        result = 1;
        continue;
      }
    }
    if (getBits(value_1, 127)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }
  return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 1;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 0;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 1;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 0;
        break;
      } else {
        result = 0;
        continue;
      }
    }
    if (getBits(value_1, 127)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 1;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 0;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 1;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 0;
        break;
      } else {
        continue;
      }
    }
    if (getBits(value_1, 127)) {
      if (result == 1)
        result = 0;
      else
        result = 1;
    }
  }
  return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 1;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 0;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 0;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 0;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 0;
        break;
      } else {
        continue;
      }
    }
  }
  return result;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int scale;
  int result = 0;
  handleScaleEq(&value_1, &value_2, &scale);
  if (signLower(value_1) && !signLower(value_2)) {
    result = 1;
  } else if (!signLower(value_1) && signLower(value_2)) {
    result = 1;
  } else if (signLower(value_1) == signLower(value_2)) {
    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
        break;
      } else if (value_1.bits[i] < value_2.bits[i]) {
        result = 1;
        break;
      } else {
        continue;
      }
    }
  }
  return result;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    initBits(dst);
    if (src < 0) {
      src *= -1;
      setBits(dst, 127);
    }
    char buff[32];
    getBinaryFromInt(src, buff);
    for (int i = 31, j = 0; i >= 0; i--, j++) {
      if (buff[i]) setBits(dst, j);
    }
  }
  return res;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = 0;
  if (src == 1 / 0.0 && src == 0 / 0.0 && src == -1 / 0.0 && src == -0 / 0.0)
    res = 1;
  initBits(dst);
  if (src != 0) {
    initBits(dst);
    if (dst && !res) {
      int is_negative = 0;
      if (src < 0) {
        is_negative = 1;
        src *= -1;
      }
      double doub = src;
      char float_bin_buff[32] = "";
      getBinaryFromFloat((float)doub, float_bin_buff);
      int exp = getExpBinFloat(float_bin_buff);
      int scale = 0;
      while (scale < 28 && (int)doub / (int)pow(2, 21) == 0) {
        doub *= 10;
        scale++;
      }
      doub = round(doub);
      if (scale <= 28 && (exp > -94 && exp < 96)) {
        while (fmod(doub, 10) == 0 && scale > 0) {
          doub = doub / 10;
          scale--;
        }
        getBinaryFromFloat((float)doub, float_bin_buff);
        exp = getExpBinFloat(float_bin_buff);
        setBits(dst, exp);
        mantisaDecimal(dst, float_bin_buff, exp);
        writeScaleToDecimal(dst, scale);
        writeSign(dst, is_negative);
      } else {
        res = 1;
      }
    }
  }
  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = 0;
  if (!dst) {
    res = 1;
  } else {
    s21_decimal truncated;
    res = s21_truncate(src, &truncated);
    int highBit = getHighBit(truncated);
    if (highBit > 31) {
      res = 1;
    } else {
      int base = 1;
      *dst = 0;
      for (int i = 0; i <= highBit; i++) {
        *dst += getBits(truncated, i) * base;
        base = base * 2;
      }
      if (getBits(src, 127)) *dst *= -1;
    }
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  if (!dst || getScaleToDecimal(src) > 28) {
    res = 1;
  } else {
    *dst = 0.0;
    int scale = getScaleToDecimal(src);
    int last_bit = getBits(src, 127);
    int sign = getBits(src, 127);
    if (sign) setBits(&src, 127);
    writeScaleToDecimal(&src, scale);
    double tmp = *dst;
    if (last_bit == 1) setBits(&src, 127);
    unsigned long base = 1;
    for (int i = 0; i < 96; i++) {
      tmp += getBits(src, i) * base;
      base = base * 2;
    }
    while (scale != 0) {
      tmp = tmp / 10;
      scale--;
    }
    if (getBits(src, 127)) tmp *= -1;
    *dst = tmp;
  }
  return res;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = 0;
  if (!result) {
    res = 1;
  } else {
    if (checkNull(value)) {
      initBits(result);
    } else {
      s21_decimal truncated;
      res = s21_truncate(value, &truncated);
      if (res) return res;
      if (s21_is_equal(truncated, value)) {
        *result = value;
      } else {
        if (getBits(value, 127)) {
          s21_decimal one = {{1, 0, 0, 0}};
          res = s21_sub(truncated, one, result);
        } else {
          *result = truncated;
        }
      }
    }
  }
  return res;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int resd = 0;
  initBits(result);
  if (!result) {
    resd = 1;
  } else {
    if (checkNull(value)) {
      initBits(result);
    } else {
      s21_decimal truncated;
      resd = s21_truncate(value, &truncated);
      if (resd) return resd;
      if (s21_is_equal(truncated, value)) {
        *result = value;
      } else {
        int sign = 0;
        if (getBits(value, 127)) {
          sign = 1;
          s21_negate(value, &value);
          s21_negate(truncated, &truncated);
        }
        s21_decimal result_of_sub;
        s21_sub(value, truncated, &result_of_sub);
        float res;
        resd = s21_from_decimal_to_float(result_of_sub, &res);
        if (resd) return resd;
        s21_decimal one = {{1, 0, 0, 0}};
        s21_decimal zero = {{0, 0, 0, 0}};
        if (res >= 0.5) {
          resd = s21_add(truncated, one, &truncated);
        }
        if (resd) return resd;
        *result = truncated;
        if (sign && !s21_is_equal(truncated, zero)) setBits(result, 127);
      }
    }
  }
  return resd;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  if (!result) {
    ret = 1;
  } else {
    int scale = getScaleToDecimal(value);
    s21_decimal ten = {{10, 0, 0, 0}}, rem;
    int fail = 0;
    int sign = 0;
    if (getBits(value, 127)) sign = 1;
    value.bits[3] = 0;
    while (scale) {
      value = divBits(value, ten, &rem, &fail);
      if (fail) break;
      scale--;
    }
    if (sign) setBits(&value, 127);
    ret = fail;
    *result = value;
  }
  return ret;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  if (!getBits(value, 127))
    result->bits[3] |= 1u << 31;
  else
    result->bits[3] &= ~(1u << 31);
  return 0;
}

int checkNull(s21_decimal value) {
  int ret_val = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0)
    ret_val = 1;
  return ret_val;
}

s21_decimal divBits(s21_decimal dec1, s21_decimal dec2, s21_decimal *rmd,
                    int *fail) {
  initBits(rmd);
  s21_decimal result = {{0, 0, 0, 0}};
  int resScale = 0;
  *fail = handleScaleEq(&dec1, &dec2, &resScale);
  for (int i = getHighBit(dec1); i >= 0; i--) {
    if (getBits(dec1, i)) setBits(rmd, 0);
    if (s21_is_greater_or_equal(*rmd, dec2)) {
      *fail = subNoScale(*rmd, dec2, rmd);
      if (i != 0) *fail = shiftLeft(rmd, 1);
      if (getBits(dec1, i - 1)) setBits(rmd, 0);
      *fail = shiftLeft(&result, 1);
      setBits(&result, 0);
    } else {
      *fail = shiftLeft(&result, 1);
      if (i != 0) *fail = shiftLeft(rmd, 1);
      if (i - 1 >= 0 && getBits(dec1, i - 1)) setBits(rmd, 0);
    }
  }
  writeScaleToDecimal(rmd, resScale);
  return result;
}

int subNoScale(s21_decimal value1, s21_decimal value2, s21_decimal *result) {
  initBits(result);
  int ret = 0;
  int rmd = 0;
  if (!getBits(value1, 127) && getBits(value2, 127)) {
    s21_negate(value2, &value2);
    ret = addNoScale(value1, value2, result);
  } else if (getBits(value1, 127) && !getBits(value2, 127)) {
    setBits(&value2, 127);
    ret = addNoScale(value1, value2, result);
  } else {
    if (getBits(value1, 127) && getBits(value2, 127)) {
      s21_negate(value2, &value2);
      s21_negate(value1, &value1);
      changeValues(&value1, &value2);
    }
    if (!s21_is_greater_or_equal(value1, value2)) {
      setBits(result, 127);
      changeValues(&value1, &value2);
    }
    for (int i = 0; i < 96; i++) {
      if (getBits(value1, i) - getBits(value2, i) == 0) {
        if (rmd == 1) {
          setBits(result, i);
        }
      } else if (getBits(value1, i) - getBits(value2, i) == 1) {
        if (rmd == 0)
          setBits(result, i);
        else
          rmd = 0;
      } else if (getBits(value1, i) - getBits(value2, i) == -1) {
        if (rmd != 1) {
          setBits(result, i);
          rmd = 1;
        } else {
          rmd = 1;
        }
      }
      if (i == 95 && rmd) {
        if (getBits(*result, 127))
          ret = 2;
        else
          ret = 1;
      }
    }
  }
  return ret;
}

void changeValues(s21_decimal *value1, s21_decimal *value2) {
  s21_decimal value2_tmp = *value2;
  *value2 = *value1;
  *value1 = value2_tmp;
}

int addNoScale(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_Function = 0;
  if (getBits(value_1, 127) != getBits(value_2, 127)) {
    s21_decimal value_1tmp = value_1;
    s21_decimal value_2tmp = value_2;
    if (getBits(value_1, 127))
      s21_negate(value_1, &value_1tmp);
    else
      s21_negate(value_2, &value_2tmp);
    result_Function = subNoScale(value_1tmp, value_2tmp, result);
    if (getBits(value_1, 127) && s21_is_greater(value_1, value_2))
      s21_negate(*result, result);
    else if (s21_is_greater(value_2, value_1))
      s21_negate(*result, result);
  } else {
    int check_minus;
    int in_mind = 0;
    s21_decimal temp = {{0, 0, 0, 0}};
    if (getBits(value_1, 127) == 1) setBits(&temp, 127);
    for (int i = 0; i < 96; i++) {
      if (getBits(value_1, i) && getBits(value_2, i)) {
        if (in_mind) setBits(&temp, i);
        in_mind = 1;
      } else if (getBits(value_1, i) || getBits(value_2, i)) {
        if (!in_mind) setBits(&temp, i);
      } else if (in_mind) {
        setBits(&temp, i);
        in_mind = 0;
      }
      if (i == 95 && in_mind) {
        check_minus = signLower(temp);
        if (check_minus == 1)
          result_Function = 2;
        else
          result_Function = 1;
      }
    }
    *result = temp;
  }
  return result_Function;
}

int signLower(s21_decimal a) { return a.bits[3] >> 31; }

int getBits(s21_decimal d, int index) {
  int ret = 0;
  if (index >= 0) {
    int bits_index = 0;
    if (index > 127) {
      exit(1);
    }
    if (index > 31) {
      bits_index = index / 32;
      index = index % 32;
    }
    ret = (d.bits[bits_index] & (1u << index)) != 0;
  }
  return ret;
}

void setBits(s21_decimal *d, int index) {
  int bIndex = 0;
  if (index > 127 || index < 0) {
    exit(1);
  }
  if (index > 31) {
    bIndex = index / 32;
    index = index % 32;
  }
  d->bits[bIndex] = d->bits[bIndex] | (1u << index);
}

void initBits(s21_decimal *d) {
  if (d) {
    for (int i = 0; i < 4; i++) {
      d->bits[i] = 0;
    }
  }
}

void writeSign(s21_decimal *d, int is_negative) {
  if (is_negative) setBits(d, 127);
}

void writeScaleToDecimal(s21_decimal *d, int scale) {
  if (scale < 0) {
    exit(1);
  }
  char scale_bin_buff[32];
  getBinaryFromInt(scale, scale_bin_buff);
  for (int i = 24, j = 119; i < 32; i++, j--) {
    if (scale_bin_buff[i]) setBits(d, j);
  }
}

int getScaleToDecimal(s21_decimal dec) {
  int result = 0, base = 1;
  for (int i = 112; i <= 119; i++) {
    result += getBits(dec, i) * base;
    base = base * 2;
  }
  return result;
}

void getBinaryFromInt(int nmb, char *buff) {
  int index = 0;
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    buff[index] = !!(nmb & mask);
    index++;
  }
}

void getBinaryFromFloat(float src, char *buf) {
  unsigned int fbits = float_bits(src);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) {
    *buf = !!(fbits & mask);
    buf++;
  }
}

int getHighBit(s21_decimal dec) {
  int i = 95;
  while (i) {
    if (getBits(dec, i)) break;
    i--;
  }
  return i;
}

int shiftLeft(s21_decimal *dec, int shift) {
  int ret_val = 0;
  int high = getHighBit(*dec);
  if (high + shift > 95) {
    ret_val = 1;
  } else {
    for (int i = 0; i < shift; i++) {
      int last_low_bit_set = getBits(*dec, 31);
      int last_mid_bit_set = getBits(*dec, 63);
      dec->bits[0] = dec->bits[0] << 1;
      dec->bits[1] = dec->bits[1] << 1;
      dec->bits[2] = dec->bits[2] << 1;
      if (last_low_bit_set) setBits(dec, 32);
      if (last_mid_bit_set) setBits(dec, 64);
    }
  }
  if (getBits(*dec, 127) && ret_val) ret_val = 2;
  return ret_val;
}

int eqToLower(s21_decimal *dec, int scale) {
  int ret = 0;
  while (scale--) {
    s21_decimal reminder;
    s21_decimal ten = {{10, 0, 0, 0}};
    *dec = divBits(*dec, ten, &reminder, &ret);
    if (ret != 0) break;
  }
  return ret;
}

int eqToBigger(s21_decimal *dec, int scale) {
  int ret = 0;
  while (scale--) {
    s21_decimal buf1 = *dec, buf2 = *dec;
    ret = shiftLeft(&buf2, 3);
    if (ret != 0) break;
    ret = shiftLeft(&buf1, 1);
    if (ret != 0) break;
    ret = s21_add(buf2, buf1, dec);
    if (ret != 0) break;
  }
  return ret;
}

int eqScale(s21_decimal *dec1, s21_decimal *dec2, int scale) {
  int scale1 = getScaleToDecimal(*dec1);
  int scale2 = getScaleToDecimal(*dec2);
  int ret = 0;
  int sign1 = getBits(*dec1, 127);
  dec1->bits[3] = 0;
  int sign2 = getBits(*dec2, 127);
  dec2->bits[3] = 0;
  if (scale1 > scale)
    ret = eqToLower(dec1, scale1 - scale);
  else if (scale1 < scale)
    ret = eqToBigger(dec1, scale - scale1);
  if (scale2 > scale)
    ret = eqToLower(dec2, scale2 - scale);
  else if (scale2 < scale)
    ret = eqToBigger(dec2, scale - scale2);
  writeScaleToDecimal(dec1, scale);
  writeScaleToDecimal(dec2, scale);
  if (sign1) setBits(dec1, 127);
  if (sign2) setBits(dec2, 127);
  return ret;
}

int handleScaleEq(s21_decimal *value_1, s21_decimal *value_2,
                  int *final_scale) {
  s21_decimal value1_tmp = *value_1;
  s21_decimal value2_tmp = *value_2;
  int scale1 = getScaleToDecimal(*value_1);
  int scale2 = getScaleToDecimal(*value_2);
  int ret = 0, scale_to_write = scale1;
  if (scale1 > scale2) {
    ret = eqScale(&value1_tmp, &value2_tmp, scale1);
    scale_to_write = scale1;
    if (ret != 0) {
      scale_to_write = scale2;
      value1_tmp = *value_1;
      value2_tmp = *value_2;
      ret = eqScale(&value1_tmp, &value2_tmp, scale2);
    }
  } else if (scale1 < scale2) {
    ret = eqScale(&value1_tmp, &value2_tmp, scale2);
    scale_to_write = scale2;
    if (ret != 0) {
      scale_to_write = scale1;
      value1_tmp = *value_1;
      value2_tmp = *value_2;
      ret = eqScale(&value1_tmp, &value2_tmp, scale1);
    }
  }
  *final_scale = scale_to_write;
  *value_1 = value1_tmp;
  *value_2 = value2_tmp;
  return ret;
}

int getExpBinFloat(const char *src) {
  int result = 0, base = 1;
  for (int i = 8; i > 0; i--) {
    result += src[i] * base;
    base = base * 2;
  }
  return (result - 127);
}

void mantisaDecimal(s21_decimal *d, char *float_bin_buff, int exp) {
  for (int i = exp - 1, j = 9; i >= 0 && j < 32; i--, j++) {
    if (float_bin_buff[j]) setBits(d, i);
  }
}

uint32_t float_bits(const float f) {
  union {
    uint32_t u;
    float f;
  } temp;
  temp.f = f;
  return temp.u;
}
