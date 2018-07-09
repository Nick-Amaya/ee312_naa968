
#include <stdlib.h>
#include <app/i2a.h>

const time_t*
calculate_i2a_time(const time_t* irish) 
{
  time_t* austin = malloc(sizeof(time_t));

  austin->day = "same";
  austin->hour = irish->hour - 6;
  austin->min  = irish->min;

  if (austin->hour < 0) {
    austin->day = "previous";
    austin->hour += 24;
  }

  return (const time_t*) austin;
}