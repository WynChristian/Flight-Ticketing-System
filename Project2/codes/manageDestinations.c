
int scanDest(FILE *file, Category *current, int *total)
{
  // Read the file and check if its valid; return number (1 / 0)
  int result;

  while ((result = fscanf(file, "%s %d %d", &current->country, &current->price, &current->tax)) == 1)
  {
    return scanDest(file, current, total);
  }

  if (result == EOF)
  {
    fclose(file);
    return 0;
  }
  else if (result != 3)
  {
    printf("\aError reading data\n");
    return 0;
  }
  else
  {
    *total += 1;
    return 1;
  }
} //getDest

void recordDest(Category *category, int index,
                Information (*categories)[])
{
  // Store the destination in the categories(array of struct)
  int i = index - 1;

  // STORE IT in the categories with respect to their index

  strcpy(((*categories)[i]).country, category->country);
  (*categories)[i].price = category->price;
  (*categories)[i].tax = (float)category->tax * 0.01;

  return;
} // printDest

void readAllDest(FILE *file, Category *category, int *total, Information (*categories)[])
{
  *total = 0;
  file = fopen(destinationsFile, "r");
  if (!file)
  {
    printf("\aError opening %s file\n", destinationsFile);
    exit(0);
  }

  int i = 0;
  while (scanDest(file, category, total))
  {
    recordDest(category, ++i, categories);
    printf("%s %03d\n", ((*categories)[i - 1]).country, *total);
  }

  return;
}

void addDest(FILE *file, Information (*arrayCategories)[], int *total, bool checkBuffer)
{
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
  }

  int result;
  char tempDest[50];
  unsigned int tempPrice;
  unsigned int tempTax;

  printf("\n\nDestination Code: %03d", (*total + 1));

  printf("\nEnter new destination(No space): ");
  scanf("%s", tempDest);

  printf("\nEnter price ticket(digits only): ");
  result = scanf("%d", &tempPrice);
  while (!result)
  {
    puts("\nPlease Enter valid input");
    return addDest(file, arrayCategories, total, true);
  }

  printf("\nEnter travel tax(digits only): ");
  result = scanf("%d", &tempTax);
  if (!result)
  {
    puts("\nPlease Enter valid input");
    return addDest(file, arrayCategories, total, true);
  }

  char answer;
  printf("SAVE this RECORD(y/n)?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    int index = *total;
    //append the data in the file
    file = fopen(destinationsFile, "a");
    fprintf(file, "\n%-10s %10d %d%%", tempDest, tempPrice, tempTax);
    fclose(file);

    //store it in the struct information array
    strcpy((*arrayCategories)[index].country, tempDest);
    (*arrayCategories)[index].price = tempPrice;
    (*arrayCategories)[index].tax = tempTax * 0.01;

    *total += 1;
  }

  printf("\nAnother record(y/n)?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return addDest(file, arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    return;
  }

  return;
}

void editDest(FILE *file, Information (*arrayCategories)[], int total, bool checkBuffer)
{
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
  }

  int code;
  int result;
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
  {
    puts("\nplease enter valid input with format (###)");
    return editDest(file, arrayCategories, total, true);
  }
  if (code > total || code < 0)
  {
    puts("Invalid code, can't be found");
    puts("The Destination code is based on their number index");
    return editDest(file, arrayCategories, total, false);
  }
  int index = code - 1;
  printf("\nCurrent destination: %s", (*arrayCategories)[index].country);

  int newPrice;
  printf("\nEnter new ticket price(digit only): ");
  result = scanf("%d", &newPrice);
  if (!result)
  {
    puts("\nplease enter valid input with format (###)");
    return editDest(file, arrayCategories, total, true);
  }

  (*arrayCategories)[index].price = newPrice;

  char answer;
  puts("SAVE changes[y/n]?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    file = fopen(destinationsFile, "w+");
    fprintf(file, "%-15s %s %s\n\n", "Destination", "Price per Destination", "Travel tax");
    for (int i = 0; i < total; i++)
    {
      float travelTax = ((*arrayCategories)[i].tax) * 100;
      fprintf(file, "%-17s %-15d %.f%%\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price, travelTax);
    }
    fclose(file);
  }

  puts("Edit another record[y/n]?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return editDest(file, arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    return;
  }
}

void deleteDest(FILE *file, Information (*arrayCategories)[], int *total, bool checkBuffer)
{
  if (checkBuffer)
  {
    char someBuffer[10];
    scanf("%s", &someBuffer);
    checkBuffer = false;
  }

  int code;
  int result;
  printf("\n\nEnter destination code(000 by their index): ");
  result = scanf("%d", &code);
  if (!result)
  {
    puts("\nplease enter valid input with format (###)");
    return deleteDest(file, arrayCategories, total, true);
  }
  if (code > *total || code < 0)
  {
    puts("Invalid code, can't be found");
    puts("The Destination code is based on their number index");
    return deleteDest(file, arrayCategories, total, false);
  }
  int index = code - 1;

  printf("\nDestination name: %s", (*arrayCategories)[index].country);
  printf("\nDestination price: %d", (*arrayCategories)[index].price);

  char answer;
  puts("Are you sure you want to delete this record[y/n]?");
  answer = getch();

  if (answer == 'y' || answer == 'Y')
  {
    int totalNum = *total - 1;
    puts("\nDeleting this record...");

    Information newCategories[TOTAL];
    file = fopen(destinationsFile, "w+");
    fprintf(file, "%-15s %s %s\n\n", "Destination", "Price per Destination", "Travel tax");
    for (int i = 0; i < totalNum; i++)
    {
      if (i >= index)
      {
        int next = i + 1;
        strcpy((*arrayCategories)[i].country, (*arrayCategories)[next].country);
        (*arrayCategories)[i].price = (*arrayCategories)[next].price;
        (*arrayCategories)[i].tax = (*arrayCategories)[next].tax;
      }

      float travelTax = (*arrayCategories)[i].tax * 100;
      fprintf(file, "%-17s %-15d %.f%%\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price, travelTax);
    }

    *total -= 1;
    fclose(file);
  }

  puts("Edit another record[y/n]?");
  answer = getch();
  if (answer == 'y' || answer == 'Y')
  {
    return deleteDest(file, arrayCategories, total, false);
  }
  else if (answer == 'n' || answer == 'N')
  {
    return;
  }
}

void displayDest(Information (*arrayCategories)[], int total)
{
  puts("List of Destinations\n");
  printf("%-14s %5s\n\n", "Destination", "Price");
  for (int i = 0; i < total; i++)
  {
    printf("%-14s %d\n", (*arrayCategories)[i].country, (*arrayCategories)[i].price);
  }
  puts("Press any key to RETURN");
  char some = getch();
  return;
}

void manageDestination(FILE *file, Information (*arrayCategories)[], int *total)
{
  char choice;
  char menu[5][100] = {
      "Add New Destination",
      "Edit",
      "Delete",
      "Display all",
      "Return to MAIN"};

  printf("\nMANAGE DESTINATION\n\n");
  for (int i = 0; i < 5; i++)
    printf("%d.] %s\n", (i + 1), menu[i]);

  printf("Enter Choice: ");
  choice = getchar();

  switch (choice)
  {
  case '1':
    addDest(file, arrayCategories, total, false);
    manageDestination(file, arrayCategories, total);
  case '2':
    editDest(file, arrayCategories, *total, false);
    manageDestination(file, arrayCategories, total);
  case '3':
    deleteDest(file, arrayCategories, total, false);
    manageDestination(file, arrayCategories, total);
  case '4':
    displayDest(arrayCategories, *total);
    manageDestination(file, arrayCategories, total);
  case '5':
    puts("You picked 5");
    break;
  default:
    puts("Error, invalid input. try again");
    manageDestination(file, arrayCategories, total);
  }
}