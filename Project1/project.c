/* This program demonstrates a typical flight ticketing system.
    Programmed by: Wyn Christian Rebanal
                   George Vincent De Vera
    Date Edited: January 2, 2021
*/

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <conio.h>
#include <time.h>

// import the external codes
#include "codes/structs.h"
#include "codes/functions.c"

// Some constant variables
#define TOTAL (100)
#define EQUALS (75)
#define TABS (2)

//File path
#define destinationsFile "assets/destination.txt"
#define transactionsFile "assets/historyTransaction.txt"
#define reportFile "assets/salesReport.txt"

// Color Theme for the program
#define themeColor "COLOR E0"
#define themeColor1 "COLOR 0E"

/* ===================== FUNCTIONS (from functions.c)========================= */
int getDest(FILE *, Category *, int *);
void printAndRecordDest(Category *, int, Information (*)[]);

int anotherService(void);

void run(FILE *, CurrentUser *, int, Information (*)[], SalesReport *, char[]);

void promptUser(CurrentUser *, int);
void outputUser(CurrentUser *, Information (*)[]);
void recordTransaction(FILE *, CurrentUser *, SalesReport *, char[], Information (*)[]);

void printReport(FILE *, int, Information (*)[], SalesReport *, char[], char[]);

void initialize(SalesReport *, FILE *, char[], FILE *, char[], int);

void displayAmount(float);
void fprintAmount(float, FILE *);
void equalSign(int, int);
void printSlash(int);
void printBreakLine(int);
void printLineAsterisk(int);

/* ===============================MAIN PROGRAM========================= */
int main(void)
{
  system(themeColor);

  Documents Files;          // Files
  Category currentCategory; // For getting information per transaction
  static unsigned int totalCategories = 0;
  Information categories[TOTAL]; // To track the informations of destinations with an array
  SalesReport reportTrack;       // To track the final data while the program executing

  //-------------- PHASE 1 ---------------
  // Prepare the files for the user hello
  initialize(&reportTrack, Files.appendTransaction, transactionsFile, Files.salesReport, reportFile, TOTAL);

  // Open and check the file
  Files.getDestinations = fopen(destinationsFile, "r");
  if (!Files.getDestinations)
  {
    printf("\aError opening %s file\n", destinationsFile);
    return 100;
  }

  // Print the destination categories
  static int i = 0;

  equalSign(EQUALS, TABS);

  printf("\n\t\t\t\t\tFLIGHT DESTINATION\t\t\n\n");
  while (getDest(Files.getDestinations, &currentCategory, &totalCategories))
  {
    printAndRecordDest(&currentCategory, ++i, &categories);
  }

  equalSign(EQUALS, TABS);

  //-------------- PHASE 2 ---------------
  // Prompt the user, display and record the transaction, and track the final data
  CurrentUser currentUser;
  do
  {
    //Run(invoke) all the necessary functions to call per transactions
    run(Files.appendTransaction, &currentUser,
        totalCategories, &categories,
        &reportTrack, transactionsFile);

  } while (anotherService());

  //-------------- PHASE 3 ---------------
  // Display the final data and record it to the file
  printReport(Files.salesReport, totalCategories,
              &categories, &reportTrack, reportFile, themeColor1);

  return EXIT_SUCCESS;
}

// Reminders: Don't procrastinate! Put first things first!
