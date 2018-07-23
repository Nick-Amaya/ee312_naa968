
#include <stdio.h>
#include <lib/minunit.h>
#include <test/a2i.h>
#include <test/i2a.h>

int tests_run = 0;

static const char* 
test_all() 
{
    mu_run_test(a2i_time_1030);
    mu_run_test(a2i_time_2250);
    mu_run_test(a2i_time_1800);
    mu_run_test(i2a_time_1220);
    mu_run_test(i2a_time_345);
    mu_run_test(i2a_time_500);
    mu_run_test(a2i_currency_418);
    mu_run_test(a2i_currency_0);
    mu_run_test(a2i_currency_2099);
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