#include <stdlib.h>
#include <string.h>

#include "test_utils.h"

static int generator(random_engine_t *engine, va_list ap) {
  const double *weights = va_arg(ap, double *);
  const size_t size = va_arg(ap, size_t);
  int result = (int)round(discrete_distribution(engine, weights, size));
  return result;
}

int main(void) {
  init();
  random_engine_t *engine = Xoshiro256ssEngine.ctor();
  wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
  wprintf(L"Discrete Distribution\n");

  const int samples = 1000000;

  const size_t weights_size = uniform_int_distribution(engine, 4, 10);
  double weights[weights_size];
  double sum = 0.0;

  for (size_t i = 0; i < weights_size; i++) {
      weights[i] = uniform_real_distribution(engine, 0.0, 100.0);
      sum += weights[i];
  }
  // Normalize the weights so that they sum up to 100
  for (size_t i = 0; i < weights_size; i++) {
      weights[i] = (weights[i] / sum) * 100.0;
  }

  wprintf(L"Randomly choosen weights: \n");
  for (size_t i = 0; i < weights_size - 1; i++) {
    wprintf(L"%*d  ", 6, i);
  }
  wprintf(L"%*d\n", 6, weights_size - 1);

  wchar_t fmt[6];
  for (size_t i = 0; i < weights_size - 1; i++) {
    swprintf(fmt, 6, L"%.2g", weights[i]);
    wprintf(L"%*ls%%  ", 5, fmt);
  }
  swprintf(fmt, 6, L"%.2g", weights[weights_size - 1]);
  wprintf(L"%*ls%%\n", 5, fmt);

  int results[weights_size];
  memset(results, 0, sizeof(results));
  generate_samples(engine, results, weights_size, samples, generator, weights,
                   weights_size);
  display_histogram(results, weights_size, samples, default_label);
  wprintf(L"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");

  random_engine_dtor(engine);
  return 0;
}
