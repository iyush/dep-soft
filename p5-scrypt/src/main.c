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

static void
split_hex_strings(unsigned char *m, unsigned char * g,  unsigned int len)
{
    const char *pos =  (char *) m;
    unsigned char val[len+1];

    /* source 
     * https://stackoverflow.com/questions/3408706/hexadecimal-string-to-byte-array-in-c 
     * */
     /* WARNING: no sanitization or error-checking whatsoever */
    for (size_t count = 0; count < sizeof val/sizeof *val; count++) {
        sscanf(pos, "%2hhx", &val[count]);
        pos += 2;
    }

    for(size_t count = 1; count < sizeof val/sizeof *val; count++)
    {
        g[count-1] = val[count];
    }
}

static void
parse_encrypted_ecb(unsigned char* c,uint32_t k)
{
    if (c[0] == '0' && c[1] == 'x') 
    {
        int len = strlen((char*) c);
        len -= 2;
        if (len % 2 == 1){
            fprintf(stderr, "scrypt: invalid hexadecimal cipher, cipher must be even in length\n" );
            exit(EXIT_FAILURE);
        }
        len /= 2;
        // printf("%d\n",len);
        unsigned char array_of_hex[len];
        split_hex_strings( (unsigned char *) c, array_of_hex, len);

        unsigned char m[len];
        sc_dec_ecb(array_of_hex, m, len, k);

        printf("Decryption using ecb: 0x");
        for(int i = 0; i < len; i++)
        {
            printf("%02x", m[i]);
        }
        printf("\t \"%s\"", m);
    } 
    else
    {
        fprintf(stderr, "scrypt: invalid hexadecimal cipher, cipher must be of format \"0x...\"\n");
        exit(EXIT_FAILURE);
    }

}


static void
parse_encrypted_cbc(unsigned char* c, uint32_t k, uint8_t iv)
{
    if (c[0] == '0' && c[1] == 'x') 
    {
        int len = strlen((char*) c);
        len -= 2;
        if (len % 2 == 1){
            fprintf(stderr, "scrypt: invalid hexadecimal cipher, cipher must be even in length\n" );
            exit(EXIT_FAILURE);
        }
        len /= 2;

        // printf("%d\n",len);
        unsigned char array_of_hex[len];
        split_hex_strings( (unsigned char *) c, array_of_hex, len);

        // decrypt(array_of_hex, len, k, iv);

        unsigned char m[len];
        sc_dec_cbc(array_of_hex, m, len, k, iv);

        printf("Decryption using cbc: 0x");
        for(int i = 0; i < len; i++)
        {
            printf("%02x", m[i]);
        }
        printf("\t \"%s\"", m);
    } 
    else
    {
        fprintf(stderr, "scrypt: invalid hexadecimal cipher, cipher must be of format \"0x...\"\n");
        exit(EXIT_FAILURE);
    }

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

int main(int argc, char *argv[])
{
    uint32_t k = 0x98267351;
    uint8_t iv = 0x42;

    int i;
    char c;
    int do_decryption = 0;

    while ((c = getopt(argc, argv, "i:k:hd")) != -1) {
	switch (c) {
	case 'i':
	    iv = getlong_or_die(optarg);
	    break;
	case 'k':
	    k = getlong_or_die(optarg);
	    break;
    case 'd':
        do_decryption = 1;
        break;
	case 'h':
	default:
	    printf("usage: scrypt [options] [-i iv] [-k key] \nOptions:\n  -d\tDecryption of provided encrypted key, provided encrypted key must be of format \"0x...\"\n");
	    break;
	}
    }
    argc -= optind;
    argv += optind;

    // printf("do decryption?  %d \n", do_decryption);
    for (i = 0; i < argc; i++) {
        if (do_decryption) {
            parse_encrypted_ecb((unsigned char *) argv[i], k);
        }else{
            test_ecb((unsigned char*) argv[i], k);
        }
        puts("");
    }

    for	(i = 0; i < argc; i++) {
        if (do_decryption) {
            parse_encrypted_cbc((unsigned char*) argv[i], k, iv);
        }else{
            test_cbc((unsigned char *) argv[i], k, iv);
        }
        puts("");
    }

    return EXIT_SUCCESS;
}
