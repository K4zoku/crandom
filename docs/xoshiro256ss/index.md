---
title: Xoshiro256**
description: Xoshiro256** random number generator
generator: doxide
---


# Xoshiro256**

Xoshiro256** random number generator

## Functions

| Name | Description |
| ---- | ----------- |
| [xoshiro256ss_ctor](#xoshiro256ss_ctor) | Construct a new xoshiro256** random number generator with a random seed generated from the default random device. |
| [xoshiro256ss_ctor_full](#xoshiro256ss_ctor_full) | Construct a new xoshiro256** random number generator with a full 256-bit seed. |
| [xoshiro256ss_ctor_rd](#xoshiro256ss_ctor_rd) | Construct a new xoshiro256** random number generator with a random seed generated from the given random device. |
| [xoshiro256ss_ctor_seed](#xoshiro256ss_ctor_seed) | Construct a new xoshiro256** random number generator with a 64-bit seed. |
| [xoshiro256ss_dtor](#xoshiro256ss_dtor) | Release the resources used by the xoshiro256** random number generator. |
| [xoshiro256ss_next](#xoshiro256ss_next) | Generate the next random number from the xoshiro256** random number generator. |

## Function Details

### xoshiro256ss_ctor<a name="xoshiro256ss_ctor"></a>
!!! function "random_engine_t &#42;xoshiro256ss_ctor(void)"

    
    Construct a new xoshiro256** random number generator with a random seed generated from the default random device.
    
    
    :material-keyboard-return: **Return**
    :    random_engine_t* The constructed random number generator.
    
    
    
    

### xoshiro256ss_ctor_full<a name="xoshiro256ss_ctor_full"></a>
!!! function "random_engine_t &#42;xoshiro256ss_ctor_full(const uint64_t seed[4])"

    
    Construct a new xoshiro256** random number generator with a full 256-bit seed.
    
    
    :material-location-enter: `seed`
    :    The 256-bit seed.
        
    :material-keyboard-return: **Return**
    :    random_engine_t* The constructed random number generator.
    
    
    
    

### xoshiro256ss_ctor_rd<a name="xoshiro256ss_ctor_rd"></a>
!!! function "random_engine_t &#42;xoshiro256ss_ctor_rd(random_device_t &#42;rd)"

    
    Construct a new xoshiro256** random number generator with a random seed generated from the given random device.
    
    
    :material-location-enter: `rd`
    :    The random device.
        
    :material-keyboard-return: **Return**
    :    random_engine_t* The constructed random number generator.
    
    
    
    

### xoshiro256ss_ctor_seed<a name="xoshiro256ss_ctor_seed"></a>
!!! function "random_engine_t &#42;xoshiro256ss_ctor_seed(const uint64_t seed)"

    
    Construct a new xoshiro256** random number generator with a 64-bit seed.
    
    
    !!! note
         The seed is expanded to a full 256-bit seed using the splitmix64 algorithm.
    
    
    :material-location-enter: `seed`
    :    The 64-bit seed.
        
    :material-keyboard-return: **Return**
    :    random_engine_t* The constructed random number generator.
    
    
    
    

### xoshiro256ss_dtor<a name="xoshiro256ss_dtor"></a>
!!! function "void xoshiro256ss_dtor(random_engine_t &#42;engine)"

    
    Release the resources used by the xoshiro256** random number generator.
    
    
    :material-location-enter: `engine`
    :    The random number generator.
    
    
    
    

### xoshiro256ss_next<a name="xoshiro256ss_next"></a>
!!! function "uint64_t xoshiro256ss_next(random_engine_t &#42;engine)"

    
    Generate the next random number from the xoshiro256** random number generator.
    
    
    :material-location-enter: `engine`
    :    The random number generator.
        
    :material-keyboard-return: **Return**
    :    uint64_t The next random number.
    
    
    
    

