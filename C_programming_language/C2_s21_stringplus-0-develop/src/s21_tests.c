#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

char string1[15] = "hello world\0";
char string2[15] = "1234567890";
char string3[0];
char cmp_str1[15] = "HELLO WORLD\0";
char cmp_str2[15] = "0987654321";
char cmp_str3[0];

START_TEST(s21_memchr_test) {
    ck_assert_ptr_eq(s21_memchr(string1, 'o', 10), memchr(string1, 'o', 10));
    ck_assert_ptr_eq(s21_memchr(string2, '7', 10), memchr(string2, '7', 10));
    ck_assert_ptr_eq(s21_memchr(string3, '7', 10), memchr(string3, '7', 10));
}
END_TEST

START_TEST(s21_memcmp_test) {
    ck_assert_int_eq(s21_memcmp(string1, cmp_str1, 1),
                     memcmp(string1, cmp_str1, 1));
    ck_assert_int_eq(s21_memcmp(string2, cmp_str2, 10),
                     memcmp(string2, cmp_str2, 10));
    ck_assert_int_eq(s21_memcmp(string3, cmp_str3, 0),
                     memcmp(string3, cmp_str3, 0));
}
END_TEST

START_TEST(s21_memcpy_test) {
    char dest1[100] = "Test_1_memcpy ";
    char dest2[100] = "Test_1_memcpy ";
    s21_memcpy(dest1, string1, 11);
    memcpy(dest2, string1, 11);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_memcpy ";
    char dest4[100] = "Test_2_memcpy ";
    s21_memcpy(dest3, string2, 10);
    memcpy(dest4, string2, 10);
    ck_assert_str_eq(dest3, dest4);

    char dest5[100] = "Test_3_memcpy ";
    char dest6[100] = "Test_3_memcpy ";
    char string1_1[10] = "\0";
    s21_memcpy(dest5, string1_1, 2);
    memcpy(dest6, string1_1, 2);
    ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_memmove_test) {
    char dest1[100] = "Test_1_memmove ";
    char dest2[100] = "Test_1_memmove ";

    s21_memmove(dest1, string1, 11);
    memmove(dest2, string1, 11);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_memmove ";
    char dest4[100] = "Test_2_memmove ";
    s21_memmove(dest3, string2, 10);
    memmove(dest4, string2, 10);
    ck_assert_str_eq(dest3, dest4);

    char dest5[100] = "Test_3_memmove ";
    char dest6[100] = "Test_3_memmove ";
    s21_memmove(dest5, string3, 0);
    memmove(dest6, string3, 0);
    ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_memset_test) {
    ck_assert_str_eq(s21_memset(string1, 'H', 10), memset(string1, 'H', 10));
    ck_assert_str_eq(s21_memset(string2, '7', 10), memset(string2, '7', 10));
    ck_assert_str_eq(s21_memset(cmp_str2, '0', 10), memset(cmp_str2, '0', 10));
}
END_TEST

START_TEST(s21_strcat_test) {
    char dest1[100] = "Test_1_strcat ";
    char dest2[100] = "Test_1_strcat ";

    s21_strcat(dest1, string1);
    strcat(dest2, string1);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_strcat ";
    char dest4[100] = "Test_2_strcat ";
    s21_strcat(dest3, string2);
    strcat(dest4, string2);
    ck_assert_str_eq(dest3, dest4);

    char dest5[100] = "Test_3_strcat ";
    char dest6[100] = "Test_3_strcat ";
    s21_strcat(dest5, string3);
    strcat(dest6, string3);
    ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_strncat_test) {
    char dest1[100] = "Test_1_strncat ";
    char dest2[100] = "Test_1_strncat ";

    s21_strncat(dest1, string1, 5);
    strncat(dest2, string1, 5);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_strncat ";
    char dest4[100] = "Test_2_strncat ";
    s21_strncat(dest3, string2, 5);
    strncat(dest4, string2, 5);
    ck_assert_str_eq(dest3, dest4);

    char dest5[100] = "Test_3_strncat ";
    char dest6[100] = "Test_3_strncat ";
    s21_strncat(dest5, string3, 0);
    strncat(dest6, string3, 0);
    ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_strchr_test) {
    ck_assert_msg(s21_strchr(string1, 'w') == strchr(string1, 'w'),
                  "s21_strchr 1");
    ck_assert_msg(s21_strchr(string2, '7') == strchr(string2, '7'),
                  "s21_strchr 2");
}
END_TEST

START_TEST(s21_strcmp_test) {
    ck_assert_int_eq(s21_strcmp(string1, cmp_str1), strcmp(string1, cmp_str1));
    ck_assert_int_eq(s21_strcmp(string2, cmp_str2), strcmp(string2, cmp_str2));
    ck_assert_int_eq(s21_strcmp(string3, cmp_str3), strcmp(string3, cmp_str3));
    char *str1 = " ";
    char *str2 = "-";
    ck_assert_int_eq(s21_strcmp(str1, str2), strcmp(str1, str2));
}
END_TEST

START_TEST(s21_strncmp_test) {
    ck_assert_int_eq(s21_strncmp(string1, cmp_str1, 6),
                     strncmp(string1, cmp_str1, 6));
    ck_assert_int_eq(s21_strncmp(string2, cmp_str2, 10),
                     strncmp(string2, cmp_str2, 10));
    ck_assert_int_eq(s21_strncmp(string3, cmp_str3, 0),
                     strncmp(string3, cmp_str3, 0));
    char toCompare[20] = "Hell0 man";
    char test1_1[20] = "Hell0 world\0";
    char test2_2[20] = "Hell0 world\n\0";
    ck_assert_int_eq(s21_strncmp(test1_1, toCompare, 6),
                     strncmp(test1_1, toCompare, 6));
    ck_assert_int_eq(s21_strncmp(test2_2, toCompare, 6),
                     strncmp(test2_2, toCompare, 6));
}
END_TEST

START_TEST(s21_strcpy_test) {
    char dest1[100] = "Test_1_strcpy ";
    char dest2[100] = "Test_1_strcpy ";
    s21_strcpy(dest1, string1);
    strcpy(dest2, string1);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_strcpy ";
    char dest4[100] = "Test_2_strcpy ";
    s21_strcpy(dest3, string2);
    strcpy(dest4, string2);
    ck_assert_str_eq(dest3, dest4);

    char dest5[100] = "Test_3_strcpy ";
    char dest6[100] = "Test_3_strcpy ";
    s21_strcpy(dest5, string3);
    strcpy(dest6, string3);
    ck_assert_str_eq(dest5, dest6);
}
END_TEST

START_TEST(s21_strncpy_test) {
    char dest1[100] = "Test_1_strncpy ";
    char dest2[100] = "Test_1_strncpy ";

    s21_strncpy(dest1, string1, 7);
    strncpy(dest2, string1, 7);
    ck_assert_str_eq(dest1, dest2);

    char dest3[100] = "Test_2_strncpy ";
    char dest4[100] = "Test_2_strncpy ";
    s21_strncpy(dest3, string2, 5);
    strncpy(dest4, string2, 5);
    ck_assert_str_eq(dest3, dest4);
}
END_TEST

START_TEST(s21_strcspn_test) {
    char string_cmp1[10] = "Hello";
    char string_cmp2[4] = "1234";
    ck_assert_int_eq(s21_strcspn(string1, string_cmp1),
                     strcspn(string1, string_cmp1));
    ck_assert_int_eq(s21_strcspn(string2, string_cmp2),
                     strcspn(string2, string_cmp2));
    ck_assert_int_eq(s21_strcspn(string3, cmp_str3),
                     strcspn(string3, cmp_str3));
}
END_TEST

START_TEST(s21_strerror_test) {
    for (int index = 0; index <= 133; index++) {
        char *tester = s21_strerror(index);
        ck_assert_str_eq(tester, strerror(index));
        free(tester);
    }
}
END_TEST

START_TEST(s21_strlen_test) {
    ck_assert_int_eq(s21_strlen(string1), strlen(string1));
    ck_assert_int_eq(s21_strlen(string2), strlen(string2));
}
END_TEST

START_TEST(s21_strpbrk_test) {
    char str1[] = "abcdefghijklmnop", str2[] = "pksah", str3[] = "";
    ck_assert_msg(s21_strpbrk(string1, str1) == strpbrk(string1, str1),
                  "s21_strpbrk 1");
    ck_assert_msg(s21_strpbrk(string1, str2) == strpbrk(string1, str2),
                  "s21_strpbrk 2");
    ck_assert_msg(s21_strpbrk(string1, str3) == strpbrk(string1, str3),
                  "s21_strpbrk 3");
}
END_TEST

START_TEST(s21_strrchr_test) {
    char str_strrchr[15] = "123123123";
    ck_assert_msg(s21_strrchr(string1, 'l') == strrchr(string1, 'l'),
                  "s21_strrchr 1");
    ck_assert_msg(s21_strrchr(str_strrchr, '2') == strrchr(str_strrchr, '2'),
                  "s21_strrchr 2");
}
END_TEST

START_TEST(s21_strspn_test) {
    char str_strspn1[10] = "elloH";
    char str_strspn2[10] = "210";
    ck_assert_int_eq(s21_strspn(string1, str_strspn1),
                     strspn(string1, str_strspn1));
    ck_assert_int_eq(s21_strspn(string2, str_strspn2),
                     strspn(string2, str_strspn2));
}
END_TEST

START_TEST(s21_strstr_test) {
    char str1[4] = "ell";
    char str2[4] = "345";
    char *result, *result2;

    result = s21_strstr(string1, str1);
    result2 = strstr(string1, str1);
    ck_assert_msg(result == result2, "s21_strstr 1");

    result = s21_strstr(string2, str2);
    result2 = strstr(string2, str2);
    ck_assert_msg(result == result2, "s21_strstr 2");
}
END_TEST

START_TEST(s21_strtok_test) {
    char str1_1[100] = "test1/test2/test3/test4";
    char str1[100] = "test1/test2/test3/test4";
    char delim1[4] = "/";
    char *result, *result2;

    result = s21_strtok(str1_1, delim1);
    result2 = strtok(str1, delim1);
    ck_assert_str_eq(result, result2);
    ck_assert_str_eq(s21_strtok(S21_NULL, delim1), strtok(NULL, delim1));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim1), strtok(NULL, delim1));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim1), strtok(NULL, delim1));

    char str2_1[100] = "Aleksey - Ramil - Dima - Semen - Dylara";
    char str2[100] = "Aleksey - Ramil - Dima - Semen - Dylara";
    char delim2[10] = " - ";
    char *result3, *result4;

    result3 = s21_strtok(str2_1, delim2);
    result4 = strtok(str2, delim2);
    ck_assert_str_eq(result3, result4);
    ck_assert_str_eq(s21_strtok(S21_NULL, delim2), strtok(NULL, delim2));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim2), strtok(NULL, delim2));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim2), strtok(NULL, delim2));

    char str3_1[100] = "Aleksey - Ramil - Dima - Semen - Dylara";
    char str3[100] = "Aleksey - Ramil - Dima - Semen - Dylara";
    char delim3[10] = " ";
    char *result5, *result6;

    result5 = s21_strtok(str3_1, delim3);
    result6 = strtok(str3, delim3);
    ck_assert_str_eq(result5, result6);
    ck_assert_str_eq(s21_strtok(S21_NULL, delim3), strtok(NULL, delim3));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim3), strtok(NULL, delim3));
    ck_assert_str_eq(s21_strtok(S21_NULL, delim3), strtok(NULL, delim3));
}
END_TEST

START_TEST(s21_to_upper_test) {
    char *temp;

    temp = s21_to_upper("test");
    ck_assert_str_eq(temp, "TEST");
    free(temp);

    temp = s21_to_upper("777test777");
    ck_assert_str_eq(temp, "777TEST777");
    free(temp);

    temp = s21_to_upper("!@#$");
    ck_assert_str_eq(temp, "!@#$");
    free(temp);

    temp = s21_to_upper(" ");
    ck_assert_str_eq(temp, " ");
    free(temp);
}
END_TEST

START_TEST(s21_to_lower_test) {
    char *temp = s21_to_lower(cmp_str1);
    ck_assert_str_eq(temp, "hello world\0");
    free(temp);

    temp = s21_to_lower("TEST");
    ck_assert_str_eq(temp, "test");
    free(temp);

    temp = s21_to_lower("777TEST777");
    ck_assert_str_eq(temp, "777test777");
    free(temp);

    temp = s21_to_lower("!@#$");
    ck_assert_str_eq(temp, "!@#$");
    free(temp);
    temp = s21_to_lower(" ");
    ck_assert_str_eq(temp, " ");
    free(temp);
}
END_TEST

START_TEST(s21_insert_test) {
    char src1[50] = "Hello";
    char str1[50] = ", team!";
    char *temp = s21_insert(src1, str1, 5);
    ck_assert_str_eq(temp, "Hello, team!");
    free(temp);

    char src2[50] = "team!";
    char str2[50] = "Dream";
    temp = s21_insert(src2, str2, 0);
    ck_assert_str_eq(temp, "Dreamteam!");
    free(temp);

    char src3[50] = "VR";
    char str3[50] = "erte";
    temp = s21_insert(src3, str3, 1);
    ck_assert_str_eq(temp, "VerteR");
    free(temp);

    char src4[50] = "";
    char str4[50] = " ";
    temp = s21_insert(src4, str4, 0);
    ck_assert_str_eq(temp, " ");
    free(temp);
}
END_TEST

START_TEST(s21_trim_test) {
    char src1[50] = "***Hello***";
    char trim_chars1[50] = "*";
    char *temp = s21_trim(src1, trim_chars1);
    ck_assert_str_eq(temp, "Hello");
    free(temp);

    char src2[50] = " Dreamteam! ";
    char trim_chars2[50] = "";
    temp = s21_trim(src2, trim_chars2);
    ck_assert_str_eq(temp, " Dreamteam! ");
    free(temp);

    char src3[50] = "DELETEtestDELETE";
    char trim_chars3[50] = "DELETE";
    temp = s21_trim(src3, trim_chars3);
    ck_assert_str_eq(temp, "test");
    free(temp);
}
END_TEST

START_TEST(s21_sprintf_test) {
    char c[255] = {}, d[255] = {}, x1 = 't';
    int n = 2100, n1 = 0, n2 = -21;
    short sh = 123, sh1 = -123;
    float f = 21.21, f1 = -21.21;
    long int lg = 12345678912345, lg1 = -12345678912345;
    s21_sprintf(c, "%% %p", &n);
    sprintf(d, "%% %p", &n);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg,
                lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
            lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n,
                212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
            2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    sprintf(d, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    ck_assert_str_eq(c, d);
    s21_sprintf(
        c, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d", 10,
        n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    sprintf(d, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
            10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX,
                SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
            USHRT_MAX, LONG_MAX, LONG_MIN);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %10c %-10c", '!', 'a', 'b');
    sprintf(d, "%c %10c %-10c", '!', 'a', 'b');
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    sprintf(d, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello",
                "hello", "hello", "hello", "hello", "hello");
    sprintf(d, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello",
            "hello", "hello", "hello", "hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello",
                L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
    sprintf(d, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello", L"hello",
            L"hello", L"hello", L"hello", L"hello", L"hello");
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%u %lu", UINT_MAX, ULONG_MAX);
    sprintf(d, "%u %lu", UINT_MAX, ULONG_MAX);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "hello %n", &n);
    sprintf(d, "hello %n", &n1);
    ck_assert_msg(c, d, "error");
    s21_sprintf(c, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n,
                0, n2, 0, 21, 42);
    sprintf(d, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0,
            n2, 0, 21, 42);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0,
                123);
    sprintf(d, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21,
                n, 0, 123);
    sprintf(d, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0,
            123);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n,
            n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    sprintf(d, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
                4221, n1);
    sprintf(d, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
            4221, n1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
                21.21, -21.21, 42.42, -42.42, f, f1);
    sprintf(d, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
            21.21, -21.21, 42.42, -42.42, f, f1);
    ck_assert_str_eq(c, d);
    s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21);
    sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
            21.21, 0.0, 21.21, 21., 0.0, 21.21);
    ck_assert_str_eq(c, d);
    ck_assert_int_eq(
        s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1,
                    21., 21.21, 0.0, 21.21, 21., 0.0, 21.21),
        sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                21.21, 0.0, 21.21, 21., 0.0, 21.21));
    ck_assert_int_eq(
        s21_sprintf(c,
                    "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                    n, n2, 21, 0, 42, 21, 0, -65, lg, lg1),
        sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                n, n2, 21, 0, 42, 21, 0, -65, lg, lg1));
}
END_TEST

START_TEST(s21_sscanf_test) {
    wchar_t wc1, wc2;
    int a1 = 1, b1 = 0, i1 = 0, n1 = 0, i2 = 0, n2 = 0;
    unsigned int a2 = 1, a3 = 1, b2 = 0, b3 = 0;
    long e1 = 1, r1 = 1;
    unsigned long e2 = 0, r2 = 0;
    long double e3 = 0, e4 = 0, g3 = 0, g4 = 0, ld1 = 0, ld2 = 1;
    float f1 = 0, f2 = 1;
    char q1 = '0', w1 = '1', arr1[100] = "", arr2[100] = "";
    void *adres1 = S21_NULL, *adres2 = S21_NULL;
    ck_assert_int_eq(
        s21_sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &a1, &a2, &a3, &q1,
                   arr1),
        sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &b1, &b2, &b3, &w1, arr2));
    ck_assert_int_eq(a1, b1);
    ck_assert_int_eq(a2, b2);
    ck_assert_int_eq(a3, b3);
    ck_assert_int_eq(q1, w1);
    ck_assert_str_eq(arr1, arr2);
    ck_assert_int_eq(
        s21_sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc1, &f1, &ld1),
        sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc2, &f2, &ld2));
    ck_assert_float_eq(f1, f2);
    ck_assert_ldouble_eq(ld1, ld2);
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                     sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
    ck_assert_int_eq(e1, r1);
    ck_assert_int_eq(e2, r2);
    ck_assert_int_eq(s21_sscanf("5 0x213def", "%1i%p%n", &i1, &adres1, &n1),
                     sscanf("5 0x213def", "%1i%p%n", &i2, &adres2, &n2));
    ck_assert_int_eq(i1, i2);
    ck_assert_int_eq(n1, n2);
    ck_assert_ptr_eq(adres1, adres2);
    ck_assert_int_eq(
        s21_sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e3, &g3),
        sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e4, &g4));
    ck_assert_ldouble_eq(e3, e4);
    ck_assert_ldouble_eq(g3, g4);
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                     sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
    ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "dfdf"),
                     sscanf(" -123abcdeasd", "dfdf"));
}
END_TEST

int main() {
    Suite *suite = suite_create("s21_suite_tests");
    SRunner *suite_runner = srunner_create(suite);
    // test 1
    TCase *s21_memchrCase = tcase_create("s21_memchrCase");
    suite_add_tcase(suite, s21_memchrCase);
    tcase_add_test(s21_memchrCase, s21_memchr_test);
    // test 2
    TCase *s21_memcmpCase = tcase_create("s21_memcmpCase");
    suite_add_tcase(suite, s21_memcmpCase);
    tcase_add_test(s21_memcmpCase, s21_memcmp_test);
    // test 3
    TCase *s21_memcpyCase = tcase_create("s21_memcpyCase");
    suite_add_tcase(suite, s21_memcpyCase);
    tcase_add_test(s21_memcpyCase, s21_memcpy_test);
    // test 4
    TCase *s21_memmoveCase = tcase_create("s21_memmoveCase");
    suite_add_tcase(suite, s21_memmoveCase);
    tcase_add_test(s21_memmoveCase, s21_memmove_test);
    // test 5
    TCase *s21_memsetCase = tcase_create("s21_memsetCase");
    suite_add_tcase(suite, s21_memsetCase);
    tcase_add_test(s21_memsetCase, s21_memset_test);
    // test 6
    TCase *s21_strcatCase = tcase_create("s21_strcatCase");
    suite_add_tcase(suite, s21_strcatCase);
    tcase_add_test(s21_strcatCase, s21_strcat_test);
    // test 7
    TCase *s21_strncatCase = tcase_create("s21_strncatCase");
    suite_add_tcase(suite, s21_strncatCase);
    tcase_add_test(s21_strncatCase, s21_strncat_test);
    // test 8
    TCase *s21_strchrCase = tcase_create("s21_strchrCase");
    suite_add_tcase(suite, s21_strchrCase);
    tcase_add_test(s21_strchrCase, s21_strchr_test);
    // test 9
    TCase *s21_strcmpCase = tcase_create("s21_strcmpCase");
    suite_add_tcase(suite, s21_strcmpCase);
    tcase_add_test(s21_strcmpCase, s21_strcmp_test);
    // test 10
    TCase *s21_strncmpCase = tcase_create("s21_strncmpCase");
    suite_add_tcase(suite, s21_strncmpCase);
    tcase_add_test(s21_strncmpCase, s21_strncmp_test);
    // test 11
    TCase *s21_strcpyCase = tcase_create("s21_strcpyCase");
    suite_add_tcase(suite, s21_strcpyCase);
    tcase_add_test(s21_strcpyCase, s21_strcpy_test);
    // test 12
    TCase *s21_strncpyCase = tcase_create("s21_strncpyCase");
    suite_add_tcase(suite, s21_strncpyCase);
    tcase_add_test(s21_strncpyCase, s21_strncpy_test);
    // test 13
    TCase *s21_strcspnCase = tcase_create("s21_strcspnCase");
    suite_add_tcase(suite, s21_strcspnCase);
    tcase_add_test(s21_strcspnCase, s21_strcspn_test);
    // test 14
    TCase *s21_strerrorCase = tcase_create("s21_strerrorCase");
    suite_add_tcase(suite, s21_strerrorCase);
    tcase_add_test(s21_strerrorCase, s21_strerror_test);
    // test 15
    TCase *s21_strlenCase = tcase_create("s21_strlenCase");
    suite_add_tcase(suite, s21_strlenCase);
    tcase_add_test(s21_strlenCase, s21_strlen_test);
    // test 16
    TCase *s21_strpbrkCase = tcase_create("s21_strpbrkCase");
    suite_add_tcase(suite, s21_strpbrkCase);
    tcase_add_test(s21_strpbrkCase, s21_strpbrk_test);
    // test 17
    TCase *s21_strrchrCase = tcase_create("s21_strrchrCase");
    suite_add_tcase(suite, s21_strrchrCase);
    tcase_add_test(s21_strrchrCase, s21_strrchr_test);
    // test 18
    TCase *s21_strspnCase = tcase_create("s21_strspnCase");
    suite_add_tcase(suite, s21_strspnCase);
    tcase_add_test(s21_strspnCase, s21_strspn_test);
    // test 19
    TCase *s21_strstrCase = tcase_create("s21_strstrCase");
    suite_add_tcase(suite, s21_strstrCase);
    tcase_add_test(s21_strstrCase, s21_strstr_test);
    // test 20
    TCase *s21_strtokCase = tcase_create("s21_strtokCase");
    suite_add_tcase(suite, s21_strtokCase);
    tcase_add_test(s21_strtokCase, s21_strtok_test);
    // bonus 1
    TCase *s21_to_upperCase = tcase_create("s21_to_upperCase");
    suite_add_tcase(suite, s21_to_upperCase);
    tcase_add_test(s21_to_upperCase, s21_to_upper_test);
    // bonus 2
    TCase *s21_to_lowerCase = tcase_create("s21_to_lowerCase");
    suite_add_tcase(suite, s21_to_lowerCase);
    tcase_add_test(s21_to_lowerCase, s21_to_lower_test);
    // bonus 3
    TCase *s21_insertCase = tcase_create("s21_insertCase");
    suite_add_tcase(suite, s21_insertCase);
    tcase_add_test(s21_insertCase, s21_insert_test);
    // bonus 4
    TCase *s21_trimCase = tcase_create("s21_trimCase");
    suite_add_tcase(suite, s21_trimCase);
    tcase_add_test(s21_trimCase, s21_trim_test);
    // s21_sprintf
    TCase *s21_sprintfCase = tcase_create("s21_sprintfCase");
    suite_add_tcase(suite, s21_sprintfCase);
    tcase_add_test(s21_sprintfCase, s21_sprintf_test);
    // s21_sscanf
    TCase *s21_sscanfCase = tcase_create("s21_sscanfCase");
    suite_add_tcase(suite, s21_sscanfCase);
    tcase_add_test(s21_sscanfCase, s21_sscanf_test);

    // run all tests
    srunner_run_all(suite_runner, CK_VERBOSE);
    int number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);

    return (number_failed == 0) ? 0 : 1;
}
