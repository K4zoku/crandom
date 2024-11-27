#ifdef _WIN32

#include <stdint.h>
#include <stdio.h>

#include <windows.h>

#include "crandom.h"

struct RandomDevice {
    HCRYPTPROV hCryptProv;
};

random_device_t *random_device_ctor(void) {
    random_device_t *rd = (random_device_t *)malloc(sizeof(random_device_t));
    if (!CryptAcquireContext(&rd->hCryptProv, NULL, NULL, PROV_RSA_FULL,
                             CRYPT_VERIFYCONTEXT)) {
      fprintf(stderr, "Error acquiring crypto context: %ld\n", GetLastError());
      exit(1);
    }
    return rd;
}

random_device_t *random_device_ctor_token(const char *token) {
    (void) token; // unused
    return random_device_ctor();
}

size_t random_device_read(random_device_t *instance, void *buffer,
                          size_t count) {
  if (!CryptGenRandom(rd->hCryptProv, size, buffer)) {
    return -1;
  }
  return size;
}

void random_device_dtor(random_device_t *rd) {
  CryptReleaseContext(rd->hCryptProv, 0);
  free(rd);
}

#endif /* _WIN32 */
