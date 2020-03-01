/*
 * stats/test/check-stats.c --
 */

#include <stdlib.h>
#include <check.h>

#include "stats.h"

#ifndef ck_assert_double_eq_tol
#include <math.h>

void ck_assert_double_eq_tol(double x, double y, double t)
{
    ck_assert_msg(fabsl(x - y) < t,
                  "Assertion 'fabsl(%g - %g) < %g' failed", x, y, t);
}
#endif

START_TEST(test_stat0)
{
    double a[] = {60, 53, 168, 59, 52, 55, 57};
    stats_t res;
    double tolerance = 0.00000001;

    stats(a, sizeof(a) / sizeof(a[0]), &res);

    ck_assert_double_eq_tol(res.min, 52, tolerance);
    ck_assert_double_eq_tol(res.max, 168, tolerance);
    ck_assert_double_eq_tol(res.mean, 72, tolerance);
    ck_assert_double_eq_tol(res.median, 57, tolerance);
}
END_TEST

START_TEST(test_stat1)
{
    double a[] = {42};
    stats_t res;
    double tolerance = 0.00000001;

    stats(a, sizeof(a) / sizeof(a[0]), &res);

    ck_assert_double_eq_tol(res.min, 42, tolerance);
    ck_assert_double_eq_tol(res.max, 42, tolerance);
    ck_assert_double_eq_tol(res.mean, 42, tolerance);
    ck_assert_double_eq_tol(res.median, 42, tolerance);
}
END_TEST

START_TEST(test_stat2)
{
    double a[] = {1, 2, 3, 4};
    stats_t res;
    double tolerance = 0.00000001;

    stats(a, sizeof(a) / sizeof(a[0]), &res);

    ck_assert_double_eq_tol(res.min, 1, tolerance);
    ck_assert_double_eq_tol(res.max, 4, tolerance);
    ck_assert_double_eq_tol(res.mean, 2.5, tolerance);
    ck_assert_double_eq_tol(res.median, 2.5, tolerance);
}
END_TEST

START_TEST(test_stat3)
{
    double a[] = {1, 3};
    stats_t res;
    double tolerance = 0.00000001;

    stats(a, sizeof(a) / sizeof(a[0]), &res);

    ck_assert_double_eq_tol(res.min, 1, tolerance);
    ck_assert_double_eq_tol(res.max, 3, tolerance);
    ck_assert_double_eq_tol(res.mean, 2, tolerance);
    ck_assert_double_eq_tol(res.median, 2, tolerance);
}
END_TEST

START_TEST(test_stat4)
{
    double a[] = {42, 42.0, 42.0e0};
    stats_t res;
    double tolerance = 0.00000001;

    stats(a, sizeof(a) / sizeof(a[0]), &res);

    ck_assert_double_eq_tol(res.min, 42, tolerance);
    ck_assert_double_eq_tol(res.max, 42, tolerance);
    ck_assert_double_eq_tol(res.mean, 42, tolerance);
    ck_assert_double_eq_tol(res.median, 42, tolerance);
}
END_TEST

static Suite *
gdb_suite(void)
{
    Suite *s;
    TCase *tc_stat;

    s = suite_create("all");
    tc_stat = tcase_create("stat");

    tcase_add_test(tc_stat, test_stat0);
    tcase_add_test(tc_stat, test_stat1);
    tcase_add_test(tc_stat, test_stat2);
    tcase_add_test(tc_stat, test_stat3);
    tcase_add_test(tc_stat, test_stat4);
    suite_add_tcase(s, tc_stat);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = gdb_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
