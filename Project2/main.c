#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define destinationsFile "destination.txt"
#define databaseRootFile "database/"
#define TOTAL (100)

typedef struct category Category;
typedef struct info Information;

// This is our external files
#include "codes/structs.h"
#include "codes/manageDestinations.c"
#include "codes/reserveTicket.c"

void readAllDest(FILE *file, int *total, Information (*categories)[]);

// -------------- MANAGE DESTINATION --------------
void manageDestination(FILE *file, Information (*arrayCategories)[], int *total);

// --------------- RESERVE TICKET ------------------
void reserveTicket(char *filePath, Information (*arrayCategories)[], int *total);

// ------------------ BUY TICKET -------------------
// void buyTicket()

int main(void)
{
  Documents Files;
  Information allCategories[TOTAL];
  unsigned int totalNumCategories = 0;

  readAllDest(Files.getDestinations, &totalNumCategories, &allCategories);

  // manageDestination(Files.getDestinations, &allCategories, &totalNumCategories);
  // reserveTicket(databaseRootFile, &allCategories, &totalNumCategories);

  return 0;
}
