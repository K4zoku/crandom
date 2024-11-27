#include "crandom.h"
#include <stdlib.h>

struct RandomEngine {
    const random_engine_spec_t * spec;
    void * data;
};

random_engine_t * random_engine_ctor(const random_engine_spec_t * spec, void * data) {
    random_engine_t * engine = (random_engine_t *) malloc(sizeof(random_engine_t));
    engine->spec = spec;
    engine->data = data;
    return engine;
}

void random_engine_dtor(random_engine_t * engine) {
    random_engine_data_dtor_fn dtor = engine->spec->dtor;
    dtor(engine);
    free(engine);
}

const random_engine_spec_t * random_engine_get_spec(random_engine_t * engine) {
    return engine->spec;
}

void * random_engine_data(random_engine_t * engine) {
    return engine->data;
}

uint64_t random_engine_next(random_engine_t * engine) {
    random_engine_next_fn next = engine->spec->next;
    return next(engine);
}
