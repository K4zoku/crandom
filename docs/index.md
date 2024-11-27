---
title: CRandom
description: A random number generation implementation in C similar to the one found in standard C++
generator: doxide
---


# CRandom

A random number generation implementation in C similar to the one found in standard C++

:material-format-section: [Distribution functions](distributions/index.md)
:   Distribution functions

:material-format-section: [Xoshiro256**](xoshiro256ss/index.md)
:   Xoshiro256** random number generator

## Types

| Name | Description |
| ---- | ----------- |
| [random_device_t](random_device_t.md) | Random Device type. |
| [random_engine_t](random_engine_t.md) | Random engine type. |
| [RandomEngineSpec](RandomEngineSpec.md) | Random engine specification structure. |

## Functions

| Name | Description |
| ---- | ----------- |
| [random_device_ctor_token](#random_device_ctor_token) | Construct a random device from a token. |
| [random_device_ctor](#random_device_ctor) | Construct a random device. |
| [random_device_read](#random_device_read) | Read random data from the random device. |
| [random_device_read_s](#random_device_read_s) | Read random data from the random device in a safe manner. |
| [random_device_dtor](#random_device_dtor) | Free memory used by the random device. |
| [random_engine_ctor](#random_engine_ctor) | Construct a random engine using a specific specification. Primarily designed to facilitate the creation of custom random engines. |
| [random_engine_next](#random_engine_next) | Get the next random number from the random engine. |
| [random_engine_dtor](#random_engine_dtor) | Free memory used by the random engine. |
| [random_engine_get_spec](#random_engine_get_spec) | Get specification of the random engine. |
| [random_engine_data](#random_engine_data) | Get data of the random engine. |

## Function Details

### random_device_ctor_token<a name="random_device_ctor_token"></a>
!!! function "random_device_t &#42;random_device_ctor_token(const char &#42;token)"

    
    Construct a random device from a token.
    
    
    :material-location-enter: `token`
    :    A token to construct the random device from.
    
    
    !!! note
         Possible tokens on Unix-like systems: `/dev/urandom` and `/dev/random`.
        default is `/dev/urandom`.
    
    
    !!! note
         On Windows, the token is ignored and the default random device is used.
    
    
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
    
    
    !!! note
        
        This function should release any resources allocated for the random
        device.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random device instance.
        
    

### random_engine_ctor<a name="random_engine_ctor"></a>
!!! function "random_engine_t &#42; random_engine_ctor(random_engine_spec_t spec, void &#42;data)"

    
    Construct a random engine using a specific specification. Primarily designed to facilitate the creation of custom random engines.
    
    
    :material-location-enter: `spec`
    :    A pointer to the random engine specification.
        
    :material-location-enter: `data`
    :    A pointer to the data to be used by the random engine.
    
    
    !!! warning
         Spec pointer must point to a static instance.
    
    
    :material-keyboard-return: **Return**
    :    A pointer to the random engine instance.
    
    

### random_engine_next<a name="random_engine_next"></a>
!!! function "uint64_t random_engine_next(random_engine_t &#42;instance)"

    
    Get the next random number from the random engine.
    
    
    :material-location-enter: `instance`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    The next random number in the range [0, UINT64_MAX].
        
    

### random_engine_dtor<a name="random_engine_dtor"></a>
!!! function "void random_engine_dtor(random_engine_t &#42;engine)"

    
    Free memory used by the random engine.
    
    
    !!! note
        
        This function will auto-release data by calling the data destructor
        function in the random engine specification.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    

### random_engine_get_spec<a name="random_engine_get_spec"></a>
!!! function "random_engine_spec_t random_engine_get_spec(random_engine_t &#42;engine)"

    
    Get specification of the random engine.
    
    
    !!! note
         This function is useful when you implement a custom random engine.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random engine specification.
        
    

### random_engine_data<a name="random_engine_data"></a>
!!! function "void &#42;random_engine_data(random_engine_t &#42;engine)"

    
    Get data of the random engine.
    
    
    !!! note
         This function is useful when you implement a custom random engine.
    
    
    :material-location-enter: `engine`
    :    A pointer to the random engine instance.
        
    :material-keyboard-return: **Return**
    :    A pointer to the random engine data.
        
    

