#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define destinationsFile "destination.txt"
#define TOTAL (100)

typedef struct category Category;
typedef struct info Information;

struct category
{
  int price;
  int tax;
  char country[50];
};

struct info
{
  char code[5];
  char country[50];
  int price;
  float tax;
};

#include "codes/manageDestinations.c"
#include "codes/reserveTicket.c"
// -------------- MANAGE DESTINATION --------------
void readAllDest(FILE *file, Category *category, int *total, Information (*categories)[]);

void manageDestination(FILE *file, Information (*arrayCategories)[], int *total);

// --------------- RESERVE TICKET ------------------
void reserveTicket(FILE *file, Information (*arrayCategories)[], int *total);

int main(void)
{

  FILE *destinationFile;
  FILE *database;
  Category currentCategory;
  Information allCategories[TOTAL];
  unsigned int totalNumCategories = 0;

  readAllDest(destinationFile, &currentCategory, &totalNumCategories, &allCategories);

  //manageDestination(destinationFile, &allCategories, &totalNumCategories);
  reserveTicket(database, &allCategories, &totalNumCategories);

  return 0;
}
