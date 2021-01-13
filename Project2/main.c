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
#include "codes/displayReport.c"
#include "codes/mainMenu.c"

int main(void)
{
  Documents Files;
  Information allCategories[TOTAL];
  Report salesReports[TOTAL];
  unsigned int totalNumCategories = 0;
  unsigned int totalCountry = 0;

  readAllDest(Files.getDestinations, &totalNumCategories, &allCategories);
  initialize(&allCategories, &salesReports, &totalNumCategories, &totalCountry, transactionsFile);

  displayMainMenu(&Files, &allCategories, &salesReports, &totalNumCategories, TOTALMEMBERS, databaseRootFile, &totalCountry, transactionsFile, reportFile, MAXTRANSACTION);

  return 0;
}
