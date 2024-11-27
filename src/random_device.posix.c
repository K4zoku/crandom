#ifndef _WIN32

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#include "crandom.h"

struct RandomDevice {
  int fd;
};

size_t random_device_read(random_device_t *instance, void *buffer,
                          size_t count) {
  return read(instance->fd, buffer, count);
}

void random_device_dtor(random_device_t *instance) {
  close(instance->fd);
  free(instance);
}

random_device_t *random_device_ctor_token(const char *token) {
  random_device_t *rd = (random_device_t *)malloc(sizeof(random_device_t));
  rd->fd = open(token, O_RDONLY);
  if (rd->fd == -1) {
    free(rd);
    return NULL;
  }
  return rd;
}

random_device_t *random_device_ctor(void) {
  return random_device_ctor_token("/dev/urandom");
}

#endif /* _WIN32 */
