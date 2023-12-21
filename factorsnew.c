#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
    FILE *stream;
    long long char *line = NULL;
    size_t len = 0;
    mpz_t number, counter, divisor;
    ssize_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        mpz_init(number);
        mpz_init(counter);
        mpz_init(divisor);

        mpz_set_str(number, line, 10);

        mpz_nextprime(divisor, divisor);
        mpz_mod(counter, number, divisor);

        if (mpz_cmp_ui(counter, 0) == 0) {
            mpz_divexact(counter, number, divisor);
            gmp_printf("%Zd=%Zd*%Zd\n", number, counter, divisor);
        }
        mpz_clear(divisor);
        mpz_clear(number);
        mpz_clear(counter);
    }

    free(line);
    fclose(stream);
    
    
    

    exit(EXIT_SUCCESS);
}
