---
title: xoshiro256ss_spec_t
description: Construct a random engine with 256 bits of seed data.Construct a random engine with a single 64-bit seed. *    The seed will be duplicated to fill the 256 bits of seed data.Construct a random engine with a random device.
generator: doxide
---


# xoshiro256ss_spec_t

**typedef struct Xoshiro256ssSpec xoshiro256ss_spec_t**


Construct a random engine with 256 bits of seed data.


:material-location-enter: `seed`
:    The seed to initialize the random engine with.
    
:material-keyboard-return: **Return**
:    A pointer to the random engine instance.
      

    Construct a random engine with a single 64-bit seed.
   *    The seed will be duplicated to fill the 256 bits of seed data.


:material-location-enter: `seed`
:    The seed to initialize the random engine with.
    
:material-keyboard-return: **Return**
:    A pointer to the random engine instance.
      

    Construct a random engine with a random device.


:material-location-enter: `rd`
:    A pointer to the random device instance.
    
:material-keyboard-return: **Return**
:    A pointer to the random engine instance.
      


