/* This program demonstrates and implements a typical interactive flight ticketing system.
    Programmed by: Añonuevo, Stphenson
                   Bisda, Marc Lesther
                   Cabrera, Jacob Emmanuel
                   De Vera, George Vincent
                   Mataya, Glen
                   Rebanal, Wyn Christian
    Date: January 23, 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Some pre-proccessed codes
#define FLUSH while (getchar() != '\n')

// This is the file path of the .txt files
#define destinationsFile "assets/destination.txt"
#define transactionsFile "assets/historyTransaction.txt"
#define reportFile "assets/salesReport.txt"

// the database root file
#define databaseRootFile "database/"

#define TOTAL (100)         // size of an arrays
#define MAXMEMBERS (16)     // For reservation per reservation
#define MAXTRANSACTION (16) // For non reservation per transaction
#define DESIGN (70)         // For the design
#define DESIGN2 (35)        // For the design too

// This is our external files
#include "codes/structs.h"            // Just a collection of structs
#include "codes/designs.c"            // Some UI designs
#include "codes/utilities.c"          // some reusable functios
#include "codes/manageDestinations.c" // 1.] Manage Destination
#include "codes/reserveTicket.c"      // 2.] Reserve Ticket
#include "codes/buyTicket.c"          // 3.] Buy Ticket
#include "codes/displayReport.c"      // 4.] Display Report
#include "codes/mainMenu.c"           // The MAIN menu

int main(void)
{
  Information allCategories[TOTAL]; // to track the current data in `destinationsFile`
  Report salesReports[TOTAL];       // To track the sales report

  // To track the numbers of categories in the `destinationFile`
  unsigned int numCategories = 0;
  // To track the total country in the `salesReport` array
  unsigned int totalCountry = 0;

  // Get the information in the `destinationFile`
  readAllDest(&numCategories, &allCategories);

  // Initialize the values in `salesReport` array with 0
  initialize(&allCategories, &salesReports, &numCategories,
             &totalCountry);

  // Start the main program
  displayMainMenu(&allCategories, &salesReports,
                  &numCategories, &totalCountry);

  return 0;
} // main Function
