/*
  Amaya, Nicholas
  naa968
  16300
  EE312 Assignment 2: Manipulating Numeric Data
*/


#include <stdio.h>
#include "../lib/minunit.h"

#define hours 0
#define mins  1
#define prev  0
#define same  1
#define next  2

//****************************  I/O Variable Place Holders  **************************
int austinTime[2];
int irishTime[2];
const char * DAYS[3];

int US_dollar[2];
double euro;

int farenheit;
double celsius;

int US_pounds[2];
double kilograms;

double mile;
double kilometer;


//*****************************  Conversion Functions  **********************************
//-------------AusintoIrish-------------
void AustintoIrish_time(void) {
  int day = same;

  printf("Enter Austin time to be converted, expressed in hours and minutes <hours> <minutes>: ");
  scanf("%d %d", &austinTime[hours], &austinTime[mins]);

  irishTime[hours] = austinTime[hours] - 6;
  irishTime[mins] = austinTime[mins];

  if(austinTime[hours] <= 6) {
    irishTime[hours] += 24;
    day = prev;
  }

  printf("The time in Ireland equivalent to %d %02d in Austin is %d %02d of the %s day\n", austinTime[hours], austinTime[mins], irishTime[hours], irishTime[mins], DAYS[day]);
}

void AustintoIrish_currency(void) {
  printf("Enter USD value <dollar> <cents>: ");
  scanf("%d %d", &US_dollar[0], &US_dollar[1]);

  euro = US_dollar[0] + (US_dollar[1] / 100.0);
  euro *= 0.89;

  printf("\nEUR value is: %.2f Euros\n", euro);
}

void AustintoIrish_temp(void) {
  printf("Enter temperature in Farenheit: ");
  scanf("%d", &farenheit);

  celsius = (5.0/9) * (farenheit - 32);

  printf("\nTemperature in Celsius is: %lf", celsius);
}

void AustintoIrish_weight(void) {
  printf("Enter weight in pounds and ounces <pounds> <ounces>: ");
  scanf("%d %d", &US_pounds[0], &US_pounds[1]);

  kilograms = ((double)US_pounds[0] + (US_pounds[1] / 16.0)) * 0.45359327;

  printf("Weight in kg is: %1.3f kg", kilograms);
}

void AustintoIrish_distance(void) {
  printf("Enter distances in miles: ");
  scanf("%lf", &mile);

  kilometer = 1.6093439 * mile;

  printf("Distance in km is: %lf k", kilometer);
}

//----------IrishtoAustin------------
void IrishtoAustin_time(void) {
  int day = same;

  printf("Enter Irish time to be converted, expressed in hours and minutes: ");
  scanf("%d %d", &irishTime[0], &irishTime[1]);

  austinTime[hours] = (irishTime[hours] + 6) % 24;
  austinTime[mins] = irishTime[mins];

  if(austinTime[hours] % 24 <= 6) {
    day = next;
  }

  printf("The time in Austin equivalent to %d %02d in Ireland is %d %02d of the %s day\n", irishTime[hours], irishTime[mins], austinTime[hours], austinTime[mins], DAYS[day]);
}

void IrishtoAustin_currency(void) {

  printf("Enter EUR value <euros>: ");
  scanf("%lf", &euro);

  euro *= 1.13;
  US_dollar[0] = (int)(euro);
  US_dollar[1] = (euro - US_dollar[0]) * 100;

  printf("\nUSD value is: $%d.%d\n", US_dollar[0], US_dollar[1]);

}

void IrishtoAustin_temp(void) {
  float round_test;

  printf("Enter temperature in Celsius: ");
  scanf("%lf", &celsius);

  farenheit = round_test = ((9.0/5) * celsius) + 32;

  if(round_test - farenheit >= 0.5)
    farenheit++;

  printf("Temperature in Farenheit: %d\n", farenheit);
}

void IrishtoAustin_weight(void) {
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

void IrishtoAustin_distance(void) {
  printf("Enter distances in km: ");
  scanf("%lf", &kilometer);

  mile = 0.6213712 * kilometer;

  printf("Distance in miles is: %lf mi", mile);
}

//*********************************  Main Program  ******************************************
int main(void) {

  unsigned int conversionType = 0;
  DAYS[prev] = "previous";
  DAYS[same] = "same";
  DAYS[next] = "next";

  while(conversionType != 11) {

    printf("\nEnter a number from the menu (1-11) to select a specific conversion to perform or to quit: ");
    scanf("%d", &conversionType);

    switch (conversionType) {
      case 1: AustintoIrish_time(); break;
      case 2: IrishtoAustin_time(); break;
      case 3: AustintoIrish_currency(); break;
      case 4: IrishtoAustin_currency(); break;
      case 5: AustintoIrish_temp(); break;
      case 6: IrishtoAustin_temp(); break;
      case 7: IrishtoAustin_weight(); break;
      case 8: AustintoIrish_weight(); break;
      case 9: IrishtoAustin_distance(); break;
      case 10: AustintoIrish_distance(); break;
      case 11: printf("Goodbye\n\n"); break;
      default: printf("\nYou entered an invalid menu item. Please try again.\n"); break;
    }
  }

  return 0;
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
