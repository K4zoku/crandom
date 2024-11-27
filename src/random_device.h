#pragma once
#ifndef H_RANDOM_DEVICE_INCLUDED
#define H_RANDOM_DEVICE_INCLUDED

#include "crandom.h"

random_engine_t *random_device_engine_ctor(void);
uint64_t random_device_engine_next(random_engine_t *engine);
void random_device_engine_dtor(random_engine_t *engine);

#endif /* H_RANDOM_DEVICE_INCLUDED */
