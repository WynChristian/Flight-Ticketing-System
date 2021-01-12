#define TOTALMEMBERS (16)

typedef struct database database;

struct database
{
  int age;
  int price;
};

void propmtUserAdultMembers(int *result, int *answer, int *members)
{
  *result = 0;
  *answer = 0;
  printf("\nHow many adults(18+ years old): ");
  *result = scanf("%d", answer);
  while (!(*result) || *answer < 0 || *answer > TOTALMEMBERS)
  {
    if (*answer > TOTALMEMBERS)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", TOTALMEMBERS);
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

void propmtUserAdultAges(int *result, int *answer, int *members, database (*datas)[])
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

void propmtUserChildren(int *result, int *answer, int *members)
{
  if (*members == TOTALMEMBERS)
    return;
  *result = 0;
  *answer = 0;

  printf("\nHow many children(17- years old): ");
  *result = scanf("%d", &*answer);
  int tempTotalMembers = (*members) + *answer;
  // Data validation
  while (!(*result) || *answer < 0 || *answer > TOTALMEMBERS || tempTotalMembers > TOTALMEMBERS)
  {
    if (tempTotalMembers < TOTALMEMBERS)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", TOTALMEMBERS);
      printf("\nAvailable reservation = %d", TOTALMEMBERS - *members);
    }
    if (*answer > TOTALMEMBERS)
    {
      printf("\nSorry, we can reserve for maximum of %d members only", TOTALMEMBERS);
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

  *members += *answer;
}

void propmtUserChildrenAges(int *result, int *answer, int *members, database (*datas)[])
{
  if (*members == TOTALMEMBERS)
    return;

  int totalChild = *answer;
  for (int i = 0, j = *members; i < totalChild; i++, j++)
  {
    *answer = 0;
    result = 0;
    printf("\nEnter age: ");
    *result = scanf("%d", &*answer);
    while (*answer > 17 || !(*result) || *answer < 0)
    {
      puts("Please enter valid input\n");
      if (!(*result))
      {
        char removeBuffer[100];
        scanf("%s", removeBuffer);
      }
      if (*answer < 18)
      {
        puts("Warning: Age is too high for children");
      }
      printf("\nEnter age: ");
      *result = scanf("%d", answer);
    }

    (*datas)[i].age = *answer;
  }
}

void reserveTicket(FILE *file, Information (*arrayCategories)[], int *total)
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
  while (answer > *total || answer < 0 || !result)
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

  if (answer == *total)
    return;

  char tempCountry[100];
  int totalMembers = 0;
  database reservedDATA[20];
  //Store the current country
  strcpy(tempCountry, (*arrayCategories)[answer - 1].country);

  //propmt user (Quantity of adult members (18+ years old))
  propmtUserAdultMembers(&result, &answer, &totalMembers);
  //Prompt user (adult member's age)
  propmtUserAdultAges(&result, &answer, &totalMembers, &reservedDATA);
  //propmt user (Quantity of children members (17- years old))
  propmtUserChildren(&result, &answer, &totalMembers);
  //Prompt user (children member's age)
  propmtUserChildrenAges(&result, &answer, &totalMembers, &reservedDATA);
}