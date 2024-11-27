#include <string.h>

#include "test_utils.h"

static int generator(random_engine_t * engine, va_list ap) {
    const int offset = va_arg(ap, int);
    const int mean = va_arg(ap, int);
    int result = (int)round(normal_distribution(engine, mean, 2)); // actual random distribution call
    return result + offset;
}

int offset = 0;

wchar_t * label(int i) {
    static wchar_t buffer[8];
    swprintf(buffer, 8, L"%d", i - offset);
    return buffer;
}

int main(void) {
    init();
    random_engine_t *engine = Xoshiro256ssEngine.ctor();
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    wprintf(L"Normal Distribution\n");

    const int min = 1;
    const int max = 6;
    const int samples = 1000000;

    const int mean = uniform_int_distribution(engine, min, max); // Randomly choosen mean
    wprintf(L"Randomly choosen mean: %d\n", mean);
    const int len = (max - min) * 4;
    offset = (int)(max - min);
    int results[len];
    memset(results, 0, sizeof(results));
    generate_samples(engine,results, len, samples, generator, offset, mean);
    display_histogram(results, len, samples, label);
    wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

    random_engine_dtor(engine);
    return 0;
}
