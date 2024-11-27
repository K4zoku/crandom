#include <stdlib.h>
#include <string.h>

#include "test_utils.h"

static int generator(random_engine_t * engine, va_list ap) {
    const uint64_t n = va_arg(ap, uint64_t);
    const double p = va_arg(ap, double);
    int result = (int)round(binomial_distribution(engine, n, p)); // actual random distribution call
    return result;
}

wchar_t * label(int i) {
    static wchar_t buffer[10];
    swprintf(buffer, 10, L"#%d", i + 1);
    return buffer;
}

int main(void) {
    init();
    random_engine_t *engine = Xoshiro256ssEngine.ctor();
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    wprintf(L"Binomial Distribution\n");
    const int samples = 1000000;

    const uint64_t n = uniform_int_distribution(engine, 5, 20);
    const double p = uniform_real_distribution(engine, 0.0, 1.0);
    wprintf(L"Randomly choosen trials: %llu\n", n);
    wprintf(L"Randomly choosen probability: %.2g\n", p);
    size_t len = n + 1;
    int results[len];
    memset(results, 0, sizeof(results));

    generate_samples(engine, results, len, samples, generator, n, p);
    display_zero_in_histogram = true;
    display_histogram(results, len, samples, label);
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    random_engine_dtor(engine);
    return 0;
}
