
#include <stdlib.h>

#include <app/a2i.h>

const time_t*
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

const euro_t*
calculate_a2i_currency(const usd_t* usd)
{
  euro_t* euro = malloc(sizeof(euro_t));

  euro->value = usd->dollars + (usd->cents / 100.0);
  euro->value *= 0.89;

  return euro;
}