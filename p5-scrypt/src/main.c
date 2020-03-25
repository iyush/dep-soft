/*
 * scrypt/src/main.c --
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "scrypt.h"

/*

static void
printhex(char *prefix, unsigned char *s, size_t len)
{
    size_t i;
    int printable = 1;
    
    printf("%s", prefix);
    for (i = 0; i < len; i++) {
        printf("%02x", s[i]);
        printable = (printable && isprint(s[i]));
    }
    if (printable) {
        printf(" \"%.*s\"", (int) len, s);
    }
    puts("");
}

static void
test_ecb(unsigned char *m, uint32_t k)
{
    uint32_t nk = htonl(k);
    size_t len = strlen((char*) m);
    unsigned char c[len];
    unsigned char d[len];

    sc_enc_ecb(m, c, len, k);
    sc_dec_ecb(c, d, len, k);

    printf("b: ecb\n");
    printhex("k: 0x", (unsigned char *) &nk, 4);
    printhex("m: 0x", m, len);
    printhex("c: 0x", c, len);
    printhex("d: 0x", d, len);
}

static void
test_cbc(unsigned char *m, uint32_t k, uint8_t iv)
{
    uint32_t nk = htonl(k);
    size_t len = strlen((char *) m);
    unsigned char c[len];
    unsigned char d[len];
    
    sc_enc_cbc(m, c, len, k, iv);
    sc_dec_cbc(c, d, len, k, iv);

    printf("b: cbc\n");
    printhex("k: 0x", (unsigned char *) &nk, 4);
    printhex("i: 0x", (unsigned char *) &iv, 1);
    printhex("m: 0x", m, len);
    printhex("c: 0x", c, len);
    printhex("d: 0x", d, len);
}

static long
getlong_or_die(char *s)
{
    long l;
    char *end;

    l = strtol(optarg, &end, 0);
    if (!end || *end != 0) {
	fprintf(stderr, "scrypt: invalid number '%s'\n", optarg);
	exit(EXIT_FAILURE);
    }
    return l;
}
*/

int main(int argc, char *argv[])
{
    uint32_t k = 0x98267351;
    uint8_t iv = 0x42;



    printf("orig %x \n", iv);
    uint8_t enc = sc_enc8(iv, k);
    printf("encoded %x \n", enc);
    uint8_t dec = sc_dec8(enc, k);
    printf("decoded %x \n", dec);


    /*
    int i;
    char c;

    while ((c = getopt(argc, argv, "i:k:h")) != -1) {
	switch (c) {
	case 'i':
	    iv = getlong_or_die(optarg);
	    break;
	case 'k':
	    k = getlong_or_die(optarg);
	    break;
	case 'h':
	default:
	    printf("usage: scrypt [-i iv] [-k key]\n");
	    break;
	}
    }
    argc -= optind;
    argv += optind;

    for (i = 0; i < argc; i++) {
        test_ecb((unsigned char *) argv[i], k);
        puts("");
    }

    for	(i = 0; i < argc; i++) {
        test_cbc((unsigned char *) argv[i], k, iv);
        puts("");
    }

    */
    
    return EXIT_SUCCESS;
}
