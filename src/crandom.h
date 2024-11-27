#pragma once
#include <stdio.h>
#ifndef H_RANDOM_INCLUDED
#define H_RANDOM_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Random Device type.
 *
 * @note
 * The internal structure is dependent on the platform. The user should not
 * be concerned with the internal structure of the random device.
 */
typedef struct RandomDevice random_device_t;

/**
 * @brief Construct a random device from a token.
 *
 * @param token A token to construct the random device from.
 *
 * @note Possible tokens on Unix-like systems: `/dev/urandom` and `/dev/random`.
 * default is `/dev/urandom`.
 *
 * @note On Windows, the token is ignored and the default random device is used.
 *
 * @return A pointer to the random device instance.
 */
random_device_t *random_device_ctor_token(const char *token);

/**
 * @brief Construct a random device.
 *
 * @return A pointer to the random device instance.
 */
random_device_t *random_device_ctor(void);

/**
 * @brief Read random data from the random device.
 *
 * @param instance A pointer to the random device instance.
 * @param buffer A pointer to the buffer to write the random data to.
 * @param count The number of bytes to read. Must be less than or equal to the
 * size of the buffer.
 * @return The number of bytes read.
 */
size_t random_device_read(random_device_t *instance, void *buffer,
                          size_t count);

/**
 * @brief Read random data from the random device in a safe manner.
 *
 * @param instance A pointer to the random device instance.
 * @param buffer A pointer to the buffer to write the random data to.
 * @param buffer_size The size of the buffer.
 * @param count The number of bytes to read.
 * @return The number of bytes read.
 */
size_t random_device_read_s(random_device_t *instance, void *buffer,
                            size_t buffer_size, size_t count);

/**
 * @brief Free memory used by the random device.
 *
 * @note
 * This function should release any resources allocated for the random
 * device.
 *
 * @param instance A pointer to the random device instance.
 */
void random_device_dtor(random_device_t *instance);

/* Random Engine */

/**
 * @brief Random engine type.
 *
 * @note
 * The internal structure of the random engine is hidden from the user.
 * However, the user can access the random engine's specification and data
 * through the `random_engine_get_spec` and `random_engine_data` functions.
 */
typedef struct RandomEngine random_engine_t;

typedef random_engine_t *(*random_engine_ctor_fn)(void);
typedef uint64_t (*random_engine_next_fn)(random_engine_t *instance);
typedef void (*random_engine_data_dtor_fn)(random_engine_t *instance);

/**
 * @brief Random engine specification structure.
 *
 * @note Defines the behavior and functions used to interact with a custom
 * random engine.
 */
 struct RandomEngineSpec {
  const char *name;           ///< The name of the random engine.
  random_engine_ctor_fn ctor; ///< Constructor function to create an instance of
                              ///< the random engine.
  random_engine_next_fn
      next; ///< Function to generate the next random number in the engine.
  random_engine_data_dtor_fn dtor; ///< Function to release the memory allocated
                                   ///< for data by the random engine.
};

typedef const struct RandomEngineSpec * random_engine_spec_t;

/**
 * @brief Construct a random engine using a specific specification. Primarily designed to facilitate the creation of custom random engines.
 *
 * @param spec A pointer to the random engine specification.
 * @param data A pointer to the data to be used by the random engine.
 *
 * @warning Spec pointer must point to a static instance.
 *
 * @return A pointer to the random engine instance.
 */
random_engine_t * random_engine_ctor(random_engine_spec_t spec, void *data);

/**
 * @brief Get the next random number from the random engine.
 *
 * @param instance A pointer to the random engine instance.
 * @return The next random number in the range [0, UINT64_MAX].
 */
uint64_t random_engine_next(random_engine_t *instance);

/**
 * @brief Free memory used by the random engine.
 *
 *@note
 * This function will auto-release data by calling the data destructor
 * function in the random engine specification.
 *
 * @param engine A pointer to the random engine instance.
 */
void random_engine_dtor(random_engine_t *engine);

/**
 * @brief Get specification of the random engine.
 *
 * @note This function is useful when you implement a custom random engine.
 *
 * @param engine A pointer to the random engine instance.
 * @return A pointer to the random engine specification.
 */
random_engine_spec_t random_engine_get_spec(random_engine_t *engine);

/**
 * @brief Get data of the random engine.
 *
 * @note This function is useful when you implement a custom random engine.
 *
 * @param engine A pointer to the random engine instance.
 * @return A pointer to the random engine data.
 */
void *random_engine_data(random_engine_t *engine);

extern const struct RandomEngineSpec RandomDeviceEngine;

typedef random_engine_t * (*xoshiro256ss_ctor_full_fn)(const uint64_t seed[4]);
typedef random_engine_t * (*xoshiro256ss_ctor_seed_fn)(uint64_t seed);
typedef random_engine_t * (*xoshiro256ss_ctor_rd_fn)(random_device_t *rd);

/**
 * @brief Specification for the Xoshiro256** random engine.
 *
 * @note
 * The first 4 fields is inherited from the [RandomEngineSpec](RandomEngineSpec.md) structure.
 * So this structure can be cast and used as a [RandomEngineSpec](RandomEngineSpec.md).
 *
 */
struct Xoshiro256ssSpec {
  const char *name; ///< The name of the random engine. In this case, `Xoshiro256**`.
  random_engine_ctor_fn ctor; ///< Constructor function to create an instance of Xoshiro256ss. [xoshiro256ss_ctor](../xoshiro256ss/#xoshiro256ss_ctor)
  random_engine_next_fn next; ///< Function to generate the next random number in the engine. [xoshiro256ss_next](../xoshiro256ss/#xoshiro256ss_next)
  random_engine_data_dtor_fn dtor; ///< Function to release the memory allocated for data by Xoshiro256ss. [xoshiro256ss_dtor](../xoshiro256ss/#xoshiro256ss_dtor)
  xoshiro256ss_ctor_full_fn ctor_full; ///< Constructor function with a full 256-bit seed. [xoshiro256ss_ctor_full](../xoshiro256ss/#xoshiro256ss_ctor_full)
  xoshiro256ss_ctor_seed_fn ctor_seed; ///< Constructor function with a single 64-bit seed. [xoshiro256ss_ctor_seed](../xoshiro256ss/#xoshiro256ss_ctor_seed)
  xoshiro256ss_ctor_rd_fn ctor_rd; ///< Constructor function with a random device. [xoshiro256ss_ctor_rd](../xoshiro256ss/#xoshiro256ss_ctor_rd)
};

extern const struct Xoshiro256ssSpec Xoshiro256ssEngine;

/* Distributions */

/**
 * @brief Generate a random integer uniformly distributed in the range `[min,
 * max]`.
 *
 * @param engine A pointer to the random engine.
 * @param min The minimum value (inclusive).
 * @param max The maximum value (inclusive).
 * @return A random integer in the specified range.
 *
 * @ingroup distributions
 */
int uniform_int_distribution(random_engine_t *engine, int min, int max);

/**
 * @brief Generate a random floating-point number uniformly distributed in the range `[min, max)`.
 *
 * @param engine A pointer to the random engine.
 * @param min The minimum value (inclusive).
 * @param max The maximum value (exclusive).
 * @return A random floating-point number in the specified range.
 *
 * @ingroup distributions
 */
double uniform_real_distribution(random_engine_t *engine, double min,
                                 double max);

/**
 * @brief Generate a random boolean value based on the given probability.
 *
 * @param engine A pointer to the random engine.
 * @param probability The probability of returning `true` (between 0.0 and 1.0).
 * @return A random boolean value (`true` with the specified probability).
 *
 * @ingroup distributions
 */
bool bernoulli_distribution(random_engine_t *engine, double probability);

/**
 * @brief Generate a random value from a binomial distribution.
 *
 * @param engine A pointer to the random engine.
 * @param n The number of trials (must be >= 0).
 * @param p The probability of success in a single trial (range: [0.0, 1.0]).
 * @return A random value representing the number of successes in the range [0,
 * n].
 *
 * @ingroup distributions
 */
uint64_t binomial_distribution(random_engine_t *engine, uint64_t n, double p);

/**
 * @brief Generate a random value from a Poisson distribution.
 *
 * @param engine A pointer to the random engine.
 * @param lambda The mean of the Poisson distribution (must be > 0).
 * @return A random value representing the number of events in the range [0, ∞).
 *
 * @ingroup distributions
 */
uint64_t poisson_distribution(random_engine_t *engine, double lambda);

/**
 * @brief Generate a random value from a normal (Gaussian) distribution.
 *
 * @param engine A pointer to the random engine.
 * @param mu The mean of the distribution.
 * @param sigma The standard deviation of the distribution.
 * @return A random value sampled from the normal distribution, which
 * theoretically ranges from -∞ to +∞.
 *
 * @ingroup distributions
 */
double normal_distribution(random_engine_t *engine, double mu, double sigma);

/**
 * @brief Generate a random index based on a discrete probability distribution.
 *
 * @param engine A pointer to the random engine.
 * @param weights An array of probabilities for each index.
 * @param size The number of elements in the weights array.
 * @return A random index in the range [0, size-1], sampled according to the
 * given probabilities.
 *
 * @ingroup distributions
 */
size_t discrete_distribution(random_engine_t *engine, const double *weights,
                             size_t size);

#endif
