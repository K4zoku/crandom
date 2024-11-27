---
title: Distribution functions
description: Distribution functions
generator: doxide
---


# Distribution functions

Distribution functions

## Functions

| Name | Description |
| ---- | ----------- |
| [bernoulli_distribution](#bernoulli_distribution) | Generate a random boolean value based on the given probability. |
| [binomial_distribution](#binomial_distribution) | Generate a random value from a binomial distribution. |
| [discrete_distribution](#discrete_distribution) | Generate a random index based on a discrete probability distribution. |
| [normal_distribution](#normal_distribution) | Generate a random value from a normal (Gaussian) distribution. |
| [poisson_distribution](#poisson_distribution) | Generate a random value from a Poisson distribution. |
| [uniform_int_distribution](#uniform_int_distribution) | Generate a random integer uniformly distributed in the range `[min, * max]`. |
| [uniform_real_distribution](#uniform_real_distribution) | Generate a random floating-point number uniformly distributed in the range `[min, max)`. |

## Function Details

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
    
    
    
    

### poisson_distribution<a name="poisson_distribution"></a>
!!! function "uint64_t poisson_distribution(random_engine_t &#42;engine, double lambda)"

    
    Generate a random value from a Poisson distribution.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `lambda`
    :    The mean of the Poisson distribution (must be > 0).
        
    :material-keyboard-return: **Return**
    :    A random value representing the number of events in the range [0, ∞).
    
    
    
    

### uniform_int_distribution<a name="uniform_int_distribution"></a>
!!! function "int uniform_int_distribution(random_engine_t &#42;engine, int min, int max)"

    
    Generate a random integer uniformly distributed in the range `[min,
     * max]`.
    
    
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

    
    Generate a random floating-point number uniformly distributed in the range `[min, max)`.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine.
        
    :material-location-enter: `min`
    :    The minimum value (inclusive).
        
    :material-location-enter: `max`
    :    The maximum value (exclusive).
        
    :material-keyboard-return: **Return**
    :    A random floating-point number in the specified range.
    
    
    
    

