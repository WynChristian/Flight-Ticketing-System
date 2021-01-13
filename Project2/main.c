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
#define TOTALMEMBERS (16)   //For reservation per reservation
#define MAXTRANSACTION (16) //For non reservation per transaction

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
void reserveTicket(char *filePath, Information (*arrayCategories)[], int *total, int totalMembers);

// ------------------ BUY TICKET -------------------
void buyTicket(Documents *files, Information (*arrayCategories)[], Report (*arrayReports)[], unsigned int *total, char *dataRootFile, int *totalCountries, char *transactionFilePath, char *reportFilePath, int maxTransaction);

int main(void)
{
  Documents Files;
  Information allCategories[TOTAL];
  Report salesReports[TOTAL];
  unsigned int totalNumCategories = 0;
  unsigned int totalCountry = 0;

  readAllDest(Files.getDestinations, &totalNumCategories, &allCategories);
  initialize(&allCategories, &salesReports, &totalNumCategories, &totalCountry);
  printf("\n\tTESTING totalCountry = %d", totalCountry);
  // manageDestination(Files.getDestinations, &allCategories, &totalNumCategories);
  // reserveTicket(databaseRootFile, &allCategories, &totalNumCategories, TOTALMEMBERS);
  buyTicket(&Files, &allCategories, &salesReports, &totalNumCategories, databaseRootFile, &totalCountry, transactionsFile, reportFile, MAXTRANSACTION);
  return 0;
}
