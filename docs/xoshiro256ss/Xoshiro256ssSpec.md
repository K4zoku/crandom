---
title: Xoshiro256ssSpec
description: Specification for the Xoshiro256** random engine.
generator: doxide
---


# Xoshiro256ssSpec

**struct Xoshiro256ssSpec**


Specification for the Xoshiro256** random engine.


!!! note
    
    The first 4 fields is inherited from the [RandomEngineSpec](RandomEngineSpec.md) structure.
    So this structure can be cast and used as a [RandomEngineSpec](RandomEngineSpec.md).





## Variables

| Name | Description |
| ---- | ----------- |
| [name](#name) | The name of the random engine. |
| [ctor](#ctor) | Constructor function to create an instance of Xoshiro256ss. |
| [next](#next) | Function to generate the next random number in the engine. |
| [dtor](#dtor) | Function to release the memory allocated for data by Xoshiro256ss. |
| [ctor_full](#ctor_full) | Constructor function with a full 256-bit seed. |
| [ctor_seed](#ctor_seed) | Constructor function with a single 64-bit seed. |
| [ctor_rd](#ctor_rd) | Constructor function with a random device. |

## Variable Details

### name<a name="name"></a>

!!! variable "const char &#42;name"

    The name of the random engine. In this case, `Xoshiro256**`.
    

### ctor<a name="ctor"></a>

!!! variable "random_engine_ctor_fn ctor"

    Constructor function to create an instance of Xoshiro256ss. [xoshiro256ss_ctor](xoshiro256ss_ctor)
    

### next<a name="next"></a>

!!! variable "random_engine_next_fn next"

    Function to generate the next random number in the engine. [xoshiro256ss_next](xoshiro256ss_next)
    

### dtor<a name="dtor"></a>

!!! variable "random_engine_data_dtor_fn dtor"

    Function to release the memory allocated for data by Xoshiro256ss. [xoshiro256ss_dtor](xoshiro256ss_dtor)
    

### ctor_full<a name="ctor_full"></a>

!!! variable "xoshiro256ss_ctor_full_fn ctor_full"

    Constructor function with a full 256-bit seed. [xoshiro256ss_ctor_full](xoshiro256ss_ctor_full)
    

### ctor_seed<a name="ctor_seed"></a>

!!! variable "xoshiro256ss_ctor_seed_fn ctor_seed"

    Constructor function with a single 64-bit seed. [xoshiro256ss_ctor_seed](xoshiro256ss_ctor_seed)
    

### ctor_rd<a name="ctor_rd"></a>

!!! variable "xoshiro256ss_ctor_rd_fn ctor_rd"

    Constructor function with a random device. [xoshiro256ss_ctor_rd](xoshiro256ss_ctor_rd)
    

