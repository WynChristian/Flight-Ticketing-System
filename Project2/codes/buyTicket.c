

void updateSalesReport(Documents *files, char *reportFilePath, Report (*arrayReports)[], int totalCountries)
{
  files->salesReport = fopen(reportFilePath, "w+");
  fprintf(files->salesReport, "%-15s %-10s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Trave Tax");
  for (int i = 0; i < totalCountries; i++)
  {
    fprintf(files->salesReport, "%-14s %-9d %-10.2f %.2f\n", (*arrayReports)[i].country, (*arrayReports)[i].quantity, (*arrayReports)[i].amount, (*arrayReports)[i].tax);
  }
  fclose(files->salesReport);
}

int checkCountry(char *country, Report (*arrayReports)[], int *totalCountries)
{
  int result = 0;
  for (int i = 0; i < *totalCountries; i++)
  {
    if (!strcmp(country, (*arrayReports)[i].country))
    {
      return result;
    }
    result++;
  }
  *totalCountries += 1;
  return 0;
}

// --------------------- For Non - Reserved Ticket -------------------------

void promptAdult(int *numMembers, int maxTransaction)
{
  int result = 0;
  int answer = 0;
  printf("\nHow many adult/s(18+ y.o)(max: %d): ", maxTransaction);
  result = scanf(" %d", &answer);
  while (!result || answer < 0 || answer > maxTransaction)
  {
    while (answer > maxTransaction)
    {
      printf("\nSorry, we can transact for maximum of %d members only per transaction", maxTransaction);
      printf("\nHow many adults(max: %d): ", maxTransaction);
      result = scanf(" %d", &answer);
      break;
    }
    puts("Please enter valid input\n");
    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
    printf("\nHow many adults(max: %d): ", maxTransaction);
    result = scanf(" %d", &answer);
  }
  *numMembers += answer;
  return;
}

void promptAdultAges(Transactions (*arrayTransaction)[], int *numMembers, Information *category)
{
  int age = 18;
  int result;
  for (int i = 0; i < *numMembers; i++)
  {
    printf("\nEnter age(18+): ");
    result = scanf(" %d", &age);
    while (age > 160 || age < 18 || !result)
    {
      if (age < 18)
      {
        printf("\nAge is too low for adult age(18+)");
      }

      puts("\nPlease enter valid input\n");
      printf("\nEnter age(18+): ");
      result = scanf(" %d", &age);

      if (!result)
      {
        char removeBuffer[100];
        scanf(" %s", removeBuffer);
      }
    }

    (*arrayTransaction)[i].age = age;
    (*arrayTransaction)[i].price = calculateDiscount(age, category->price);
  }
}

void promptChildrenAges(Transactions (*arrayTransaction)[], Information *category, int *total, int index)
{
  int maxAge = 17;
  int age = 0;
  int result;
  for (int i = index; i < *total; i++)
  {
    printf("\nEnter age(%d or lower): ", maxAge);
    result = scanf(" %d", &age);
    while (age < 0 || age > 18 || !result)
    {
      if (age > 17)
      {
        printf("\nAge is too high(Must be %d or lower)", maxAge);
      }
      puts("\nPlease enter valid input\n");
      printf("\nEnter age(%d or lower): ", maxAge);
      result = scanf(" %d", &age);

      if (!result)
      {
        char removeBuffer[100];
        scanf(" %s", removeBuffer);
      }
    }

    (*arrayTransaction)[i].age = age;
    (*arrayTransaction)[i].price = calculateDiscount(age, category->price);
  }
}

void promptChildren(Transactions (*arrayTransaction)[], Information *category, int *numMembers, int maxTransaction)
{
  if (*numMembers == maxTransaction)
  {
    return;
  }
  printf("\ncurrent *numMembers (propmtChildren) = %d", *numMembers);
  int result;
  int answer = 0;
  printf("\nHow many children(17-)(max: %d, current %d): ", maxTransaction, *numMembers);
  result = scanf(" %d", &answer);

  while (!result || answer < 0 || answer > maxTransaction)
  {
    while (answer > maxTransaction - *numMembers)
    {
      printf("\nSorry, we can transact for maximum of %d members only per transaction", maxTransaction);
      printf("\nNo. of available: %d", maxTransaction - *numMembers);
      printf("\nHow many children(17-): ");
      result = scanf(" %d", &answer);
      break;
    }
    puts("Please enter valid input\n");
    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
    printf("\nHow many children(17-): ");
    result = scanf(" %d", &answer);
  }
  int index = *numMembers;
  *numMembers += answer;

  printf("\n\t TESTING totalMembers: %d", *numMembers);
  promptChildrenAges(arrayTransaction, category, numMembers, index);
  return;
}

void promptUserTransaction(Information *category, Transactions (*arrayTransaction)[], int maxTransaction, int *totalMembers)
{

  promptAdult(totalMembers, maxTransaction);
  promptAdultAges(arrayTransaction, totalMembers, category);
  promptChildren(arrayTransaction, category, totalMembers, maxTransaction);
}

int proceedTransaction(bool checkBuffer)
{
  if (checkBuffer)
  {
    char buffer[100];
    scanf(" %s", buffer);
  }
  char choice;
  int result;
  printf("\nProceed to buy the transaction[y/n]? ");
  result = scanf(" %c", &choice);

  while (!result)
  {
    printf("\nPlease enter valid input ");
    char buffer[100];
    scanf("%s", buffer);

    printf("\nProceed to buy the transaction[y/n]? ");
    result = scanf("%d", &choice);
  }
  if (choice == 'y' || choice == 'Y')
    return 1;
  else if (choice == 'n' || choice == 'N')
    return 0;
  else
  {
    printf("\nPlease enter valid input ");
    return proceedTransaction(true);
  }
}

void appendTransactionNonReserved(Documents *files, Transactions (*transactionsList)[], Information *category, int *totalMember, char *filePath)
{
  files->appendTransaction = fopen(filePath, "a");
  for (int i = 0; i < *totalMember; i++)
  {
    float price = (*transactionsList)[i].price;
    float tax = price * category->tax;
    fprintf(files->appendTransaction, "\n%- 12s %-7d %-15.2f %.2f", category->country, (*transactionsList)[i].age, (*transactionsList)[i].price, tax);
  }
  fclose(files->appendTransaction);
}

void updateSalesReportNonReserved(Documents *files, Report (*arrayReports)[], Transactions (*transactionsList)[], Information *category, int index, int *totalMembers, int *totalCountries, char *reportFilePath)
{
  float totalPrice = 0;
  float tax = category->tax;
  int total = *totalMembers;
  for (int i = 0; i < total; i++)
  {
    (*arrayReports)[index].amount += (*transactionsList)[i].price;
    totalPrice += (*transactionsList)[i].price;
  }
  (*arrayReports)[index].tax += (totalPrice * tax);

  updateSalesReport(files, reportFilePath, arrayReports, *totalCountries);
}

void storeTransactionData(Documents *files, Report (*arrayReport)[], Information *category, Transactions (*transactionsList)[], int *totalMember, int *totalCountries, char *transactionFilePath, char *reportFilePath)
{
  int index;
  int output;
  if ((output = checkCountry(category->country, arrayReport, totalCountries)))
  {
    index = output;
    (*arrayReport)[index].quantity += *totalMember;
  }
  else
  {
    index = *totalCountries - 1;
    strcpy((*arrayReport)[index].country, category->country);
    (*arrayReport)[index].quantity = *totalMember;
    (*arrayReport)[index].amount = 0;
    (*arrayReport)[index].tax = 0;
  }
  appendTransactionNonReserved(files, transactionsList, category, totalMember, transactionFilePath);
  updateSalesReportNonReserved(files, arrayReport, transactionsList, category, index, totalMember, totalCountries, reportFilePath);
}

void displayPrice(Transactions (*transactionList)[], int totalMember)
{
  float total = 0;
  for (int i = 0; i < totalMember; i++)
  {
    total += (*transactionList)[i].price;
  }
  printf("\n\nTotal Ticket Price: %.2f", total);
  return;
}

void buyNonReservedTicket(Documents *files, Information (*arrayCategories)[], int *totalCountries, Report (*arrayReport)[], char *transactionFilePath, char *reportFilePath, int *total, int maxTransaction)
{
  //Display destinations-
  puts("FLIGHT DESTINATION\n");
  for (int i = 0; i < *total; i++)
  {
    printf("%d. %-19s %d.00\n", (i + 1), (*arrayCategories)[i].country, (*arrayCategories)[i].price);
  }
  printf("%d. %s\n", *total + 1, "Return to MAIN");

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

  Information tempCategory = (*arrayCategories)[answer - 1];
  Transactions transactionList[100];
  int totalMember = 0;

  promptUserTransaction(&tempCategory, &transactionList, maxTransaction, &totalMember);
  displayPrice(&transactionList, totalMember);
  if (proceedTransaction(false))
  {
    //storedata -> transaction, sales report
    storeTransactionData(files, arrayReport, &tempCategory, &transactionList, &totalMember, totalCountries, transactionFilePath, reportFilePath);
  }
}

// --------------------- For Reserved Ticket -------------------------
void appendTransactionReserved(Documents *files, char *filePath, CurrentData *category, CurrentOutput *currentOutput)
{
  float price = currentOutput->price;
  float tax = price * category->tax * 0.01;
  files->appendTransaction = fopen(filePath, "a");
  fprintf(files->appendTransaction, "\n%-11s %-7d %-15.2f %.2f", category->country, currentOutput->age, currentOutput->price, tax);
  fclose(files->appendTransaction);
}

void updateSalesReportReserved(Report (*arrayReports)[], int index, int tax, CurrentOutput *currentoutput, int *totalCountries, char *reportFilePath, Documents *files)
{
  float finalTax = currentoutput->price * (tax * 0.01);

  (*arrayReports)[index].amount += currentoutput->price;
  (*arrayReports)[index].tax += finalTax;

  updateSalesReport(files, reportFilePath, arrayReports, *totalCountries);
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

void storeCodeData(Documents *files, char *filePath, int *totalCountries, Report (*arrayReports)[], char *transactionFilePath, char *reportFilePath)
{
  CurrentData current;
  CurrentOutput currentoutput;

  files->reservedData = fopen(filePath, "r");
  int result = fscanf(files->reservedData, "%s %d %d", current.country, &current.tax, &current.total);
  if (result != 3)
  {
    fclose(files->reservedData);
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
    index = *totalCountries - 1;
    strcpy((*arrayReports)[index].country, current.country);
    (*arrayReports)[index].quantity = current.total;
    (*arrayReports)[index].amount = 0;
    (*arrayReports)[index].tax = 0;
  }
  while (scanData(files->reservedData, &currentoutput))
  {
    appendTransactionReserved(files, transactionFilePath, &current, &currentoutput);
    updateSalesReportReserved(arrayReports, index, current.tax, &currentoutput, totalCountries, reportFilePath, files);
  }
  remove(filePath);
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
    scanf("%s", buffer);

    printf("\nProceed to but Ticket[y/n]? ");
    result = scanf("%d", &choice);
  }
  if (choice == 'y' || choice == 'Y')
    return 1;
  else if (choice == 'n' || choice == 'N')
    return 0;
  else
  {
    printf("\nPlease enter valid input ");
    return proceedPayment(true);
  }
}

void buyReservedTicket(Documents *files, Information (*arrayCategories)[], char *dataRootFile, int *totalCountries, Report (*arrayReport)[], char *transactionFilePath, char *reportFilePath)
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
    return buyReservedTicket(files, arrayCategories, dataRootFile, totalCountries, arrayReport, transactionFilePath, reportFilePath);
  }

  if (proceedPayment(false))
  {
    storeCodeData(files, codeFilePath, totalCountries, arrayReport, transactionFilePath, reportFilePath);
  }
  puts("\nPress any KEY to RETURN");
  char some = getch();
}

// ----------------------------- Buy Ticket MENU --------------------------
void buyTicket(Documents *files, Information (*arrayCategories)[], Report (*arrayReports)[], unsigned int *total, char *dataRootFile, int *totalCountries, char *transactionFilePath, char *reportFilePath, int maxTransaction)
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
    buyReservedTicket(files, arrayCategories, dataRootFile, totalCountries, arrayReports, transactionFilePath, reportFilePath);
    buyTicket(files, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
  case '2':
    buyNonReservedTicket(files, arrayCategories, totalCountries, arrayReports, transactionFilePath, reportFilePath, total, maxTransaction);
    buyTicket(files, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
  case '3':
    return;
  default:
    puts("Error, invalid input. try again");
    buyTicket(files, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
  }
}