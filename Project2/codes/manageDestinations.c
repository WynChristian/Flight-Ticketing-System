/* 
  This is where manage destination functions

  The following functions are used for 
  managing destinations:
  * manageDestination()
    * addDest()
    * editDest()
    * deleteDest()
    * displayDest()
 */

// this function adds destination in the `destinationFile`
void addDest(Information (*arrayCategories)[], int *total, bool hasBuffer)
{
  system("cls");

  //  checks if the buffer has some value
  if (hasBuffer)
    FLUSH;

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
    return addDest(arrayCategories, total, true);

  result = 0;

  // Prompt the user a new ticket price
  printf("\nEnter price ticket(digits only): ");
  result = scanf("%d", &tempPrice);
  if (!result)
    return addDest(arrayCategories, total, true);

  // Prompt the user a new travel tax
  printf("\nEnter travel tax(digits only): ");
  result = scanf("%d", &tempTax);
  if (!result)
    return addDest(arrayCategories, total, true);

  // Request the user to proceed
  char answer;
  if (promptUser("\nSAVE this RECORD(y/n)?"))
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
  if (promptUser("\nAnother record(y/n)?"))
    return addDest(arrayCategories, total, false);
  else
    // Return to Manage Destination menu
    return;

} // addDest Function

// It updates the existing category's price
void editDest(Information (*arrayCategories)[], int total, bool hasBuffer)
{
  system("cls");
  // checks if the buffer has some irrelevant values
  if (hasBuffer)
    FLUSH;

  int code;
  int result;
  // Prompts the user about the dest code
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
    return editDest(arrayCategories, total, true);

  if (code > total || code < 0)
    return editDest(arrayCategories, total, false);

  int index = code - 1;
  // display the current destination
  printf("\nCurrent destination: %s", (*arrayCategories)[index].country);

  int newPrice;
  // Prompts the user a new price for the selected destination
  printf("\nEnter new ticket price(digit only): ");
  result = scanf("%d", &newPrice);
  if (!result)
    return editDest(arrayCategories, total, true);

  // Ask the user to save the changes
  // If yes, then update the current category's price
  if (promptUser("\nSAVE changes[y/n]?"))
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
  if (promptUser("\nEdit another record[y/n]?"))
    return editDest(arrayCategories, total, false);
  else
    // Return to Manage Destination menu
    return;

} // editDest Function

// It removes the existing category and update the arrays
void deleteDest(Information (*arrayCategories)[], int *total, bool checkBuffer)
{
  system("cls");
  // checks if the buffer has some value
  if (checkBuffer)
    FLUSH;

  // Prompts the user to enter the dest code
  int code;
  int result;
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
    return deleteDest(arrayCategories, total, true);

  if (code > *total || code < 0)
    return deleteDest(arrayCategories, total, false);

  int index = code - 1;

  // Displays the selected category's name and price
  printf("\nDestination name: %s", (*arrayCategories)[index].country);
  printf("\nDestination price: %d", (*arrayCategories)[index].price);

  // Ask the user to proceed to delete the selected category
  // if yes, then delete the selected category
  if (promptUser("\nAre you sure you want to delete this record[y/n]?"))
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
  if (promptUser("\nDelete another record[y/n]?"))
    return deleteDest(arrayCategories, total, false);
  else
    // Return to Manage Destination menu
    return;

} // editDest Function

// Displays the current data in the `reportFile`
void displayDest(Information (*arrayCategories)[], int total)
{
  system("cls");
  if (total == 0)
  {
    printf("\nSorry, there's no available flight right now...");
  }
  else
  {
    // Display the header
    printEquals();
    puts("\n\t\tList of Destinations");
    printf("\n\t\t%-14s %5s\n\n", "Destination", "Price");

    // Display all of the current data
    for (int i = 0; i < total; i++)
    {
      printf("\n\t\t%-14s %d\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price);
    }
    printEquals();
  }

  // Return to Manage Destination menu
  puts("\n\t\tPress any key to RETURN");
  char some = getch();
  return;
} // displayDest Function

// The main function in this file
// It manage the information of `arrayCategories`
void manageDestination(Information (*arrayCategories)[], int *total)
{
  system("cls");
  FLUSH;

  char menu[5][100] = {
      "Add New Destination",
      "Edit",
      "Delete",
      "Display all",
      "Return to MAIN"};

  // Display the menu
  printDash();
  printf("\n\t\tMANAGE DESTINATION\n\n");
  for (int i = 0; i < 5; i++)
    printf("\t\t%d.] %s\n\n", (i + 1), menu[i]);
  printDash();

  // Prompts the user to choose which category
  printf("\t\tEnter Choice: ");

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
