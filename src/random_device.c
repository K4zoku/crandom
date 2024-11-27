#include <stdio.h>
#include <stdlib.h>

#include "random_device.h"

size_t random_device_read_s(random_device_t *rd, void *buffer,
                            size_t buffer_size, size_t count) {
  return random_device_read(rd, buffer,
                            count < buffer_size ? count : buffer_size);
}

random_engine_t * random_device_engine_ctor(void) {
  random_device_t * data = random_device_ctor();
  if (data == NULL) {
    return NULL;
  }
  random_engine_t * engine = random_engine_ctor((random_engine_spec_t) &RandomDeviceEngine, data);
  return engine;
}

void random_device_engine_dtor(random_engine_t *engine) {
  random_device_t * rd = random_engine_data(engine);
  random_device_dtor(rd);
}

uint64_t random_device_engine_next(random_engine_t *engine) {
  uint64_t result;
  random_device_t *instance = random_engine_data(engine);
  random_device_read_s(instance, &result, sizeof(result), sizeof(result));
  return result;
}

const struct RandomEngineSpec RandomDeviceEngine = {
    .name = "RandomDevice",
    .ctor = random_device_engine_ctor,
    .dtor = random_device_engine_dtor,
    .next = random_device_engine_next,
};
