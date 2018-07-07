
#include <stdlib.h>

#include <app/a2i.h>

time_t*
calculate_a2i_time(const time_t* austin) 
{
  time_t* irish = malloc(sizeof(time_t));

  irish->day = "same";
  irish->hour = (austin->hour + 6) % 24;
  irish->min = austin->min;

  if (irish->hour <= 6) {
    irish->day = "next";
  }

  return irish;
}