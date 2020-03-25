/*
 * scrypt/src/scrypt.c --
 */

#include <stdlib.h>

#include "scrypt.h"
#include "stdio.h"
#include "math.h"
uint8_t
f(uint8_t b)
{
    return ((b + 1) * 7) % 16;
}

uint8_t
f_inv(uint8_t b)
{
    uint8_t x;
    if (b >= 0 && b <= 15)
    {
        if (b % 2 != 0)
        {

            x = abs(b - 7);
            if (b >= 9 && b <= 13)
            {
                if (b == 9)
                {
                    return 14;
                }

                if (b == 13)
                {
                    return 10;
                }
                uint8_t i;
                i = 13 - b;
                x += 4 * i;
            }
        }
        else
        {
            x = (14 - b) + 1;
        }

                return x;
    }

    else
    {
        return EXIT_FAILURE;
    }

    /*
    switch(b)
    {
        case 7:
            return 0;
            break;
        case 14:
            return 1;
        case 5:
            return 2;
        case 12:
            return 3;
        case 3:
            return 4;
        case 10:
            return 5;
        case 1:
            return 6;
        case 8:
            return 7;
        case 15:
            return 8;
        case 6:
            return 9;
        case 13:
            return 10;
        case 4:
            return 11;
        case 11:
            return 12;
        case 2:
            return 13;
        case 9:
            return 14;
        case 0:
            return 15;
        default:
            printf("Lookup not found");
            return EXIT_FAILURE;
    }
    */
}

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
sub_inverse(uint8_t b)
{
    //printf("We are taking %x \n", b);

    uint8_t lower = b << 4;
    lower = lower >> 4;
    uint8_t upper = b >> 4;

    //printf("Upper %x \n", upper);
    //printf("Lower %x \n", lower);

    uint8_t enc_upper = f_inv(upper);
    uint8_t enc_lower = f_inv(lower);

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
rot_shift_right_2(uint8_t b)
{
    return (b >> 2) | (b << 6);
}

uint8_t
sc_enc8(uint8_t m, uint32_t k)
{

    uint8_t subbed;
    uint8_t xored;
    uint8_t rotated;
    // printf("we got c: %x\n\n", m);
    // printf("we got k: %x\n", k);

    uint8_t splittedkeys[4];
    uint8_t *vp = (uint8_t *)&k;

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
    xored = splittedkeys[0] ^ m;

    /* round 1 */

    // substitution step
    subbed = sub(xored);

    // permutation step
    rotated = rot_shift_left_2(subbed);

    // key step
    xored =  splittedkeys[1] ^ rotated;
    // printf("HERE %x \n", xored);

    // printf("HERE %x \n", xored);

    // round 2

    // substitution step
    subbed = sub(xored);
    // permutation step
    rotated = rot_shift_left_2(subbed);
    // key step
    xored = splittedkeys[2] ^ rotated;

    // round 3

    // substitution step
    subbed = sub(xored);
    // permutation step
    // rotated = rot_shift_left_2(subbed);
    // key step
    xored = splittedkeys[3] ^ subbed;

    return xored;
}

uint8_t
sc_dec8(uint8_t m, uint32_t k)
{

    uint8_t subbed;
    uint8_t xored;
    uint8_t rotated;
    // printf("we got k: %x\n", k);
    uint8_t splittedkeys[4];
    uint8_t *vp = (uint8_t *)&k;

    // split 32 bits into 8 x 4 equal sized bits
    splittedkeys[0] = vp[0];
    splittedkeys[1] = vp[1];
    splittedkeys[2] = vp[2];
    splittedkeys[3] = vp[3];

    // printf("we splittedkeys: %x\n", splittedkeys[0]);
    // printf("we splittedkeys: %x\n", splittedkeys[1]);
    // printf("we splittedkeys: %x\n", splittedkeys[2]);
    // printf("we splittedkeys: %x\n", splittedkeys[3]);

    /* round 0 */

    // key step
    xored = splittedkeys[0] ^ m;

    /* round 1 */

    // substitution step
    subbed = sub_inverse(xored);
    // key step
    xored = splittedkeys[1] ^ subbed;
    // permutation step
    rotated = rot_shift_right_2(xored);

    /* round 2 */

    // substitution step
    subbed = sub_inverse(rotated);
    // key step
    xored = splittedkeys[2] ^ subbed;
    // permutation step
    rotated = rot_shift_right_2(xored);

    /* round 3 */
    // substitution step
    subbed = sub_inverse(rotated);
    // permutation step
    // rotated = rot_shift_left_2(subbed);
    // key step
    xored = splittedkeys[3] ^ subbed;

    return xored;
}

void sc_enc_ecb(unsigned char *m, unsigned char *c, size_t len, uint32_t k)
{
    for (int i = 0; i < len; i++) 
    {
        // printf("We got %c\n", m[i]);
        uint8_t enc = sc_enc8( (uint8_t) m[i], k);
        c[i] = enc;
    }
}

void sc_dec_ecb(unsigned char *c, unsigned char *m, size_t len, uint32_t k)
{
    for (int i = 0; i < len; i++) 
    {
        // printf("We got %x\n", c[i]);
        uint8_t dec = sc_dec8( (uint8_t) c[i], k);
        m[i] = dec;
    }
}

void sc_enc_cbc(unsigned char *m, unsigned char *c, size_t len, uint32_t k, uint8_t iv)
{
    uint8_t plain_text_xored;
    for (int i = 0; i < len; i++) 
    {
        plain_text_xored =  m[i] ^ iv;
        iv = sc_enc8( (uint8_t) plain_text_xored, k);
        c[i] = iv;
    }

}

void sc_dec_cbc(unsigned char *c, unsigned char *m, size_t len, uint32_t k, uint8_t iv)
{
    for (int i = 0; i < len; i++) 
    {
        // printf("We got %x\n", c[i]);
        uint8_t dec = sc_dec8( (uint8_t) c[i], k);
        dec = dec ^ iv;
        m[i] = dec;

        iv = c[i];
    }
}
