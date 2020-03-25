/*
 * scrypt/src/scrypt.h --
 */

#ifndef _SCRYPT_H
#define _SCRYPT_H

#include <stdint.h>

/**
 * \brief Encrypt an 8-bit cleartext using a 32-bit key.
 *
 * \param m 8-bit cleartext. 
 * \param k 32-bit key.
 * \result 8-bit ciphertext.
 */

uint8_t
sc_enc8(uint8_t m, uint32_t k);

/**
 * \brief Decrypt an 8-bit ciphertext using a 32-bit key.
 *
 * \param m 8-bit ciphertext. 
 * \param k 32-bit key.
 * \result 8-bit cleartext.
 */

uint8_t
sc_dec8(uint8_t c, uint32_t k);

/**
 * \brief Encrypt a variable-length cleartext using a 32-bit key in ECB mode.
 *
 * \param m cleartext.
 * \param c ciphertext.
 * \param len length of the cleartext and ciphertext buffers.
 * \param k 32-bit key.
 */

void
sc_enc_ecb(unsigned char *m, unsigned char *c, size_t len, uint32_t k);

/**
 * \brief Decrypt variable-length ciphertext using a 32-bit key in ECB mode.
 *
 * \param c ciphertext.
 * \param m cleartext.
 * \param len length of the ciphertext and cleartext buffers.
 * \param k 32-bit key.
 */

void
sc_dec_ecb(unsigned char *c, unsigned char *m, size_t len, uint32_t k);

/**
 * \brief Encrypt a variable-length cleartext using a 32-bit key in CBC mode.
 *
 * \param m cleartext.
 * \param c ciphertext.
 * \param len length of the cleartext and ciphertext buffers.
 * \param k 32-bit key.
 * \param iv 8-bit initialization vector.
 */

void
sc_enc_cbc(unsigned char *m, unsigned char *c, size_t len,
	   uint32_t k, uint8_t iv);

/**
 * \brief Decrypt variable-length ciphertext using a 32-bit key in CBC mode.
 *
 * \param m ciphertext.
 * \param m cleartext.
 * \param len length of the ciphertext.
 * \param k 32-bit key.
 * \param iv 8-bit initialization vector.
 */

void
sc_dec_cbc(unsigned char *c, unsigned char *m, size_t len,
	   uint32_t k, uint8_t iv);

#endif
