#pragma once
#ifndef H_XOSHIRO256SS_INCLUDED
#define H_XOSHIRO256SS_INCLUDED

#include "crandom.h"

/**
* @brief Construct a new xoshiro256** random number generator with a full 256-bit seed.
*
* @param seed The 256-bit seed.
* @return random_engine_t* The constructed random number generator.
*
* @ingroup xoshiro256ss
*/
random_engine_t *xoshiro256ss_ctor_full(const uint64_t seed[4]);

/**
* @brief Construct a new xoshiro256** random number generator with a 64-bit seed.
*
* @note The seed is expanded to a full 256-bit seed using the splitmix64 algorithm.
*
* @param seed The 64-bit seed.
* @return random_engine_t* The constructed random number generator.
*
* @ingroup xoshiro256ss
*/
random_engine_t *xoshiro256ss_ctor_seed(const uint64_t seed);

/**
* @brief Construct a new xoshiro256** random number generator with a random seed generated from the given random device.
*
* @param rd The random device.
* @return random_engine_t* The constructed random number generator.
*
* @ingroup xoshiro256ss
*/
random_engine_t *xoshiro256ss_ctor_rd(random_device_t *rd);

/**
* @brief Construct a new xoshiro256** random number generator with a random seed generated from the default random device.
*
* @return random_engine_t* The constructed random number generator.
*
* @ingroup xoshiro256ss
*/
random_engine_t *xoshiro256ss_ctor(void);

/**
* @brief Generate the next random number from the xoshiro256** random number generator.
*
* @param engine The random number generator.
* @return uint64_t The next random number.
*
* @ingroup xoshiro256ss
*/
uint64_t xoshiro256ss_next(random_engine_t *engine);

/**
* @brief Release the resources used by the xoshiro256** random number generator.
*
* @param engine The random number generator.
*
* @ingroup xoshiro256ss
*/
void xoshiro256ss_dtor(random_engine_t *engine);

#endif /* H_XOSHIRO256SS_INCLUDED */
