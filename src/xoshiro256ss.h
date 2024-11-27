#pragma once
#ifndef H_XOSHIRO256SS_INCLUDED
#define H_XOSHIRO256SS_INCLUDED

#include "crandom.h"

random_engine_t *xoshiro256ss_ctor_full(const uint64_t seed[4]);
random_engine_t *xoshiro256ss_ctor_seed(const uint64_t seed);
random_engine_t *xoshiro256ss_ctor_rd(random_device_t *rd);
random_engine_t *xoshiro256ss_ctor(void);
uint64_t xoshiro256ss_next(random_engine_t *engine);
void xoshiro256ss_dtor(random_engine_t *engine);

#endif /* H_XOSHIRO256SS_INCLUDED */
