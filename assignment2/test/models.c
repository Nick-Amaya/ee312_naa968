
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <lib/minunit.h>

#include <test/models.h>

const char* 
assert_time_equals(const char* prefix, const time_t* expected, const time_t* actual)
{
    char* msg_buffer = malloc(100);
    char* fmt_buffer = malloc(100);

    strcpy(fmt_buffer, prefix);
    sprintf(msg_buffer, strcat(fmt_buffer, "TIME: Day: expected %s but found %s\n"), expected->day, actual->day);
    mu_assert(msg_buffer, !strcmp(expected->day, actual->day));

    strcpy(msg_buffer, prefix);
    sprintf(msg_buffer, strcat(msg_buffer, "TIME: Hour: expected %d but found %d\n"), expected->hour, actual->hour);
    mu_assert_equals(msg_buffer, expected->hour, actual->hour);
    
    strcpy(msg_buffer, prefix);
    sprintf(msg_buffer, strcat(msg_buffer, "TIME: Min: expected %d but found %d\n"), expected->min, actual->min);
    mu_assert_equals(msg_buffer, expected->min, actual->min);

    free(msg_buffer);
    free(fmt_buffer);

    return 0;
}

const char* 
assert_euro_equals(const char* prefix, const euro_t* expected, const euro_t* actual)
{
    char* msg_buffer = malloc(100);
    char* fmt_buffer = malloc(100);

    strcpy(fmt_buffer, prefix);
    sprintf(msg_buffer, strcat(fmt_buffer, "CURRENCY: value: expected %lf but found %lf\n"), expected->value, actual->value);
    mu_assert(msg_buffer, ((fabs(expected->value) - fabs(actual->value)) < 0.000001));

    free(msg_buffer);
    free(fmt_buffer);

    return 0;
}