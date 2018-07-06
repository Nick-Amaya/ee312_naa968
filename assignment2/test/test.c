
#include <stdio.h>
#include "../lib/minunit.h"
#include "a2i.h"
#include "i2a.h"

int testsRun = 0;

static char* testAll() {
    mu_run_test(austinToIrishTimeTest);
    mu_run_test(austinToIrishCurrencyTest);
    mu_run_test(austinToIrishTemperatureTest);
    mu_run_test(austinToIrishWeightTest);
    mu_run_test(austinToIrishDistanceTest);
    mu_run_test(irishToAustinTimeTest);
    mu_run_test(irishToAustinCurrencyTest);
    mu_run_test(irishToAustinTemperatureTest);
    mu_run_test(irishToAustinWeightTest);
    mu_run_test(irishToAustinDistanceTest);
    mu_run_test(exitTest);
    return 0;
}

int main() {
  char* result = testAll();
  if (result != 0) {
    printf("ERROR: %s\n", result);
  } else {
    printf("ALL TESTS PASSED\n");
  }
  return result != 0;
}