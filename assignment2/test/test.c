
#include <stdio.h>
#include "../lib/minunit.h"
#include "a2i.h"
#include "i2a.h"

int tests_run = 0;

static const char* 
test_all() 
{
    mu_run_test(a2i_time_1030);
    mu_run_test(a2i_time_2250);
    mu_run_test(a2i_time_1800);
    return 0;
}

int 
main() 
{
  const char* result = test_all();
  if (result != 0) {
    printf("ERROR: %s\n", result);
    printf("Failed on test: %d\n", tests_run);
    printf("%d TESTS PASSED.\n", tests_run-1);
  } else {
    printf("ALL TESTS PASSED (%d)\n", tests_run);
  }
  return result != 0;
}