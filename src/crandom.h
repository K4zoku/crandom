#pragma once
#include <stdio.h>
#ifndef H_RANDOM_INCLUDED
#define H_RANDOM_INCLUDED

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Random Device type.
 *    The internal structure is dependent on the platform. The user should not
 *    be concerned with the internal structure of the random device.
 */
typedef struct RandomDevice random_device_t;

/**
 * @brief Construct a random device from a token.
 *
 * @param token A token to construct the random device from. Possible tokens
 * are:
 * - "/dev/urandom" - Use /dev/urandom as the random device.
 * - "/dev/random" - Use /dev/random as the random device.
 * Note that on Windows, the token is ignored and the default random device is
 * used.
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
 *    This function should release any resources allocated for the random
 * device.
 *
 * @param instance A pointer to the random device instance.
 */
void random_device_dtor(random_device_t *instance);

/* Random Engine */

/**
 * @brief Random engine type.
 *    The internal structure of the random engine is hidden from the user.
 *    However, the user can access the random engine's specification and data
 *    through the `random_engine_get_spec` and `random_engine_data` functions.
 */
typedef struct RandomEngine random_engine_t;

/**
 * @brief Construct a random engine.
 * @return A pointer to the random engine instance.
 */
typedef random_engine_t *(*random_engine_ctor_fn)(void);

/**
 * @brief Function type to get the next random number from the random engine.
 *
 * @param instance A pointer to the random engine instance.
 * @return The next random number in the range [0, UINT64_MAX].
 */
typedef uint64_t (*random_engine_next_fn)(random_engine_t *instance);

/**
 * @brief Get the next random number from the random engine.
 *
 * @param instance A pointer to the random engine instance.
 * @return The next random number in the range [0, UINT64_MAX].
 */
uint64_t random_engine_next(random_engine_t *instance);

/**
 * @brief Function Type to release the memory allocated for data by the random
 * engine, but NOT the random engine itself.
 *
 * @param instance A pointer to the random engine instance.
 */
typedef void (*random_engine_data_dtor_fn)(random_engine_t *instance);

/**
 * @brief Random engine specification structure.
 *    Defines the behavior and functions used to interact with a custom random
 * engine.
 */
struct RandomEngineSpec {
  /**
   * @brief The name of the random engine.
   */
  const char *name;

  /**
   * @brief Constructor function to create an instance of the random engine.
   */
  random_engine_ctor_fn ctor;

  /**
   * @brief Function to generate the next random number in the engine.
   */
  random_engine_next_fn next;

  /**
   * @brief Function to release the memory allocated for data by the random
   * engine.
   */
  random_engine_data_dtor_fn dtor;
};

typedef struct RandomEngineSpec random_engine_spec_t;

/**
 * @brief Construct a random engine using a specific specification.
 *   Primarily designed to facilitate the creation of custom random engines.
 *
 * @param spec A pointer to the random engine specification.
 *   Must point to a static instance of a random engine specification.
 * @param data A pointer to the data to be used by the random engine.
 * @return A pointer to the random engine instance.
 */
random_engine_t *random_engine_ctor(const random_engine_spec_t *spec,
                                    void *data);

/**
 * @brief Free memory used by the random engine.
 *   This function will auto-release data by calling the data destructor
 *   function in the random engine specification.
 *
 * @param engine A pointer to the random engine instance.
 */
void random_engine_dtor(random_engine_t *engine);

/**
 * @brief Get specification of the random engine.
 *    This function is useful when you implement a custom random engine.
 *
 * @param engine A pointer to the random engine instance.
 * @return A pointer to the random engine specification.
 */
const random_engine_spec_t *random_engine_get_spec(random_engine_t *engine);

/**
 * @brief Get data of the random engine.
 *    This function is useful when you implement a custom random engine.
 *
 * @param engine A pointer to the random engine instance.
 * @return A pointer to the random engine data.
 */
void *random_engine_data(random_engine_t *engine);

/**
 * @brief Specification for the random device engine.
 */
extern const random_engine_spec_t RandomDeviceEngine;

/**
 * @brief Specification for the Xoshiro256** random engine.
 *    The first 4 fields is inherited from the RandomEngineSpec structure.
 *    So this structure can be cast and used as a RandomEngineSpec.
 * @see RandomEngineSpec
 */
struct Xoshiro256ssSpec {
  const char *name;
  random_engine_ctor_fn ctor;
  random_engine_next_fn next;
  random_engine_data_dtor_fn dtor;

  /**
   * @brief Construct a random engine with 256 bits of seed data.
   *
   * @param seed The seed to initialize the random engine with.
   * @return A pointer to the random engine instance.
   */
  random_engine_t *(*ctor_full)(const uint64_t seed[4]);

  /**
   * @brief Construct a random engine with a single 64-bit seed.
   *    The seed will be duplicated to fill the 256 bits of seed data.
   *
   * @param seed The seed to initialize the random engine with.
   * @return A pointer to the random engine instance.
   */
  random_engine_t *(*ctor_seed)(uint64_t seed);

  /**
   * @brief Construct a random engine with a random device.
   *
   * @param rd A pointer to the random device instance.
   * @return A pointer to the random engine instance.
   */
  random_engine_t *(*ctor_rd)(random_device_t *rd);
};

typedef struct Xoshiro256ssSpec xoshiro256ss_spec_t;

/**
 * @brief The specification for the Xoshiro256** random engine.
 */
extern const xoshiro256ss_spec_t Xoshiro256ssEngine;

/* Distributions */

/**
 * @brief Generate a random integer uniformly distributed in the range [min,
 * max].
 *
 * @param engine A pointer to the random engine.
 * @param min The minimum value (inclusive).
 * @param max The maximum value (inclusive).
 * @return A random integer in the specified range.
 */
int uniform_int_distribution(random_engine_t *engine, int min, int max);

/**
 * @brief Generate a random floating-point number uniformly distributed in the
 * range [min, max).
 *
 * @param engine A pointer to the random engine.
 * @param min The minimum value (inclusive).
 * @param max The maximum value (exclusive).
 * @return A random floating-point number in the specified range.
 */
double uniform_real_distribution(random_engine_t *engine, double min,
                                 double max);

/**
 * @brief Generate a random boolean value based on the given probability.
 *
 * @param engine A pointer to the random engine.
 * @param probability The probability of returning `true` (between 0.0 and 1.0).
 * @return A random boolean value (`true` with the specified probability).
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
 */
uint64_t binomial_distribution(random_engine_t *engine, uint64_t n, double p);

/**
 * @brief Generate a random value from a Poisson distribution.
 *
 * @param engine A pointer to the random engine.
 * @param lambda The mean of the Poisson distribution (must be > 0).
 * @return A random value representing the number of events in the range [0, ∞).
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
 */
size_t discrete_distribution(random_engine_t *engine, const double *weights,
                             size_t size);

#endif
