#include <stdlib.h>

#include "test_utils.h"

static int generator(random_engine_t * engine, va_list ap) {
    const int lambda = va_arg(ap, double);
    int result = (int)round(poisson_distribution(engine, lambda)); // actual random distribution call
    return result;
}

int main(void) {
    init();
    random_engine_t *engine = Xoshiro256ssEngine.ctor();
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    wprintf(L"Poisson Distribution\n");
    const double min = 1.0, max = 10.0;
    const int samples = 1000000;

    const double lambda = uniform_real_distribution(engine, min, max);
    wprintf(L"Randomly choosen lambda: %.2g\n", lambda);

    const int len = (int)lambda * 4;
    int *results = (int *)calloc(len, sizeof(int));
    generate_samples(engine, results, len, samples, generator, lambda);
    display_histogram(results, len, samples, default_label);
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    random_engine_dtor(engine);
    free(results);
    return 0;
}
