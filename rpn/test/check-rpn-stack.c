/*
 * rpn/test/check-rpn.c --
 */

/*
 * Code Contributions made by:
 * Aayush Sharma Acharya
 * Drishti Maharjan
*/


#include <stdlib.h>
#include <check.h>

#include "rpn-stack.h"

START_TEST(test_rpn_stack0)
{
    rpn_stack_t* stk;
    int data;
    int a[] = { 1 };

    stk = rpn_stack_new();

    rpn_stack_push(stk, &a[0]);
    data = (* (int *) rpn_stack_peek(stk));
    rpn_stack_del(stk);

    ck_assert_int_eq(data, a[0]);
}
END_TEST

START_TEST(test_rpn_stack1)
{
    rpn_stack_t* stk;
    int data;
    int a[] = { 1, 2, 3 };

    stk = rpn_stack_new();

    rpn_stack_push(stk, &a[0]);
    rpn_stack_push(stk, &a[1]);
    rpn_stack_push(stk, &a[2]);

    data = *( (int *) rpn_stack_pop(stk));
    ck_assert_int_eq(data, a[2]);

    data = *( (int *) rpn_stack_pop(stk));
    ck_assert_int_eq(data, a[1]);

    data = *( (int *) rpn_stack_pop(stk));
    ck_assert_int_eq(data, a[0]);

    rpn_stack_del(stk);
}
END_TEST

START_TEST(test_rpn_stack2)
{
    rpn_stack_t* stk;
    int a[] = { 1, 2, 3 };

    stk = rpn_stack_new();

    rpn_stack_push(stk, &a[0]);
    rpn_stack_push(stk, &a[1]);
    rpn_stack_push(stk, &a[2]);
    int empty = rpn_stack_empty(stk);
    ck_assert_int_eq(empty, 0);

    rpn_stack_del(stk);
}
END_TEST

START_TEST(test_rpn_stack3)
{
    rpn_stack_t* stk;
    int a[] = { 1 };

    stk = rpn_stack_new();

    rpn_stack_push(stk, &a[0]);
    (void) rpn_stack_pop(stk);
    int empty = rpn_stack_empty(stk);
    ck_assert_int_eq(empty, 1);

    rpn_stack_del(stk);
}
END_TEST

static Suite*
gdb_suite(void)
{
    Suite *s;
    TCase *tc_rpn_stack;

    s = suite_create("all");
    tc_rpn_stack = tcase_create("stat");

    tcase_add_test(tc_rpn_stack, test_rpn_stack0);
    tcase_add_test(tc_rpn_stack, test_rpn_stack1);
    tcase_add_test(tc_rpn_stack, test_rpn_stack2);
    tcase_add_test(tc_rpn_stack, test_rpn_stack3);
    suite_add_tcase(s, tc_rpn_stack);

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
