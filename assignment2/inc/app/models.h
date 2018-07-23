
#ifndef __MODELS__
#define __MODELS__

typedef struct {
  char* day;
  int hour;
  int min;
} time_t;

typedef struct {
  int dollars;
  int cents;
} usd_t;

typedef struct {
  double value;
} euro_t;

#endif
