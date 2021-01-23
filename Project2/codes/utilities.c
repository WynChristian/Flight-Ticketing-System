/*
  some necessary utilities functions

  The following functions are executed first
  before the MAIN program starts:
  * readAllDest()
    * scanDest()
    * recordDest()
  * initialize()

  Some function globally used:
  *promptUser()

 */

// This function Reads the current data in the `destinationFile`
// It returns (1 or 0) signifying either true or false
int scanDest(FILE *file, Category *current, int *total)
{
  // Read the file and check if its valid; return number (1 / 0)
  int result;

  // A pre-loop that checks if the current line is
  // in the right line to scan the data.
  while ((result = fscanf(file, "%s %d %d", &current->country, &current->price, &current->tax)) == 1)
  {
    // if its not in the right line, recurse (invoke its own function)
    return scanDest(file, current, total);
  }

  // Check the result of `fscanf`
  if (result == EOF)
  {
    // if its EOF, then close the file and return 0/false
    fclose(file);
    return 0;
  }
  else if (result != 3)
  {
    // if its invalid, then display error and exit
    printf("\aError reading data\n");
    exit(0);
  }
  else
  {
    // if its valid, then increment the numCategories
    // and return 1 or true
    *total += 1;
    return 1;
  }
} // scanDest Function

// it stores the current destination from `scanDest` function
// in the categories(array of struct)
void recordDest(Category *category, int index,
                Information (*categories)[])
{
  int i = index - 1;

  // STORE IT in the categories with respect to their index
  strcpy(((*categories)[i]).country, category->country);
  (*categories)[i].price = category->price;
  (*categories)[i].tax = (float)category->tax * 0.01;

  return;
} // recordDest function

// This function will try to analyze and store
// the data in `destinationFile` to `categories` array
void readAllDest(int *total, Information (*categories)[])
{
  *total = 0;
  FILE *file = fopen(destinationsFile, "r");
  if (!file)
  {
    printf("\aError opening %s file\n", destinationsFile);
    exit(0);
  }

  int i = 0;
  Category category;
  // A loop that calls the previous two function
  // its job is to keep reading until
  // either produce error or done scanning
  while (scanDest(file, &category, total))
  {
    recordDest(&category, ++i, categories);
  }

  return;
} // readAllDest Function

// This function initialize the values of the `arrayCategories` array
//   and overwrite/create the `fileTransaction` with headers only
void initialize(Information (*arrayCategories)[],
                Report (*arrayReports)[], int *total,
                int *totalCountry)
{
  // A loop that gives a first value to each array indexes
  for (int i = 0; i < *total; i++)
  {
    strcpy((*arrayReports)[i].country, (*arrayCategories)[i].country);
    (*arrayReports)[i].quantity = 0;
    (*arrayReports)[i].amount = 0;
    (*arrayReports)[i].tax = 0;
    *totalCountry += 1;
  }

  // overwrite the `transactionsFile` with headers only
  FILE *file = fopen(transactionsFile, "w");
  fprintf(file, "%-13s %-5s %-14s %s\n\n", "Destination", "Age", "Sales Amount", "Travel Tax");
  fclose(file);
} // initialize Function

int promptUser(char *question)
{
  int result = 0;
  bool isAnswer = false;

  char answer[1];
  do
  {

    printf(question);
    result = scanf("%s", answer);
    if (!result)
    {
      FLUSH;
      printf("\nInvalid input, please try again...");
    }
    char tempHolder[1];
    strcpy(tempHolder, answer);

    if (strcmp(tempHolder, "y") == 0 || strcmp(tempHolder, "Y") == 0)
    {
      isAnswer = true;
      return 1;
    }

    if (strcmp(tempHolder, "n") == 0 || strcmp(tempHolder, "N") == 0)
    {
      isAnswer = true;
      return 0;
    }
    FLUSH;
  } while (!result || !isAnswer);
}
