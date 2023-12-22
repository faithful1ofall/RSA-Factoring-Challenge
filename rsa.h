#ifndef RSA_H
#define RSA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <math.h>
#include <gmp.h>

typedef struct
{
    mpz_t x;
    mpz_t y;
} QuadraticSievePair;

void factorize_any(FILE *file);
void factorize_rsa(FILE *file);
void algo_trivial_division_s(size_t number);
void algo_trivial_division(char *numberStr);

void gcd(mpz_t result, mpz_t a, mpz_t b);
void mod_pow(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus);
void findSmoothPair(mpz_t *x, mpz_t *y, mpz_t n, mpz_t B);
void algo_quadratic_sieve(char *numberStr);

void remove_newline(char *str, size_t len);

#endif /* RSA_H */
