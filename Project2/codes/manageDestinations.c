/* 
  This is where manage destination functions
  
  The following functions are executed first 
  before the MAIN program starts:
  * readAllDest()
    * scanDest()
    * recordDest()
  * initialize()
  
  The following functions are used for 
  managing destinations:
  * manageDestination()
    * addDest()
    * editDest()
    * deleteDest()
    * displayDest()
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

// this function adds destination in the `destinationFile`
void addDest(Information (*arrayCategories)[], int *total, bool checkBuffer)
{
  system("cls");

  //  checks if the buffer has some value
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
    printf("\nPlease enter valid input");
  }

  int result;
  char tempDest[50];
  unsigned int tempPrice;
  unsigned int tempTax;

  // Prompt the user the dest code
  printf("\n\nDestination Code: %03d", (*total + 1));

  // Prompt the user a new destination
  printf("\nEnter new destination(No space): ");
  result = scanf("%s", tempDest);
  if (!result)
  {
    puts("\nPlease Enter valid input");
    return addDest(arrayCategories, total, true);
  }

  result = 0;

  // Prompt the user a new ticket price
  printf("\nEnter price ticket(digits only): ");
  result = scanf("%d", &tempPrice);
  while (!result)
  {
    return addDest(arrayCategories, total, true);
  }

  // Prompt the user a new travel tax
  printf("\nEnter travel tax(digits only): ");
  result = scanf("%d", &tempTax);
  if (!result)
  {
    return addDest(arrayCategories, total, true);
  }

  // Request the user to proceed
  char answer;
  printf("\nSAVE this RECORD(y/n)?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    int index = *total;
    // Append the data in the file
    FILE *file = fopen(destinationsFile, "a");
    fprintf(file, "\n%-10s %10d %d%%", tempDest, tempPrice, tempTax);
    fclose(file);

    // Store it in the struct information array
    strcpy((*arrayCategories)[index].country, tempDest);
    (*arrayCategories)[index].price = tempPrice;
    (*arrayCategories)[index].tax = tempTax * 0.01;

    *total += 1;
  }

  // Prompt the user for another new record
  printf("\nAnother record(y/n)?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return addDest(arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    // Return to Manage Destination menu
    return;
  }

  return;
} // addDest Function

// It updates the existing category's price
void editDest(Information (*arrayCategories)[], int total, bool checkBuffer)
{
  system("cls");
  // checks if the buffer has some irrelevant values
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
    printf("\nPlease Enter valid input");
  }

  int code;
  int result;
  // Prompts the user about the dest code
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
  {
    return editDest(arrayCategories, total, true);
  }
  if (code > total || code < 0)
  {
    return editDest(arrayCategories, total, false);
  }

  int index = code - 1;
  // display the current destination
  printf("\nCurrent destination: %s", (*arrayCategories)[index].country);

  int newPrice;
  // Prompts the user a new price for the selected destination
  printf("\nEnter new ticket price(digit only): ");
  result = scanf("%d", &newPrice);
  if (!result)
  {
    return editDest(arrayCategories, total, true);
  }

  char answer;
  // Ask the user to save the changes
  puts("SAVE changes[y/n]?");
  answer = getch();

  // If yes, then update the current category's price
  if (answer == 'y' || answer == 'Y')
  {
    // store the new price
    (*arrayCategories)[index].price = newPrice;

    // Reprint all the data with the new update
    FILE *file = fopen(destinationsFile, "w+");
    fprintf(file, "%-15s %s %s\n\n", "Destination", "Price per Destination", "Travel tax");
    for (int i = 0; i < total; i++)
    {
      float travelTax = ((*arrayCategories)[i].tax) * 100;
      fprintf(file, "%-17s %-15d %.f%%\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price, travelTax);
    }
    fclose(file);
  }

  // Ask the user for another record
  puts("Edit another record[y/n]?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return editDest(arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    // Return to Manage Destination menu
    return;
  }
} // editDest Function

// It removes the existing category and update the arrays
void deleteDest(Information (*arrayCategories)[], int *total, bool checkBuffer)
{
  system("cls");
  // checks if the buffer has some value
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
    puts("\nPlease enter valid input ");
  }

  // Prompts the user to enter the dest code
  int code;
  int result;
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
  {
    return deleteDest(arrayCategories, total, true);
  }
  if (code > *total || code < 0)
  {
    return deleteDest(arrayCategories, total, false);
  }
  int index = code - 1;

  // Displays the selected category's name and price
  printf("\nDestination name: %s", (*arrayCategories)[index].country);
  printf("\nDestination price: %d", (*arrayCategories)[index].price);

  // Ask the user to proceed to delete the selected category
  char answer;
  puts("Are you sure you want to delete this record[y/n]?");
  answer = getch();

  // if yes, then delete the selected category
  if (answer == 'y' || answer == 'Y')
  {
    int totalNum = *total - 1;
    puts("\nDeleting this record...");

    // Reprint the `destinationsFile` headings
    FILE *file = fopen(destinationsFile, "w+");
    fprintf(file, "%-15s %s %s\n\n", "Destination", "Price per Destination", "Travel tax");

    // A loop that updates the `arrayCategories` array
    for (int i = 0; i < totalNum; i++)
    {
      if (i >= index)
      {
        // if i is greater than or equal than the index
        //  of the selected category, then store the
        //  current `i` data with the `next` index data
        int next = i + 1;
        strcpy((*arrayCategories)[i].country, (*arrayCategories)[next].country);
        (*arrayCategories)[i].price = (*arrayCategories)[next].price;
        (*arrayCategories)[i].tax = (*arrayCategories)[next].tax;
      }

      // print the data in the `destinationsFile`
      float travelTax = (*arrayCategories)[i].tax * 100;
      fprintf(file, "%-17s %-15d %.f%%\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price, travelTax);
    }

    // Decrement the current total number of categories
    *total -= 1;
    fclose(file);
  }

  // Ask the user to edit another record
  puts("\nDelete another record[y/n]?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return deleteDest(arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    // Return to Manage Destination menu
    return;
  }
} // editDest Function

// Displays the current data in the `reportFile`
void displayDest(Information (*arrayCategories)[], int total)
{
  if (total == 0)
  {
    printf("\nSorry, there's no available flight for right now");
  }
  else
  {
    // Display the header
    puts("\nList of Destinations");
    printf("\n%-14s %5s\n\n", "Destination", "Price");

    // Display all of the current data
    for (int i = 0; i < total; i++)
    {
      printf("\n%-14s %d", (*arrayCategories)[i].country, (*arrayCategories)[i].price);
    }
  }

  // Return to Manage Destination menu
  puts("\nPress any key to RETURN");
  char some = getch();
  return;
} // displayDest Function

// The main function in this file
// It manage the information of `arrayCategories`
void manageDestination(Information (*arrayCategories)[], int *total)
{
  system("cls");

  char menu[5][100] = {
      "Add New Destination",
      "Edit",
      "Delete",
      "Display all",
      "Return to MAIN"};

  // Display the menu
  printf("\nMANAGE DESTINATION\n\n");
  for (int i = 0; i < 5; i++)
    printf("%d.] %s\n", (i + 1), menu[i]);

  // Prompts the user to choose which category
  printf("Enter Choice: ");

  char choice;
  choice = getchar();

  // Analyze the `choice` stored value
  switch (choice)
  {
  case '1':
    // if '1', then invoke `addDest` Function
    addDest(arrayCategories, total, false);
    manageDestination(arrayCategories, total);
    break;
  case '2':
    // if '2', then invoke `editDest` Function
    editDest(arrayCategories, *total, false);
    manageDestination(arrayCategories, total);
    break;
  case '3':
    // if '3', then invoke `deleteDest` Function
    deleteDest(arrayCategories, total, false);
    manageDestination(arrayCategories, total);
    break;
  case '4':
    // if '4', then invoke `displayDest` Function
    displayDest(arrayCategories, *total);
    manageDestination(arrayCategories, total);
    break;
  case '5':
    // if '5', then return to MAIN
    break;
  default:
    puts("Error, invalid input. try again");
    manageDestination(arrayCategories, total);
  }

  return;
}

// This function initialize the values of the `arrayCategories` array
//   and overwrite/create the `fileTransaction` with headers only
void initialize(Information (*arrayCategories)[],
                Report (*arrayReports)[], int *total,
                int *totalCountry)
{
  // A loop that gives a first value to each array indeces
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