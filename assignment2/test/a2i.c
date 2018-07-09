
#include <lib/minunit.h>

#include <app/a2i.h>
#include <test/a2i.h>
#include <test/models.h>

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