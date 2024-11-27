#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "crandom.h"

int uniform_int_distribution(random_engine_t *engine, int min, int max) {
  return min + (int)(random_engine_next(engine) % (uint64_t)(max - min + 1));
}

double uniform_real_distribution(random_engine_t *engine, double min,
                                 double max) {
  return min + (max - min) * random_engine_next(engine) / (double)UINT64_MAX;
}

bool bernoulli_distribution(random_engine_t *engine, double p) {
  assert(0.0 <= p && p <= 1.0);
  return uniform_real_distribution(engine, 0.0, 1.0) < p;
}

uint64_t binomial_distribution(random_engine_t *engine, uint64_t n, double p) {
  assert(0.0 <= p && p <= 1.0);
  uint64_t result = 0;
  for (uint64_t i = 0; i < n; ++i) {
    if (bernoulli_distribution(engine, p)) {
      result++;
    }
  }
  return result;
}

uint64_t poisson_distribution(random_engine_t *engine, double lambda) {
  assert(lambda > 0);

  uint64_t k = 0;
  double L = exp(-lambda);
  double p = 1.0;

  do {
    k++;
    p *= uniform_real_distribution(engine, 0.0, 1.0);
  } while (p > L);

  return k - 1;
}

double normal_distribution(random_engine_t *engine, double mu, double sigma) {
  double u1 = uniform_real_distribution(engine, 0.0, 1.0);
  double u2 = uniform_real_distribution(engine, 0.0, 1.0);
  double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * atan(1) * 4 * u2);
  double r = mu + z0 * sigma;
  return r;
}

size_t discrete_distribution(random_engine_t *engine, const double *weights,
                          size_t size) {
  double total_weight = 0.0;
  for (size_t i = 0; i < size; ++i) {
    assert(weights[i] >= 0);
    total_weight += weights[i];
  }
  double random_value = uniform_real_distribution(engine, 0.0, total_weight);
  double cumulative_weight = 0.0;
  for (size_t i = 0; i < size; ++i) {
    cumulative_weight += weights[i];
    if (random_value < cumulative_weight) {
      return i;
    }
  }
  return size - 1;
}
