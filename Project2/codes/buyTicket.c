typedef struct currentData CurrentData;
typedef struct currentOutput CurrentOutput;

struct currentData
{
  char country[100];
  int tax;
  int total;
};

struct currentOutput
{
  int age;
  float price;
};

void appendTransactionReserved(FILE *transaction, char *filePath, char *currentCountry, CurrentOutput *currentOutput)
{
  transaction = fopen(filePath, "a");
  fprintf(transaction, "\n%- 12s %- 7d %.2f", currentCountry, currentOutput->age, currentOutput->price);
  fclose(transaction);
}

void updateSalesReport(Report (*arrayReports)[], int index, int tax, CurrentOutput *currentoutput)
{
  float finalTax = currentoutput->price * (tax * 0.01);

  (*arrayReports)[index].amount += currentoutput->price;
  (*arrayReports)[index].tax += finalTax;

  printf("\nTesting  (*arrayReports)[%d].amount = %.2f", index, (*arrayReports)[index].amount);
  printf("\nTesting  (*arrayReports)[%d].tax = %.2f", index, (*arrayReports)[index].tax);
}

int scanData(FILE *data, CurrentOutput *currentdata)
{
  int result;

  while ((result = fscanf(data, "%d %f", &currentdata->age, &currentdata->price)) == 1)
  {
    return scanData(data, currentdata);
  }

  if (result == EOF)
  {
    fclose(data);
    return 0;
  }
  else if (result != 2)
  {
    printf("\n Error reading data\n");
  }
  else
  {
    return 1;
  }
}

int checkCountry(char *country, Report (*arrayReports)[], int *totalCountries)
{
  int result = 0;
  for (int i = 0; i < *totalCountries; i++)
  {
    if (!strcmp(country, (*arrayReports)[i].country))
    {
      printf("\nTESTING country comparing is TRUEEEE");
      return result;
    }
    result++;
  }
  return 0;
}

void storeCodeData(FILE *fileTransaction, char *filePath, int *totalCountries, Report (*arrayReports)[], char *transactionFilePath)
{
  CurrentData current;
  CurrentOutput currentoutput;
  FILE *data = fopen(filePath, "r");
  int result = fscanf(data, "%s %d %d", current.country, &current.tax, &current.total);
  if (result != 3)
  {
    fclose(data);
    printf("\nProblem with reading the data");
    return;
  }

  int index;
  int output;
  if ((output = checkCountry(current.country, arrayReports, totalCountries)))
  {
    index = output;
    (*arrayReports)[index].quantity += current.total;
  }
  else
  {
    index = *totalCountries;
    strcpy((*arrayReports)[index].country, current.country);
    (*arrayReports)[index].quantity = current.total;
    (*arrayReports)[index].amount = 0;
    (*arrayReports)[index].tax = 0;
  }
  while (scanData(data, &currentoutput))
  {
    appendTransactionReserved(fileTransaction, transactionFilePath, current.country, &currentoutput);
    updateSalesReport(arrayReports, index, current.tax, &currentoutput);
  }
}

int proceedPayment(bool checkBuffer)
{
  if (checkBuffer)
  {
    char buffer[100];
    scanf(" %s", buffer);
  }
  char choice;
  int result;
  printf("\nProceed to but Ticket[y/n]? ");
  result = scanf(" %c", &choice);
  while (!result)
  {
    printf("\nPlease enter valid input ");
    char buffer[100];
    scanf(" %s", buffer);

    printf("\nProceed to but Ticket[y/n]? ");
    result = scanf("%d", &choice);
  }
  if (choice == 'y' || choice == 'Y')
    return 1;
  else if (choice == 'n', choice == 'N')
    return 0;
  else
  {
    printf("\nPlease enter valid input ");
    return proceedPayment(true);
  }
}

void buyReservedTicket(FILE *fileTransaction, Information (*arrayCategories)[], char *dataRootFile, int *totalCountries, Report (*arrayReport)[], char *transactionFilePath)
{
  int code;
  int result;
  printf("\nEnter reservation code: ");
  result = scanf("%d", &code);
  while (!result)
  {
    printf("\nPlease enter valid code");
    char buffer[100];
    scanf("%s", buffer);

    printf("\nEnter reservation code: ");
    result = scanf("%d", &code);
  }

  char codeFilePath[100];
  strcpy(codeFilePath, dataRootFile);
  generateFilePath(codeFilePath, code);
  if (!checkFilePath(codeFilePath))
  {
    printf("\nThe Code (%d) doesn't exist", code);
    return buyReservedTicket(fileTransaction, arrayCategories, dataRootFile, totalCountries, arrayReport, transactionFilePath);
  }

  if (proceedPayment(false))
  {
    storeCodeData(fileTransaction, codeFilePath, totalCountries, arrayReport, transactionFilePath);
  }
}

void buyTicket(FILE *fileTransaction, Information (*arrayCategories)[], Report (*arrayReports)[], int total, char *dataRootFile, int *totalCountries, char *transactionFilePath)
{

  int result;
  char menu[4][100] = {
      "Reserved",
      "No reservation",
      "Return to MAIN"};

  printf("\nBUY TICKET\n");
  for (int i = 0; i < 3; i++)
    printf("\n%d.] %s", (i + 1), menu[i]);

  char choice;
  printf("\n\nEnter your Choice: ");
  result = scanf(" %c", &choice);

  switch (choice)
  {
  case '1':
    buyReservedTicket(fileTransaction, arrayCategories, dataRootFile, totalCountries, arrayReports, transactionFilePath);
    buyTicket(fileTransaction, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath);
  case '2':
    printf("\nYou picked 2");
    buyTicket(fileTransaction, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath);
  case '3':
    printf("\nYou picked 3");
    buyTicket(fileTransaction, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath);
    break;
  default:
    puts("Error, invalid input. try again");
    buyTicket(fileTransaction, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath);
  }
}