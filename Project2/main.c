#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// This is the file path of our source code
#define destinationsFile "assets/destination.txt"
#define transactionsFile "assets/historyTransaction.txt"
#define reportFile "assets/salesReport.txt"
#define databaseRootFile "database/"

#define TOTAL (100)         // size of an arrays
#define MAXMEMBERS (16)     //For reservation per reservation
#define MAXTRANSACTION (16) //For non reservation per transaction

// This is our external files
#include "codes/structs.h"            // just a collection of structs
#include "codes/manageDestinations.c" // 1.] Manage Destination
#include "codes/reserveTicket.c"      // 2.] Reserve Ticket
#include "codes/buyTicket.c"          // 3.] Buy Ticket
#include "codes/displayReport.c"      // 4.] Display Report
#include "codes/mainMenu.c"           // The MAIN menu

int main(void)
{
  Documents Files;
  Information allCategories[TOTAL]; // to track the current data in `destinationsFile`
  Report salesReports[TOTAL];       // To track the sales report

  // To track the numbers of categories in the `destinationFile`
  unsigned int numCategories = 0;
  // To track the total country in the `salesReport` array
  unsigned int totalCountry = 0;

  // Get the information in the `destinationFile`
  readAllDest(Files.getDestinations, &numCategories, &allCategories);

  // Initialize the values in `salesReport` array with 0
  initialize(&allCategories, &salesReports, &numCategories,
             &totalCountry, transactionsFile);

  // Start the main program
  displayMainMenu(&Files, &allCategories, &salesReports,
                  &numCategories, MAXMEMBERS,
                  databaseRootFile, &totalCountry,
                  transactionsFile, reportFile,
                  MAXTRANSACTION);

  return 0;
} // main
