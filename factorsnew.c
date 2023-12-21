#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    FILE *stream;
    char buffer[BUFFER_SIZE];
    mpz_t number, counter, divisor;
    size_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Initialize mpz_t variables outside the loop
    mpz_init(number);
    mpz_init(counter);
    mpz_init(divisor);

    while ((nread = fread(buffer, 1, BUFFER_SIZE, stream)) > 0) {
        mpz_import(number, nread, 1, sizeof(buffer[0]), 0, 0, buffer);

        mpz_nextprime(divisor, divisor);
        mpz_mod(counter, number, divisor);

        if (mpz_cmp_ui(counter, 0) == 0) {
            mpz_divexact(counter, number, divisor);
            gmp_printf("%Zd=%Zd*%Zd\n", number, counter, divisor);
        }
    }

    // Clear mpz_t variables outside the loop
    mpz_clear(divisor);
    mpz_clear(number);
    mpz_clear(counter);

    fclose(stream);

    exit(EXIT_SUCCESS);
}
