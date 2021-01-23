/* 
  This is where "Reserve Ticket" category locates in.
  Its generally purpose is to make a file in the `databaseRootFile` root file
  to save the current reservation information

  Here are the function that used in this category
    * reserveTicket()
      * promptUserAdultMembers()
      * promptUserAdultAges()
      * promptUserChildren()
      * promptUserChildrenAges()
      * calculatePrices()
      * promptUser()
        * generateRandom()
        * generateFilePath()
        * checkFilePath()
 */

// It returns a (float)price with/out discount
float calculateDiscount(int age, int price)
{
  float amount;

  if (age > 5 && age < 60)
  {
    return price;
  }
  else if (age >= 60)
  {
    amount = price * 0.80;
  }
  else if (age > 1 && age < 6)
  {
    amount = price * 0.90;
  }
  else
  {
    return 0.00;
  }
  return amount;
} // calculateDiscount Function

// It calculates all the prices with respect to their ages
void calculatePrices(Database (*datas)[], int total, float *price)
{
  float totalAmounts = 0;
  int currentAmount;

  // Loop through the `datas` array to store the discounted prices
  //  with respect to their indeces
  for (int i = 0; i < total; i++)
  {
    int age = (*datas)[i].age;
    currentAmount = calculateDiscount(age, *price);
    (*datas)[i].price = currentAmount;

    // Increment it to `totalAmount` per currentAmount
    totalAmounts += currentAmount;
  }

  // Display the total price
  printf("\n\t\tTotal ticket price: %.2f", totalAmounts);
  return;
} // calculatePrices Function

// It prompts the user about the no. of adult members
void promptUserAdultMembers(int *members)
{
  int result = 0;
  int answer = 0;

  // Ask user the no. of adults
  printf("\n\t\tHow many adults(18+ years old): ");
  result = scanf("%d", &answer);

  // check the input validity
  while (!(result) || answer < 0 || answer > MAXMEMBERS)
  {
    if (answer > MAXMEMBERS)
    {
      printf("\n\t\tSorry, we can reserve for maximum of %d members only", MAXMEMBERS);
      printf("\n\t\tHow many adults: ");
      result = scanf("%d", &answer);
      break;
    }

    puts("\t\tPlease enter valid input\n");
    if (!(result))
      FLUSH;

    printf("\n\t\tHow many adults: ");
    result = scanf("%d", &answer);
  }

  // Increment `members` to track the total no. of members
  *members += answer;
  return;
} // promptUserAdultMembers Function

// It prompts the user about each ages for each adult members
void promptUserAdultAges(int *members, Database (*datas)[])
{
  int answer;
  int result;
  // A loop to track the total prompts of ages
  for (int i = 0; i < *members; i++)
  {
    answer = 0;
    result = 0;

    // Ask the user about the current member's age
    printf("\n\t\tEnter age: ");
    result = scanf("%d", &answer);

    // Check the input data validity
    while (answer < 18 || !(result) || answer > 150)
    {
      puts("\t\tPlease enter valid input");
      if (!(result))
        FLUSH;

      if (answer < 18 && result)
      {
        puts("\t\tWarning: Age is too low for adult");
      }
      printf("\n\t\tEnter age: ");
      result = scanf("%d", &answer);
    }

    // Store it in the `datas` array with respect to their indeces
    (*datas)[i].age = answer;
  }
  return;
} // promptUserAdultAges Function

// It prompts the user about how many children
void promptUserChildren(int *answer, int *members,
                        int *beforeMembers)
{
  // if the no. of members reach the maximum no. of members
  //   return to the `reserveTicket` function
  if (*members == MAXMEMBERS)
    return;

  int result = 0;

  // Prompt the user about the no. of children
  printf("\n\t\tHow many children(17- years old): ");
  result = scanf("%d", answer);
  int tempTotalMembers = (*members) + *answer;

  // check the input data validity
  while (!(result) || *answer < 0 || *answer > MAXMEMBERS || tempTotalMembers > MAXMEMBERS)
  {
    if (tempTotalMembers < MAXMEMBERS)
    {
      printf("\n\t\tSorry, we can reserve for maximum of %d members only", MAXMEMBERS);
      printf("\n\t\tAvailable reservation = %d", MAXMEMBERS - *members);
    }
    if (*answer > MAXMEMBERS)
    {
      printf("\n\t\tSorry, we can reserve for maximum of %d members only", MAXMEMBERS);
      printf("\n\t\tHow many adults: ");
      result = scanf("%d", answer);
      break;
    }
    puts("\t\tPlease enter valid input");
    if (!(result))
      FLUSH;

    printf("\n\t\tHow many adults(17- years old): ");
    result = scanf("%d", answer);
  } // while loop

  //Track the total no. of members in the current reservation
  *beforeMembers = *members;
  *members += *answer;
  return;
} // promptUserChildren Function

// It prompts the user about the age for each children members
void promptUserChildrenAges(int *answer, int *members,
                            int *beforeMembers,
                            Database (*datas)[])
{
  // If the current no. of members reach the maximum no. of reservation members
  //    return to `reserveTicket` function
  if (*members == MAXMEMBERS)
    return;

  int totalChild = *answer;
  int result = 0;
  // A loop that prompts the user until it reaches the no. of children members
  for (int i = 0, j = *beforeMembers; i < totalChild; i++, j++)
  {
    *answer = 0;
    result = 0;

    // ask the user about current child's age
    printf("\n\t\tEnter age: ");
    result = scanf("%d", answer);

    // Check the input data validity
    while (*answer > 17 || !(result) || *answer < 0)
    {
      puts("\t\tPlease enter valid input\n");
      if (!(result))
        FLUSH;

      if (*answer > 17)
      {
        puts("\t\tWarning: Age is too high for children");
      }
      printf("\n\t\tEnter age: ");
      result = scanf("%d", answer);
    }
    // store the current age in the `datas` array with respect to their indeces
    (*datas)[j].age = *answer;
  } // for loop
  return;
} // promptUserChildrenAges Function

// It returns a pseudo-random number with a seed of current time
int generateRandom(void)
{
  srand(time(NULL));
  return rand();
} // generateRandom Function

// It generates a file path by concatenating the `rootFile`, `randomCode`, and ".txt"
//    returns a string with a format of "`rootFile`/`randomCode`.txt"
void generateFilePath(char *rootFile, int randomCode)
{
  char num[20];
  char root[100];
  char extnsion[] = ".txt";
  strcpy(root, rootFile);
  sprintf(num, "%d", randomCode);

  int length, j;

  length = 0;
  while (root[length] != '\0')
  {
    length += 1;
  }

  // concatenate the `rootFile` with the current `randomCode`
  for (j = 0; num[j] != '\0'; ++j, ++length)
  {
    root[length] = num[j];
  }

  // concatenate the `rootFile` with ".txt" extension
  for (j = 0; extnsion[j] != '\0'; ++j, ++length)
  {
    root[length] = extnsion[j];
  }
  // concatenate it with '\0' for string ending
  root[length] = '\0';

  // update the `rootFile` variable with the final value of `root` string
  strcpy(rootFile, root);
  return;
} // generateFilePath Function

// It checks if the current file path is not existing
//   returns  1 or 2; signifying `true` or `false`
int checkFilePath(char *sampleFilePath)
{
  FILE *fp = fopen(sampleFilePath, "r");
  if (!fp)
  {
    return 0;
  }
  fclose(fp);
  return 1;
} // checkFilePath Function

// This function generate a new file to write the whole data of current reservation
//   the format of writing the data is in the `database/README.md` file
void storeData(char *sampleFilePath, char *currentCountry,
               float currentTax, Database (*currentData)[],
               int total)
{
  FILE *currentDataFile = fopen(sampleFilePath, "w");
  fprintf(currentDataFile, "%-10s %7.f %d\n\n", currentCountry, currentTax, total);
  for (int i = 0; i < total; i++)
  {
    fprintf(currentDataFile, "%-7d %10.2f\n", (*currentData)[i].age, (*currentData)[i].price);
  }
  fclose(currentDataFile);
  return;
} // storeData Function

// It is the main function of the current file
void reserveTicket(Information (*arrayCategories)[],
                   int *total)
{
  system("cls");

  // Display all the current available destinations
  printAsterisk();
  puts("\n\t\tFLIGHT DESTINATION\n");
  for (int i = 0; i < *total; i++)
  {
    printf("\t\t%d %-19s %d.00\n\n", (i + 1), (*arrayCategories)[i].country, (*arrayCategories)[i].price);
  }
  printf("\t\t%d %s\n", *total + 1, "Return to MAIN\n");
  printAsterisk();

  //Prompt user to choose which categories
  printf("\n\t\tSelect reserve destination: ");

  int answer;
  int result;
  result = scanf("%d", &answer);

  // Check the input data validity
  while ((answer - 1) > *total || answer < 0 || !result)
  {
    puts("\t\tPlease enter valid input\n");
    printf("\t\tSelect reserve destination: ");
    result = scanf("%d", &answer);

    if (!result)
      FLUSH;
  }

  if (answer == (*total + 1))
    return;

  char tempCountry[100];
  float tempTax;
  float tempPrice;
  int members = 0;
  Database reservedDATA[20];

  // Store the current selected destination
  strcpy(tempCountry, (*arrayCategories)[answer - 1].country);
  tempTax = (*arrayCategories)[answer - 1].tax * 100;
  tempPrice = (float)(*arrayCategories)[answer - 1].price;

  // Prompt the user about adults no. of members and their ages
  promptUserAdultMembers(&members);
  promptUserAdultAges(&members, &reservedDATA);

  int adultMembers;
  // Prompt the user about children no. of members and their ages
  promptUserChildren(&answer, &members, &adultMembers);
  promptUserChildrenAges(&answer, &members, &adultMembers, &reservedDATA);

  // Display the total prices with discount
  calculatePrices(&reservedDATA, members, &tempPrice);

  // Ask the user to proceed the current reservation
  if (promptUser("\n\t\tProceed your reservation[y/n]? "))
  {
    char root[100];
    int random;
    // Generate a file with a unique `random code`
    do
    {
      strcpy(root, databaseRootFile);
      random = generateRandom();
      generateFilePath(root, random);
    } while (checkFilePath(root));

    // Display the current reservation code
    printf("\n\t\tYour reservation code: \"%d\"", random);

    // Store the data in the current new generate file
    storeData(root, tempCountry, tempTax, &reservedDATA, members);
  }

  puts("\n\t\tPress any KEY to return to MAIN");
  printSlash();
  getch();
  FLUSH;
  // Return to MAIN
  return;
} // reserveTicket Function