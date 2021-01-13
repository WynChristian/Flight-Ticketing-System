

float calculateDiscount(int age, int price)
{
  float amount;

  if (age > 5 && age < 60)
  {
    printf("\n TESTING price = %d", price);
    return price;
  }
  else if (age >= 60)
  {
    amount = price * 0.80;
    printf("\n TESTING amount (20%%)= %.2f", amount);
  }
  else if (age > 1 && age < 6)
  {
    amount = price * 0.90;
    printf("\n TESTING amount (10%%)= %.2f", amount);
  }
  else
  {
    printf("\n TESTING amount = 0");
    return 0.00;
  }
  return amount;
}

void calculatePrices(Database (*datas)[], int total, float *price)
{
  float totalAmounts = 0;
  int currentAmount;

  for (int i = 0; i < total; i++)
  {
    int age = (*datas)[i].age;
    currentAmount = calculateDiscount(age, *price);
    (*datas)[i].price = currentAmount;
    totalAmounts += currentAmount;
  }
  printf("\nTotal ticket price: %.2f", totalAmounts);
}

void propmtUserAdultMembers(int *result, int *answer, int *members, int totalMembers)
{
  *result = 0;
  *answer = 0;
  printf("\nHow many adults(18+ years old): ");
  *result = scanf("%d", answer);
  while (!(*result) || *answer < 0 || *answer > totalMembers)
  {
    if (*answer > totalMembers)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", totalMembers);
      printf("\nHow many adults: ");
      *result = scanf("%d", answer);
      break;
    }

    puts("Please enter valid input\n");
    if (!(*result))
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
    printf("\nHow many adults: ");
    *result = scanf("%d", answer);
  }

  *members += *answer;
  return;
}

void propmtUserAdultAges(int *result, int *answer, int *members, Database (*datas)[])
{
  for (int i = 0; i < *members; i++)
  {
    *answer = 0;
    *result = 0;
    printf("\nEnter age: ");
    *result = scanf("%d", answer);
    while (*answer < 18 || !(*result) || *answer > 150)
    {
      puts("Please enter valid input");
      if (!(*result))
      {
        char removeBuffer[100];
        scanf("%s", removeBuffer);
      }
      if (*answer < 18 && *result)
      {
        puts("Warning: Age is too low for adult");
      }
      printf("\nEnter age: ");
      *result = scanf("%d", answer);
    }
    (*datas)[i].age = *answer;
  }
}

void propmtUserChildren(int *result, int *answer, int *members, int *beforeMembers, int totalMembers)
{
  if (*members == totalMembers)
    return;
  *result = 0;
  *answer = 0;

  printf("\nHow many children(17- years old): ");
  *result = scanf("%d", &*answer);
  int tempTotalMembers = (*members) + *answer;
  // Data validation
  while (!(*result) || *answer < 0 || *answer > totalMembers || tempTotalMembers > totalMembers)
  {
    if (tempTotalMembers < totalMembers)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", totalMembers);
      printf("\nAvailable reservation = %d", totalMembers - *members);
    }
    if (*answer > totalMembers)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", totalMembers);
      printf("\nHow many adults: ");
      *result = scanf("%d", answer);
      break;
    }
    puts("Please enter valid input");
    if (!(*result))
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
    printf("\nHow many adults(17- years old): ");
    *result = scanf("%d", answer);
  }
  *beforeMembers = *members;
  *members += *answer;
}

void propmtUserChildrenAges(int *result, int *answer, int *members, int *beforeMembers, Database (*datas)[], int totalMembers)
{
  if (*members == totalMembers)
    return;

  int totalChild = *answer;
  for (int i = 0, j = *beforeMembers; i < totalChild; i++, j++)
  {
    *answer = 0;
    *result = 0;
    printf("\nEnter age: ");
    *result = scanf("%d", answer);
    while (*answer > 17 || !(*result) || *answer < 0)
    {
      puts("Please enter valid input\n");
      if (!(*result))
      {
        char removeBuffer[100];
        scanf("%s", removeBuffer);
      }
      if (*answer > 17)
      {
        puts("Warning: Age is too high for children");
      }
      printf("\nEnter age: ");
      *result = scanf("%d", answer);
    }
    (*datas)[j].age = *answer;
  }
}

int requestReservation(void)
{

  char answer;
  printf("\nProceed your reservation[y/n]? ");
  answer = getch();

  if (answer == 'y' || answer == 'Y')
  {
    return 1;
  }
  else if (answer == 'n' || answer == 'N')
  {
    return 0;
  }
  else
  {
    puts("Please enter valid input");
    return requestReservation();
  }
}

int generateRandom(void)
{
  srand(time(NULL));
  return rand();
}

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
  for (j = 0; num[j] != '\0'; ++j, ++length)
  {
    root[length] = num[j];
  }
  for (j = 0; extnsion[j] != '\0'; ++j, ++length)
  {
    root[length] = extnsion[j];
  }
  root[length] = '\0';
  strcpy(rootFile, root);
}

int checkFilePath(char *sampleFilePath)
{
  FILE *fp = fopen(sampleFilePath, "r");
  if (!fp)
  {
    return 0;
  }
  fclose(fp);
  return 1;
}

void storeData(char *sampleFilePath, char *currentCountry, float currentTax, Database (*currentData)[], int total)
{
  FILE *currentDataFile = fopen(sampleFilePath, "w");
  fprintf(currentDataFile, "%-10s %7.f %d\n\n", currentCountry, currentTax, total);
  for (int i = 0; i < total; i++)
  {
    fprintf(currentDataFile, "%-7d %10.2f\n", (*currentData)[i].age, (*currentData)[i].price);
  }
  fclose(currentDataFile);
  return;
}

void reserveTicket(char *databaseFile, Information (*arrayCategories)[], int *total, int totalPassenger)
{
  //Display destinations-
  puts("FLIGHT DESTINATION\n");
  for (int i = 0; i < *total; i++)
  {
    printf("%d %-19s %d.00\n", (i + 1), (*arrayCategories)[i].country, (*arrayCategories)[i].price);
  }
  printf("%d %s\n", *total + 1, "Return to MAIN");

  //Prompt user (Choose categories)
  printf("Select reserve destination: ");

  int answer;
  int result;
  result = scanf("%d", &answer);
  while ((answer - 1) > *total || answer < 0 || !result)
  {
    puts("Please enter valid input\n");
    printf("Select reserve destination: ");
    result = scanf("%d", &answer);

    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
  }

  if (answer == (*total + 1))
    return;

  char tempCountry[100];
  float tempTax;
  float tempPrice;
  int members = 0;
  Database reservedDATA[20];

  //Store the current country
  strcpy(tempCountry, (*arrayCategories)[answer - 1].country);
  tempTax = (*arrayCategories)[answer - 1].tax * 100;
  tempPrice = (float)(*arrayCategories)[answer - 1].price;

  //propmt user (Quantity of adult members (18+ years old))
  propmtUserAdultMembers(&result, &answer, &members, totalPassenger);
  //Prompt user (adult member's age)
  propmtUserAdultAges(&result, &answer, &members, &reservedDATA);
  //propmt user (Quantity of children members (17- years old))
  int adultMembers;
  propmtUserChildren(&result, &answer, &members, &adultMembers, totalPassenger);
  //Prompt user (children member's age)
  propmtUserChildrenAges(&result, &answer, &members, &adultMembers, &reservedDATA, totalPassenger);

  calculatePrices(&reservedDATA, members, &tempPrice);

  if (requestReservation())
  {
    char root[100];
    int random;
    do
    {
      strcpy(root, databaseFile);
      random = generateRandom();
      generateFilePath(root, random);
    } while (checkFilePath(root));
    printf("\nYour reservation code: \"%d\"", random);
    storeData(root, tempCountry, tempTax, &reservedDATA, members);
  }

  puts("\nPress any KEY to return to MAIN");
  getch();
  return;
}