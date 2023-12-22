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

    mpz_clear(temp);
}

void algo_quadratic_sieve(char *numberStr)
{
    unsigned long int i, j;
    mpz_t B, M, n, sieveBound, result, *sieve;
    QuadraticSievePair pairP, pairQ;
    mpz_t x1, x2;

    mpz_inits(B, M, n, sieveBound, result, NULL);
    mpz_set_str(n, numberStr, 10);
    mpz_sqrt(B, n);
    mpz_add_ui(B, B, 1);
    mpz_pow_ui(M, B, 2);
    mpz_sub(M, M, n);
    mpz_sqrt(sieveBound, M);
    mpz_add_ui(sieveBound, sieveBound, 1);
    sieve = (mpz_t*)malloc(mpz_get_ui(sieveBound) * sizeof(mpz_t));

    for (i = 2; i < mpz_get_ui(sieveBound); i++)
    {
        mpz_init(sieve[i]);
        if (mpz_cmp_ui(sieve[i], 0) == 0) {
            for (j = i * i; j < mpz_get_ui(sieveBound); j += i)
                mpz_set_ui(sieve[j], 1);

            if (mpz_divisible_ui_p(M, i) != 0) {
                mpz_t p, q;
                mpz_inits(p, q, NULL);
                mpz_divexact_ui(p, M, i);
                mpz_divexact_ui(q, M, i);

                mpz_inits(pairP.x, pairP.y, pairQ.x, pairQ.y, NULL);

                findSmoothPair(&pairP.x, &pairP.y, p, B);
                findSmoothPair(&pairQ.x, &pairQ.y, q, B);

                mpz_inits(x1, x2, NULL);

                if (mpz_cmp_ui(pairP.x, 0) > 0 && mpz_cmp_ui(pairQ.x, 0) > 0) {
                    mpz_mul(result, pairP.x, pairQ.x);
                    mpz_mul(q, n, pairP.y);
                    mpz_mul(q, q, pairQ.y);
                    mpz_add(result, result, q);
                    mpz_mod(result, result, n);

                    mpz_mul(x1, pairP.x, pairQ.y);
                    mpz_mul(q, pairP.y, pairQ.x);
                    mpz_add(x1, x1, q);
                    mpz_mod(x1, x1, n);

                    mpz_clears(p, q, pairP.x, pairP.y, pairQ.x, pairQ.y, x1, x2, NULL);
                    break;
                }

                mpz_clears(p, q, pairP.x, pairP.y, pairQ.x, pairQ.y, x1, x2, NULL);
            }
        }
    }

    mpz_clears(B, M, sieveBound, NULL);

    if (mpz_cmp_ui(result, 1) == 0 || mpz_cmp(result, n) == 0)
        printf("Failed to factorize the number.\n");
    else {
        printf("The number ");
        mpz_out_str(stdout, 10, n);
        printf(" is a product of the factors ");
        mpz_out_str(stdout, 10, result);
        printf(" and ");
        mpz_divexact(result, n, result);
        mpz_out_str(stdout, 10, result);
        printf(".\n");
    }

    mpz_clears(n, result, NULL);
    free(sieve);
}
