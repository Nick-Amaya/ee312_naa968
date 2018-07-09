
#include <test/i2a.h>

#include <app/i2a.h>

#include <test/models.h>

const char* 
i2a_time_1220() 
{
    const time_t irish = {0, 12, 20};
    const time_t* austin = calculate_i2a_time(&irish);
    const time_t expected = {"same", 6, 20};
    return assert_time_equals("I2A: ", &expected, austin); 
}

const char* 
i2a_time_345() 
{
    const time_t irish = {0, 3, 45};
    const time_t* austin = calculate_i2a_time(&irish);
    const time_t expected = {"previous", 21, 45};
    return assert_time_equals("I2A: ", &expected, austin);
}

const char* 
i2a_time_500() 
{
    const time_t irish = {0, 5, 0};
    const time_t* austin = calculate_i2a_time(&irish);
    const time_t expected = {"previous", 23, 0};
    return assert_time_equals("I2A: ", &expected, austin);
}

char* irishToAustinCurrencyTest() {
    return 0;
}

char* irishToAustinTemperatureTest() {
    return 0;
}

char* irishToAustinWeightTest() {
    return 0;
}

char* irishToAustinDistanceTest() {
    return 0;
}
