#include "xoshiro256ss.h"
#include "crandom.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Xoshiro256ss {
  uint64_t state[4];
} xoshiro256ss_t;

random_engine_t *xoshiro256ss_ctor_full(const uint64_t seed[4]) {

  xoshiro256ss_t *data = malloc(sizeof(xoshiro256ss_t));
  if (!data) {
    return NULL;
  }
  random_engine_t *engine = random_engine_ctor((const random_engine_spec_t *)&Xoshiro256ssEngine, data);
  if (!engine) {
    free(data);
    return NULL;
  }
  memcpy(data->state, seed, sizeof(data->state));
  return engine;
}

random_engine_t *xoshiro256ss_ctor_seed(uint64_t seed) {
  return xoshiro256ss_ctor_full((uint64_t[]) {seed, seed, seed, seed});
}

random_engine_t *xoshiro256ss_ctor_rd(random_device_t *rd) {
  uint64_t seed[4];
  int result = random_device_read(rd, seed, sizeof(seed));
  if (result == -1)
    return NULL;
  return xoshiro256ss_ctor_full(seed);
}

random_engine_t *xoshiro256ss_ctor(void) {
  random_device_t *rd = random_device_ctor();
  random_engine_t *engine = xoshiro256ss_ctor_rd(rd);
  random_device_dtor(rd);
  return engine;
}

void xoshiro256ss_dtor(random_engine_t * engine) {
  free(random_engine_data(engine));
}

static uint64_t rotl(uint64_t x, uint64_t k) {
  return (x << k) | (x >> (64 - k));
}

uint64_t xoshiro256ss_next(random_engine_t *engine) {
  xoshiro256ss_t * data = random_engine_data(engine);
  uint64_t result = rotl(data->state[1] * 5, 7) * 9;
  uint64_t t = data->state[1] << 17;
  data->state[2] ^= data->state[0];
  data->state[3] ^= data->state[1];
  data->state[1] ^= data->state[2];
  data->state[0] ^= data->state[3];
  data->state[2] ^= t;
  data->state[3] = rotl(data->state[3], 45);
  return result;
}

const xoshiro256ss_spec_t Xoshiro256ssEngine = {
    .name = "Xoshiro256**",
    .ctor = xoshiro256ss_ctor,
    .ctor_full = xoshiro256ss_ctor_full,
    .ctor_seed = xoshiro256ss_ctor_seed,
    .ctor_rd = xoshiro256ss_ctor_rd,
    .next = xoshiro256ss_next,
    .dtor = xoshiro256ss_dtor,
};
