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

// -------------- MANAGE DESTINATION --------------
int scanDest(FILE *file, Category *current, int *total);
void recordDest(Category *category, int index, Information (*categories)[]);
void readAllDest(FILE *file, Category *category, int *total, Information (*categories)[]);

void addDest(FILE *file, Information (*arrayCategories)[], int *total, bool check);

void editDest(FILE *file, Information (*arrayCategories)[], int total, bool check);

void deleteDest(FILE *file, Information (*arrayCategories)[], int *total, bool check);

void displayDest(Information (*arrayCategories)[], int total);

void manageDestination(FILE *file, Information (*arrayCategories)[], int *total);

int main(void)
{
  FILE *destinationFile;
  Category currentCategory;
  Information allCategories[TOTAL];
  unsigned int totalNumCategories = 0;

  readAllDest(destinationFile, &currentCategory, &totalNumCategories, &allCategories);

  manageDestination(destinationFile, &allCategories, &totalNumCategories);
  return 0;
}
