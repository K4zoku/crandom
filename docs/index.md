---
title: CRandom
description: A random number generation implementation in C similar to the one found in standard C++
generator: doxide
---


# CRandom

A random number generation implementation in C similar to the one found in standard C++

## Types

| Name | Description |
| ---- | ----------- |
| [random_device_t](random_device_t.md) | Random Device type. *    The internal structure is dependent on the platform. The user should not *    be concerned with the internal structure of the random device.  |
| [random_engine_t](random_engine_t.md) | Random engine type. *    The internal structure of the random engine is hidden from the user. *    However, the user can access the random engine's specification and data *    through the `random_engine_get_spec` and `random_engine_data` functions.  |
| [RandomEngineSpec](RandomEngineSpec.md) | Function Type to release the memory allocated for data by the random * engine, but NOT the random engine itself.Random engine specification structure. *    Defines the behavior and functions used to interact with a custom random * engine.  |
| [Xoshiro256ssSpec](Xoshiro256ssSpec.md) | Specification for the Xoshiro256** random engine. *    The first 4 fields is inherited from the RandomEngineSpec structure. *    So this structure can be cast and used as a RandomEngineSpec. * @see RandomEngineSpec  |
| [xoshiro256ss_spec_t](xoshiro256ss_spec_t.md) | Construct a random engine with 256 bits of seed data.Construct a random engine with a single 64-bit seed. *    The seed will be duplicated to fill the 256 bits of seed data.Construct a random engine with a random device. |

## Variables

| Name | Description |
| ---- | ----------- |
| [RandomDeviceEngine](#RandomDeviceEngine) | Specification for the random device engine.  |
| [Xoshiro256ssEngine](#Xoshiro256ssEngine) | The specification for the Xoshiro256** random engine.  |

## Functions

| Name | Description |
| ---- | ----------- |
| [random_device_ctor_token](#random_device_ctor_token) | Construct a random device from a token. |
| [random_device_ctor](#random_device_ctor) | Construct a random device. |
| [random_device_read](#random_device_read) | Read random data from the random device. |
| [random_device_read_s](#random_device_read_s) | Read random data from the random device in a safe manner. |
| [random_device_dtor](#random_device_dtor) | Free memory used by the random device. *    This function should release any resources allocated for the random * device. |
| [random_engine_next](#random_engine_next) | Construct a random engine. * @return A pointer to the random engine instance. Function type to get the next random number from the random engine.Get the next random number from the random engine. |
| [random_engine_ctor](#random_engine_ctor) | Construct a random engine using a specific specification. *   Primarily designed to facilitate the creation of custom random engines. |
| [random_engine_dtor](#random_engine_dtor) | Free memory used by the random engine. *   This function will auto-release data by calling the data destructor *   function in the random engine specification. |
| [random_engine_get_spec](#random_engine_get_spec) | Get specification of the random engine. *    This function is useful when you implement a custom random engine. |
| [random_engine_data](#random_engine_data) | Get data of the random engine. *    This function is useful when you implement a custom random engine. |
| [uniform_int_distribution](#uniform_int_distribution) | Generate a random integer uniformly distributed in the range [min, * max]. |
| [uniform_real_distribution](#uniform_real_distribution) | Generate a random floating-point number uniformly distributed in the * range [min, max). |
| [bernoulli_distribution](#bernoulli_distribution) | Generate a random boolean value based on the given probability. |
| [binomial_distribution](#binomial_distribution) | Generate a random value from a binomial distribution. |
| [poisson_distribution](#poisson_distribution) | Generate a random value from a Poisson distribution. |
| [normal_distribution](#normal_distribution) | Generate a random value from a normal (Gaussian) distribution. |
| [discrete_distribution](#discrete_distribution) | Generate a random index based on a discrete probability distribution. |

## Variable Details

### RandomDeviceEngine<a name="RandomDeviceEngine"></a>

!!! variable "extern const random_engine_spec_t RandomDeviceEngine"

    
    Specification for the random device engine.
     
    
    
    

### Xoshiro256ssEngine<a name="Xoshiro256ssEngine"></a>

!!! variable "extern const xoshiro256ss_spec_t Xoshiro256ssEngine"

    
    The specification for the Xoshiro256** random engine.
     
    
    
    

## Function Details

### random_device_ctor_token<a name="random_device_ctor_token"></a>
!!! function "random_device_t &#42;random_device_ctor_token(const char &#42;token)"

    
    Construct a random device from a token.
    
    
    :material-location-enter: `token`
    :    A token to construct the random device from. Possible tokens
        are:
        - "/dev/urandom" - Use /dev/urandom as the random device.
        - "/dev/random" - Use /dev/random as the random device.
        Note that on Windows, the token is ignored and the default random device is
        used.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random device instance.
        
    

### random_device_ctor<a name="random_device_ctor"></a>
!!! function "random_device_t &#42;random_device_ctor(void)"

    
    Construct a random device.
    
    
    :material-keyboard-return: **Return**
    :    A pointer to the random device instance.
    
    

### random_device_read<a name="random_device_read"></a>
!!! function "size_t random_device_read(random_device_t &#42;instance, void &#42;buffer, size_t count)"

    
    Read random data from the random device.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random device instance.
        
    :material-location-enter: `buffer`
    :    A pointer to the buffer to write the random data to.
        
    :material-location-enter: `count`
    :    The number of bytes to read. Must be less than or equal to the
        size of the buffer.
        
    :material-keyboard-return: **Return**
    :    The number of bytes read.
        
    

### random_device_read_s<a name="random_device_read_s"></a>
!!! function "size_t random_device_read_s(random_device_t &#42;instance, void &#42;buffer, size_t buffer_size, size_t count)"

    
    Read random data from the random device in a safe manner.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random device instance.
        
    :material-location-enter: `buffer`
    :    A pointer to the buffer to write the random data to.
        
    :material-location-enter: `buffer_size`
    :    The size of the buffer.
        
    :material-location-enter: `count`
    :    The number of bytes to read.
        
    :material-keyboard-return: **Return**
    :    The number of bytes read.
        
    

### random_device_dtor<a name="random_device_dtor"></a>
!!! function "void random_device_dtor(random_device_t &#42;instance)"

    
    Free memory used by the random device.
     *    This function should release any resources allocated for the random
     * device.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random device instance.
        
    

### random_engine_next<a name="random_engine_next"></a>
!!! function "uint64_t random_engine_next(random_engine_t &#42;instance)"

    
    Construct a random engine.
     * @return A pointer to the random engine instance.
     
    
    
    
    Function type to get the next random number from the random engine.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    The next random number in the range [0, UINT64_MAX].
        
    
        Get the next random number from the random engine.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    The next random number in the range [0, UINT64_MAX].
        
    

### random_engine_ctor<a name="random_engine_ctor"></a>
!!! function "random_engine_t &#42;random_engine_ctor(const random_engine_spec_t &#42;spec, void &#42;data)"

    
    Construct a random engine using a specific specification.
     *   Primarily designed to facilitate the creation of custom random engines.
    
    
    :material-location-enter: `spec`
    :    A pointer to the random engine specification.
          Must point to a static instance of a random engine specification.
        
    :material-location-enter: `data`
    :    A pointer to the data to be used by the random engine.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random engine instance.
        
    

### random_engine_dtor<a name="random_engine_dtor"></a>
!!! function "void random_engine_dtor(random_engine_t &#42;engine)"

    
    Free memory used by the random engine.
     *   This function will auto-release data by calling the data destructor
     *   function in the random engine specification.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    

### random_engine_get_spec<a name="random_engine_get_spec"></a>
!!! function "const random_engine_spec_t &#42;random_engine_get_spec(random_engine_t &#42;engine)"

    
    Get specification of the random engine.
     *    This function is useful when you implement a custom random engine.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random engine specification.
        
    

### random_engine_data<a name="random_engine_data"></a>
!!! function "void &#42;random_engine_data(random_engine_t &#42;engine)"

    
    Get data of the random engine.
     *    This function is useful when you implement a custom random engine.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random engine data.
        
    

### uniform_int_distribution<a name="uniform_int_distribution"></a>
!!! function "int uniform_int_distribution(random_engine_t &#42;engine, int min, int max)"

    
    Generate a random integer uniformly distributed in the range [min,
     * max].
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `min`
    :    The minimum value (inclusive).
        
    :material-location-enter: `max`
    :    The maximum value (inclusive).
        
    :material-keyboard-return: **Return**
    :    A random integer in the specified range.
        
    

### uniform_real_distribution<a name="uniform_real_distribution"></a>
!!! function "double uniform_real_distribution(random_engine_t &#42;engine, double min, double max)"

    
    Generate a random floating-point number uniformly distributed in the
     * range [min, max).
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `min`
    :    The minimum value (inclusive).
        
    :material-location-enter: `max`
    :    The maximum value (exclusive).
        
    :material-keyboard-return: **Return**
    :    A random floating-point number in the specified range.
        
    

### bernoulli_distribution<a name="bernoulli_distribution"></a>
!!! function "bool bernoulli_distribution(random_engine_t &#42;engine, double probability)"

    
    Generate a random boolean value based on the given probability.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `probability`
    :    The probability of returning `true` (between 0.0 and 1.0).
        
    :material-keyboard-return: **Return**
    :    A random boolean value (`true` with the specified probability).
        
    

### binomial_distribution<a name="binomial_distribution"></a>
!!! function "uint64_t binomial_distribution(random_engine_t &#42;engine, uint64_t n, double p)"

    
    Generate a random value from a binomial distribution.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `n`
    :    The number of trials (must be >= 0).
        
    :material-location-enter: `p`
    :    The probability of success in a single trial (range: [0.0, 1.0]).
        
    :material-keyboard-return: **Return**
    :    A random value representing the number of successes in the range [0,
        n].
        
    

### poisson_distribution<a name="poisson_distribution"></a>
!!! function "uint64_t poisson_distribution(random_engine_t &#42;engine, double lambda)"

    
    Generate a random value from a Poisson distribution.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `lambda`
    :    The mean of the Poisson distribution (must be > 0).
        
    :material-keyboard-return: **Return**
    :    A random value representing the number of events in the range [0, ∞).
        
    

### normal_distribution<a name="normal_distribution"></a>
!!! function "double normal_distribution(random_engine_t &#42;engine, double mu, double sigma)"

    
    Generate a random value from a normal (Gaussian) distribution.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `mu`
    :    The mean of the distribution.
        
    :material-location-enter: `sigma`
    :    The standard deviation of the distribution.
        
    :material-keyboard-return: **Return**
    :    A random value sampled from the normal distribution, which
        theoretically ranges from -∞ to +∞.
        
    

### discrete_distribution<a name="discrete_distribution"></a>
!!! function "size_t discrete_distribution(random_engine_t &#42;engine, const double &#42;weights, size_t size)"

    
    Generate a random index based on a discrete probability distribution.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `weights`
    :    An array of probabilities for each index.
        
    :material-location-enter: `size`
    :    The number of elements in the weights array.
        
    :material-keyboard-return: **Return**
    :    A random index in the range [0, size-1], sampled according to the
        given probabilities.
        
    

