
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lib/minunit.h>

#include <assignment2.h>
#include <test/a2i.h>

static const char* assert_time_equals(const char* prefix, const time_t* expected, const time_t* actual);

const char* 
a2i_time_1030() 
{
    const time_t austin = {0, 10, 30};
    const time_t* irish = calculate_a2i_time(&austin);
    const time_t expected = {"same", 16, 30};
    return assert_time_equals("A2I: ", &expected, irish); 
}

const char* 
a2i_time_2250() 
{
    const time_t austin = {0, 22, 50};
    const time_t* irish = calculate_a2i_time(&austin);
    const time_t expected = {"next", 4, 50};
    return assert_time_equals("A2I: ", &expected, irish);
}

const char* 
a2i_time_1800() 
{
    const time_t austin = {0, 18, 0};
    const time_t* irish = calculate_a2i_time(&austin);
    const time_t expected = {"next", 0, 0};
    return assert_time_equals("A2I: ", &expected, irish);
}

static const char* 
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

char* austinToIrishCurrencyTest() {
    return 0;
}

char* austinToIrishTemperatureTest() {
    return 0;
}

char* austinToIrishWeightTest() {
    return 0;
}

char* austinToIrishDistanceTest() {
    return 0;
}

char* exitTest() {
    return 0;
}