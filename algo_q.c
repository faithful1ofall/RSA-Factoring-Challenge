#include "rsa.h"

void gcd(mpz_t result, mpz_t a, mpz_t b)
{
    mpz_gcd(result, a, b);
}

void mod_pow(mpz_t result, mpz_t base, mpz_t exponent, mpz_t modulus)
{
    mpz_powm(result, base, exponent, modulus);
}

void findSmoothPair(mpz_t *x, mpz_t *y, mpz_t n, mpz_t B)
{
    mpz_t temp;
    mpz_init(temp);

    mpz_sqrt(*x, n);
    mpz_set_ui(*y, 0);

    while (mpz_cmp(*y, B) < 0) {
        mpz_pow_ui(temp, *x, 2);
        mpz_sub(temp, temp, n);
        mpz_pow_ui(temp, *y, 2);
        if (mpz_cmp(temp, *y) == 0)
            break;
        mpz_add_ui(*x, *x, 1);
        mpz_add_ui(*y, *y, 1);
    }

    gmp_printf("Smooth pair found: x=%Zd, y=%Zd\n", *x, *y);

    mpz_clear(temp);
}

void quadraticSieveFactorization(mpz_t n)
{
    mpz_t B, M, sieveBound, result;
    QuadraticSievePair pairP, pairQ;

    mpz_inits(B, M, sieveBound, result, NULL);

    // Compute B (block size) and M (square of B)
    mpz_sqrt(B, n);
    mpz_add_ui(B, B, 1);
    mpz_pow_ui(M, B, 2);
    mpz_sub(M, M, n);

    // Compute the square root of M for the sieve bound
    mpz_sqrt(sieveBound, M);
    mpz_add_ui(sieveBound, sieveBound, 1);

    // Perform the sieve step and find smooth pairs
    // (The sieve array and additional code for this step are not shown in this snippet)

    // Example: Finding smooth pairs for p and q
    findSmoothPair(&pairP.x, &pairP.y, p, B);
    findSmoothPair(&pairQ.x, &pairQ.y, q, B);

    // Example: Checking if smooth pairs are valid and extracting factors
    if (mpz_cmp_ui(pairP.x, 0) > 0 && mpz_cmp_ui(pairQ.x, 0) > 0) {
        mpz_mul(result, pairP.x, pairQ.x);
        mpz_mul(q, n, pairP.y);
        mpz_mul(q, q, pairQ.y);
        mpz_add(result, result, q);
        mpz_mod(result, result, n);

        gmp_printf("Factorization Result: n=%Zd, result=%Zd\n", n, result);
    } else {
        printf("Failed to factorize the number.\n");
    }

    mpz_clears(B, M, sieveBound, result, NULL);
}
