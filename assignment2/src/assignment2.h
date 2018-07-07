
#ifndef __ASSIGNMENT_2__
#define __ASSIGNMENT_2__

typedef struct {
  char* day;
  int hour;
  int min;
} time_t;

time_t*
calculate_a2i_time(const time_t*);

#endif