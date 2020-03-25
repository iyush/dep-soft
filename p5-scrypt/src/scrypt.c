/*
 * scrypt/src/scrypt.c --
 */

#include <stdlib.h>

#include "scrypt.h"
#include "stdio.h"


uint8_t
sub(uint8_t b)
{
    //printf("We are taking %x \n", b);

    uint8_t lower = b << 4;
    lower = lower >> 4;
    uint8_t upper = b >> 4;

    //printf("Upper %x \n", upper);
    //printf("Lower %x \n", lower);

    uint8_t enc_upper = ((upper + 1) * 7) % 16;
    uint8_t enc_lower = ((lower + 1) * 7) % 16;

    //printf("enc upper %x \n", enc_upper);
    //printf("enc lower %x \n", enc_lower);

    uint8_t merged = enc_upper << 4;
    merged += enc_lower;

    //printf("Merged %x \n", merged);
    return merged;
}

uint8_t
key_step(uint8_t m, uint8_t k)
{
    return k ^ m;
}

uint8_t
rot_shift_left_2(uint8_t b)
{
    return (b << 2) | (b >> 6);
}

uint8_t
sc_enc8(uint8_t m, uint32_t k)
{

    uint8_t subbed;
    uint8_t xored;
    uint8_t rotated;
    // printf("we got m: %x\n", m);
    // printf("we got k: %x\n", k);


    uint8_t splittedkeys[4];
    uint8_t *vp = (uint8_t *) &k;

    // split 32 bits into 8 x 4 equal sized bits
    splittedkeys[3] = vp[0];
    splittedkeys[2] = vp[1];
    splittedkeys[1] = vp[2];
    splittedkeys[0] = vp[3];

    // printf("we splittedkeys: %x\n", splittedkeys[0]);
    // printf("we splittedkeys: %x\n", splittedkeys[1]);
    // printf("we splittedkeys: %x\n", splittedkeys[2]);
    // printf("we splittedkeys: %x\n", splittedkeys[3]);


    /* round 0 */

    // key step
    xored =  splittedkeys[0] ^ m;

    /* round 1 */

    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[1] ^ rotated;

    /* round 2 */

    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[2] ^ rotated;

    /* round 3 */
    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[3] ^ rotated;

    return xored;
}

uint8_t
sc_dec8(uint8_t m, uint32_t k)
{

    uint8_t subbed;
    uint8_t xored;
    uint8_t rotated;
    // printf("we got m: %x\n", m);
    // printf("we got k: %x\n", k);


    uint8_t splittedkeys[4];
    uint8_t *vp = (uint8_t *) &k;

    // split 32 bits into 8 x 4 equal sized bits
    splittedkeys[3] = vp[0];
    splittedkeys[2] = vp[1];
    splittedkeys[1] = vp[2];
    splittedkeys[0] = vp[3];

    // printf("we splittedkeys: %x\n", splittedkeys[0]);
    // printf("we splittedkeys: %x\n", splittedkeys[1]);
    // printf("we splittedkeys: %x\n", splittedkeys[2]);
    // printf("we splittedkeys: %x\n", splittedkeys[3]);


    /* round 0 */

    // key step
    xored =  splittedkeys[3] ^ m;

    /* round 1 */

    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[2] ^ rotated;

    /* round 2 */

    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[1] ^ rotated;

    /* round 3 */
    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored =  splittedkeys[0] ^ rotated;

    return xored;
}

void
sc_enc_ecb(unsigned char *m, unsigned char *c, size_t len, uint32_t k)
{
}

void
sc_dec_ecb(unsigned char *c, unsigned char *m, size_t len, uint32_t k)
{
}

void
sc_enc_cbc(unsigned char *m, unsigned char *c, size_t len, uint32_t k, uint8_t iv)
{
}

void
sc_dec_cbc(unsigned char *c, unsigned char *m, size_t len, uint32_t k, uint8_t iv)
{
}

