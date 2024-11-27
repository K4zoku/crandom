#include "test_utils.h"

static int generator(random_engine_t * engine, va_list ap) {
    const double probability = va_arg(ap, double);
    int result = (int)bernoulli_distribution(engine, probability); // actual random distribution call
    return result;
}

static wchar_t * label(int i) {
    return i ? L"True" : L"False";
}

int main(void) {
    init();
    random_engine_t *engine = Xoshiro256ssEngine.ctor();
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    wprintf(L"Bernoulli Distribution\n");
    const int samples = 1000000;

    const double probability = uniform_real_distribution(engine, 0, 1);
    wprintf(L"Randomly choosen probability: %.2g\n", probability);

    int results[2] = {0, 0};
    generate_samples(engine,results, 2, samples, generator, probability);
    display_histogram(results, 2, samples, label);
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    random_engine_dtor(engine);
    return 0;
}
