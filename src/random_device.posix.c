#ifndef _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include <assert.h>
#include <string.h>

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

static bool streq(const char * s1, const char * s2) {
  return strcmp(s1, s2) == 0;
}

static const char * SUPPORTED_TOKEN[] = {
  "/dev/urandom",
  "/dev/random",
};

random_device_t *random_device_ctor_token(const char *token) {
  bool is_default = token == NULL || token[0] == '\0' || streq(token, "default");
  if (is_default) {
    token = "/dev/urandom";
  } else {
    bool supported = false;
    for (size_t i = 0; i < sizeof(SUPPORTED_TOKEN) / sizeof(SUPPORTED_TOKEN[0]); i++) {
        if (streq(token, SUPPORTED_TOKEN[i])) {
            supported = true;
        }
    }
    if (!supported) {
        perror("random_device_ctor_token: unsupported token");
        exit(1);
        return NULL;
    }
  }
  int fd = open(token, O_RDONLY);
  if (fd == -1) {
    return NULL;
  }
  random_device_t *rd = (random_device_t *)malloc(sizeof(random_device_t));
  rd->fd = fd;
  return rd;
}

random_device_t *random_device_ctor(void) {
  return random_device_ctor_token(NULL);
}

#endif /* _WIN32 */
