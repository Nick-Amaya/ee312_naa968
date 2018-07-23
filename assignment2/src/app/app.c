
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <app/app.h>
#include <app/a2i.h>
#include <app/i2a.h>

//****************************  I/O Variable Place Holders  **************************
typedef struct {
  const void* (*prompt)();
  const void* (*calculate)(const void*);
  void (*print)(const void*, const void*);
  void (*clean_up)(const void*, const void*);
} component_t;

int US_dollar[2];
double euro;

int farenheit;
double celsius;

int US_pounds[2];
double kilograms;

double mile;
double kilometer;

/**
 * Terminal component 1: Austin Time -> Ireland Time
 */ 
static const void*
prompt_austin_time()
{
  time_t* austin = malloc(sizeof(time_t));
  printf("Enter Austin time to be converted, expressed in hours and minutes <hours> <minutes>: ");
  scanf("%d %d", &(austin->hour), &(austin->min));
  return (const time_t*) austin;
}

static const void* 
calculate_a2i_time_app_wrapper(const void* generic_austin) 
{
  const time_t* austin = (const time_t*) generic_austin;
  return (const void*) calculate_a2i_time(austin);
}

static void
print_a2i_time(const void* generic_austin, const void* generic_irish)
{
  time_t* austin = (time_t*) generic_austin;
  time_t* irish  = (time_t*) generic_irish;
  printf("The time in Ireland equivalent to %d %02d in Austin is %d %02d of the %s day\n", 
      austin->hour, austin->min, irish->hour, irish->min, irish->day);
}

static void 
a2i_time_clean_up(const void* austin, const void* irish)
{
  free((void*) austin);
  free((void*) irish);
}

/**
 * Terminal component 2: Ireland Time -> Austin Time
 */ 
static const void*
prompt_irish_time()
{
  time_t* irish = malloc(sizeof(time_t));
  printf("Enter Irish time to be converted, expressed in hours and minutes: ");
  scanf("%d %d", &(irish->hour), &(irish->min));
  return (const time_t*) irish;
}

static const void* 
calculate_i2a_time_app_wrapper(const void* generic_irish) 
{
  const time_t* irish = (const time_t*) generic_irish;
  return (const void*) calculate_i2a_time(irish);
}

static void
print_i2a_time(const void* generic_irish, const void* generic_austin)
{
  time_t* irish  = (time_t*) generic_irish;
  time_t* austin = (time_t*) generic_austin;
  printf("The time in Austin equivalent to %d %02d in Ireland is %d %02d of the %s day\n", 
      irish->hour, irish->min, austin->hour, austin->min, austin->day);
}

static void 
i2a_time_clean_up(const void* irish, const void* austin)
{
  free((void*) irish);
  free((void*) austin);
}

/**
 * Terminal Component 3: USD -> Euro
 */
// void 
// a2i_currency(void) 
// {
//   printf("Enter USD value <dollar> <cents>: ");
//   scanf("%d %d", &US_dollar[0], &US_dollar[1]);

//   euro = US_dollar[0] + (US_dollar[1] / 100.0);
//   euro *= 0.89;

//   printf("\nEUR value is: %.2f Euros\n", euro);
// }
static const void*
prompt_usd()
{
  usd_t* usd = malloc(sizeof(usd_t));
  printf("Enter USD value <dollar> <cents>: ");
  scanf("%d %d", &(usd->dollars), &(usd->cents));
  return (const usd_t*) usd;
}

static const void* 
calculate_a2i_currency_app_wrapper(const void* generic_usd) 
{
  return (const void*) calculate_a2i_currency((const usd_t*) generic_usd);
}

// static void
// print_i2a_time(const void* generic_irish, const void* generic_austin)
// {
//   time_t* irish  = (time_t*) generic_irish;
//   time_t* austin = (time_t*) generic_austin;
//   printf("The time in Austin equivalent to %d %02d in Ireland is %d %02d of the %s day\n", 
//       irish->hour, irish->min, austin->hour, austin->min, austin->day);
// }

// static void 
// i2a_time_clean_up(const void* irish, const void* austin)
// {
//   free((void*) irish);
//   free((void*) austin);
// }

/**
 * Terminal Component 4: Euro -> USD
 */

void 
a2i_temperature(void) 
{
  printf("Enter temperature in Farenheit: ");
  scanf("%d", &farenheit);

  celsius = (5.0/9) * (farenheit - 32);

  printf("\nTemperature in Celsius is: %lf", celsius);
}

void 
a2i_weight(void) 
{
  printf("Enter weight in pounds and ounces <pounds> <ounces>: ");
  scanf("%d %d", &US_pounds[0], &US_pounds[1]);

  kilograms = ((double)US_pounds[0] + (US_pounds[1] / 16.0)) * 0.45359327;

  printf("Weight in kg is: %1.3f kg", kilograms);
}

void 
a2i_distance(void) 
{
  printf("Enter distances in miles: ");
  scanf("%lf", &mile);

  kilometer = 1.6093439 * mile;

  printf("Distance in km is: %lf k", kilometer);
}

//----------IrishtoAustin------------

void 
i2a_currency(void) 
{
  printf("Enter EUR value <euros>: ");
  scanf("%lf", &euro);

  euro *= 1.13;
  US_dollar[0] = (int)(euro);
  US_dollar[1] = (euro - US_dollar[0]) * 100;

  printf("\nUSD value is: $%d.%d\n", US_dollar[0], US_dollar[1]);
}

void 
i2a_temperature(void) 
{
  float round_test;

  printf("Enter temperature in Celsius: ");
  scanf("%lf", &celsius);

  farenheit = round_test = ((9.0/5) * celsius) + 32;

  if(round_test - farenheit >= 0.5)
    farenheit++;

  printf("Temperature in Farenheit: %d\n", farenheit);
}

void 
i2a_weight(void) 
{
  float round_test;
  int ounces;

  printf("Enter weight in kg <kilograms>: ");
  scanf("%lf", &kilograms);

  ounces = round_test = (kilograms * 35.274);
  if(round_test - ounces >= 0.5)
    ounces++;

  US_pounds[0] = round_test = ounces / 16;
  US_pounds[1] = round_test = ounces % 16;

  printf("Weight in pounds and ounces is: %d lb, %d oz\n", US_pounds[0], US_pounds[1]);
}

void 
i2a_distance(void) 
{
  printf("Enter distances in km: ");
  scanf("%lf", &kilometer);

  mile = 0.6213712 * kilometer;

  printf("Distance in miles is: %lf mi", mile);
}

//*********************************  Main Program  ******************************************

component_t*
build_components()
{
  component_t* components = malloc(10*sizeof(component_t));

  component_t components_initializer[] = {
    {prompt_austin_time, calculate_a2i_time_app_wrapper, print_a2i_time, a2i_time_clean_up},
    {prompt_irish_time, calculate_i2a_time_app_wrapper, print_i2a_time, i2a_time_clean_up},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };

  return memcpy(components, components_initializer, sizeof(components_initializer));
}

component_t*
rewire(component_t* components, int selection) 
{
  return &(components[selection-1]);
}

int 
prompt_user() 
{
  int selection;
  printf("\nEnter a number from the menu (1-11) to select a specific conversion to perform or to quit: ");
  scanf("%d", &selection);
  return selection;
}

void
run(component_t* component)
{
  const void* user_input = component->prompt();
  const void* calculation = component->calculate(user_input);
  component->print(user_input, calculation);
  component->clean_up(user_input, calculation);
}

/*
  1. Convert a given Austin time to Irish time
  2. Convert a given Irish time to Austin time
  3. Convert a given USD value to EUR
  4. Convert a given EUR value to USD value
  5. Convert a given Fahrenheit temperature to Celsius
  6. Convert a given Celsius temperature to Fahrenheit
  7. Convert a given weight in kg to pounds, ounces
  8. Convert a given weight in pounds, ounces to kg
  9. Convert a given distance in km to miles
  10. Convert a given distance in miles to km
  11. Stop doing conversions and quit the program
*/
int 
run_app() 
{
  component_t* components = build_components();
  unsigned int selection;
  component_t* component;

  do {
    selection = prompt_user();
    component = rewire(components, selection);
    run(component);
  } while (selection != 11);

  free(components);

  return 0;
}
