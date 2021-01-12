#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define destinationsFile "assets/destination.txt"
#define transactionsFile "assets/historyTransaction.txt"
#define reportFile "assets/salesReport.txt"
#define databaseRootFile "database/"

#define TOTAL (100)

typedef struct category Category;
typedef struct info Information;

// This is our external files
#include "codes/structs.h"
#include "codes/manageDestinations.c"
#include "codes/reserveTicket.c"
#include "codes/buyTicket.c"

void readAllDest(FILE *file, int *total, Information (*categories)[]);
void initialize(Information (*arrayCategories)[], Report (*arrayReports)[], int *totalReport, int *totalCountry);

// -------------- MANAGE DESTINATION --------------
void manageDestination(FILE *file, Information (*arrayCategories)[], int *total);

// --------------- RESERVE TICKET ------------------
void reserveTicket(char *filePath, Information (*arrayCategories)[], int *total);

// ------------------ BUY TICKET -------------------
void buyTicket(FILE *fileTransaction, Information (*arrayCategories)[], Report (*arrayReports)[], int total, char *dataRootFile, int *totalCountries, char *transactionFilePath);

int main(void)
{
  Documents Files;
  Information allCategories[TOTAL];
  Report salesReports[TOTAL];
  unsigned int totalNumCategories = 0;
  unsigned int totalCountry = 0;

  readAllDest(Files.getDestinations, &totalNumCategories, &allCategories);
  initialize(&allCategories, &salesReports, &totalNumCategories, &totalCountry);

  // manageDestination(Files.getDestinations, &allCategories, &totalNumCategories);
  // reserveTi1cket(databaseRootFile, &allCategories, &totalNumCategories);
  buyTicket(Files.appendTransaction, &allCategories, &salesReports, totalNumCategories, databaseRootFile, &totalCountry, transactionsFile);
  return 0;
}
