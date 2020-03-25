/*
 * scrypt/test/check-scrypt.c --
 */

#include <stdlib.h>
#include <stdio.h>
#include <check.h>

#include "scrypt.h"

START_TEST(test_sc_enc_dec)
{
    uint16_t x;
    uint32_t k = 0x98267351;
    
    for (x = 0; x <= 0xff; x++) {
        ck_assert_int_eq(x, sc_dec8(sc_enc8(x, k), k));
    }
}
END_TEST

START_TEST(test_sc_ecb)
{
    uint32_t k = 0x98267351;
    unsigned char *m = (unsigned char *) "sads";
    unsigned char c[] = {0xd3, 0xf2, 0xa0, 0xd3};
    size_t len = strlen((char *) m);
    unsigned char b[len];

    sc_enc_ecb(m, b, len, k);
    ck_assert_int_eq(memcmp(b, c, len), 0);
}
END_TEST

START_TEST(test_sc_cbc)
{
    uint32_t k = 0x98267351;
    uint8_t iv = 0x42;
    unsigned char *m = (unsigned char *) "sads";
    unsigned char c[] = {0xd7, 0xad, 0x78, 0x74};
    size_t len = strlen((char *) m);
    unsigned char b[len];
    
    sc_enc_cbc(m, b, len, k, iv);
    ck_assert_int_eq(memcmp(b, c, len), 0);
}
END_TEST

START_TEST(test_sc_ecb_roundtrip)
{
    uint32_t k = 0x98267351;
    size_t len;
    unsigned char *msgs[] = {
                          (unsigned char *) "this is a test",
                          (unsigned char *) "aba",
                          NULL
    };
    int i;

    for (i = 0; msgs[i]; i++) {
	unsigned char *m = msgs[i];
        len = strlen((char *) m);
	unsigned char c[len];
	unsigned char d[len];
	
	sc_enc_ecb(m, c, len, k);
	sc_dec_ecb(c, d, len, k);
	ck_assert_int_eq(memcmp(m, d, len), 0);
    }
}
END_TEST

START_TEST(test_sc_cbc_roundtrip)
{
    uint32_t k = 0x98267351;
    unsigned char *msgs[] = {
                          (unsigned char *) "this is a test",
                          (unsigned char *) "aba",
                          NULL
    };
    size_t len;
    int i;
    uint8_t iv = 0x42;

    for (i = 0; msgs[i]; i++) {
	unsigned char *m = msgs[i];
	len = strlen((char *) m);
	unsigned char c[len];
	unsigned char d[len];
	
	sc_enc_cbc(m, c, len, k, iv);
	sc_dec_cbc(c, d, len, k, iv);
	ck_assert_int_eq(memcmp(m, d, len), 0);
    }
}
END_TEST

static Suite*
gdb_suite(void)
{
    Suite *s;
    TCase *tc_scrypt;

    s = suite_create("all");
    tc_scrypt = tcase_create("scrypt");

    tcase_add_test(tc_scrypt, test_sc_enc_dec);
    tcase_add_test(tc_scrypt, test_sc_ecb);
    tcase_add_test(tc_scrypt, test_sc_cbc);
    tcase_add_test(tc_scrypt, test_sc_ecb_roundtrip);
    tcase_add_test(tc_scrypt, test_sc_cbc_roundtrip);
    suite_add_tcase(s, tc_scrypt);
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
