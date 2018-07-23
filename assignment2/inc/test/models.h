
#ifndef __MODEL_ASSERTIONS__
#define __MODEL_ASSERTIONS__

#include <app/models.h>

const char* assert_time_equals(const char* prefix, const time_t* expected, const time_t* actual);
const char* assert_euro_equals(const char* prefix, const euro_t* expected, const euro_t* actual);

#endif