#include "rsa.h"

void algo_trivial_division_s(size_t number)
{
	size_t divisor;
	size_t max_divisor;
	size_t p = 0, q = 0;

	max_divisor = (size_t) sqrt(number);

	for (divisor = 2; (q == 0 && divisor <= max_divisor); divisor++)
	{
		if (number % divisor == 0)
		{
			p = divisor;
			q = number / divisor;
		}
	}

	if (p != 0 && q != 0)
	{ /* If factors are found */
		printf("%lu=%lu*%lu\n", number, q, p);
	}
}

void algo_trivial_division(char *numberStr)
{
    int base, success, q_cmp, div_cmp;
    mpz_t number, divisor, max_divisor, remainder, p, q;

    /* Initialize the pointers to the GMP data structure */
    mpz_init(number);
    mpz_init(divisor);
    mpz_init(max_divisor);
    mpz_init(remainder);
    mpz_init(p);
    mpz_init(q);

    /* Initialize the 2 factor variables to 0 */
    mpz_set_ui(p, 0);
    mpz_set_ui(q, 0);

    /* Convert the large number from string and store it in `number` variable */
    base = 10;
    success = mpz_set_str(number, numberStr, base);
    if (success != 0) {
        fprintf(stderr, "Error converting number string to GMP integer.\n");
        return;
    }

    /* Get the square root of our number, which represents the largest possible factor */
    mpz_sqrt(max_divisor, number);

    /* Start with divisor value of 2 */
    mpz_set_ui(divisor, 2);

    /* Initialize comparison variables */
    q_cmp = mpz_cmp_ui(q, 0);
    div_cmp = mpz_cmp(divisor, max_divisor);

    while (q_cmp == 0 && (div_cmp < 0 || div_cmp == 0))
    {
        mpz_mod(remainder, number, divisor);
        if (mpz_cmp_ui(remainder, 0) == 0)
        {
            mpz_set(p, divisor);
            mpz_div(q, number, divisor);
            break;
        }
        mpz_add_ui(divisor, divisor, 1);
        div_cmp = mpz_cmp(divisor, max_divisor);
    }

    /* Print the factors in the format: n=p*q */
    printf("%s=", numberStr);
    mpz_out_str(stdout, base, q);
    putchar('*');
    mpz_out_str(stdout, base, p);
    putchar('\n');

    /* Clear the allocated memory */
    mpz_clear(number);
    mpz_clear(divisor);
    mpz_clear(max_divisor);
    mpz_clear(remainder);
    mpz_clear(p);
    mpz_clear(q);
}
