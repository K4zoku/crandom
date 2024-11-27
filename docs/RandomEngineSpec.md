---
title: RandomEngineSpec
description: Random engine specification structure.
generator: doxide
---


# RandomEngineSpec

**struct RandomEngineSpec**


Random engine specification structure.


!!! note
     Defines the behavior and functions used to interact with a custom
    random engine.
    


## Variables

| Name | Description |
| ---- | ----------- |
| [name](#name) | The name of the random engine. |
| [ctor](#ctor) | Constructor function to create an instance of the random engine. |
| [next](#next) | Function to generate the next random number in the engine. |
| [dtor](#dtor) | Function to release the memory allocated for data by the random engine. |

## Variable Details

### name<a name="name"></a>

!!! variable "const char &#42;name"

    The name of the random engine.
    

### ctor<a name="ctor"></a>

!!! variable "random_engine_ctor_fn ctor"

    Constructor function to create an instance of
    the random engine.
    

### next<a name="next"></a>

!!! variable "random_engine_next_fn next"

    Function to generate the next random number in the engine.
    

### dtor<a name="dtor"></a>

!!! variable "random_engine_data_dtor_fn dtor"

    Function to release the memory allocated
    for data by the random engine.
    

