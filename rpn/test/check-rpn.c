/*
 * rpn/test/check-rpn.c --
 */

/*
 * Code Contributions made by:
 * Aayush Sharma Acharya
 * Drishti Maharjan
*/

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "rpn.h"

START_TEST(test_rpn0)
{
    const char *token[] =
        {
            "42",
            "2 3 +",
            "2 3 *",
            "2 3 + 2 *",
            "6 3 /",
            "foo",
            "2 4",
            "6 6 6 - /",
            "2 +",
        };

    char *result[] = {
        "42",
        "5",
        "6",
        "10",
        "2",
        "Invalid token",
        "missing operator",
        "arithmetic error",
        "missing operand"
    };

    for (int i = 0; i < 9; i++)
    {
        char *res = (char *) malloc(sizeof(char) * 255);

        if (res == NULL)
        {
            perror("Allocation error\n");
            exit(EXIT_FAILURE);
        }
        (void) rpn_eval_expr(token[i], &res);
        ck_assert_str_eq(result[i], res);
        free(res);
    }
}
END_TEST

static Suite *
gdb_suite(void)
{
    Suite *s;
    TCase *tc_rpn;

    s = suite_create("all");
    tc_rpn = tcase_create("rpn");

    tcase_add_test(tc_rpn, test_rpn0);
    suite_add_tcase(s, tc_rpn);

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
