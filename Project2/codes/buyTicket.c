/* 
  This is where `Buy Ticket` category located
  Its purpose is to track the trasactions and sales report

  Here is the tree list of the flow of the functions 
  (Take note that I didn't list the functions from other file):
    * buyTicket()
      * buyReservedTicket()
        * proceedPayment()
        * storeCodeData()
          * checkCountry()
          * scanData()
          * appendTransactionReserved()
          * updateSalesReportReserved()
            * updateSalesReport()
      * buyNonReservedTicket()
        * promptUserTransaction()
          * promptAdult()
          * promptAdultAges()
          * promptChildren()
            * promptChildrenAges()
        * displayPrice()
        * proceedTransaction()
        * storeTransactionData()
          * checkCountry()
          * appendTransactionNonReserved()
          * updateSalesReportNonReserved()
            * updateSalesReport()
 */

// It updates the `reportFile` text file to track the information
//   of the current executing program
void updateSalesReport(Documents *files, char *reportFilePath, Report (*arrayReports)[], int totalCountries)
{
  // Overwrite the `reportFile` text file with an updated information
  //    which is in the `arrayReports` array
  files->salesReport = fopen(reportFilePath, "w+");
  fprintf(files->salesReport, "%-15s %-10s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Trave Tax");

  // write all the updated informations
  for (int i = 0; i < totalCountries; i++)
  {
    fprintf(files->salesReport, "%-14s %-9d %-10.2f %.2f\n",
            (*arrayReports)[i].country, (*arrayReports)[i].quantity,
            (*arrayReports)[i].amount, (*arrayReports)[i].tax);
  } // for Loop

  fclose(files->salesReport);
  return;
} // updateSalesReport Function

// It checks if the selected country is already existing
//    in the `arrayReports` array
// It returns either 1 or 0; signifying "true" or "false"
int checkCountry(char *country, Report (*arrayReports)[], int *totalCountries)
{
  int result = 0;

  // A loop to access the arrays indeces
  for (int i = 0; i < *totalCountries; i++)
  {
    if (!strcmp(country, (*arrayReports)[i].country))
    {
      return result;
    }
    result++;
  } // for Loop

  // If it doesn't exist,
  //   then increment the current total no. of countries
  *totalCountries += 1;
  return 0;
} // checkCountry Function

// --------------------- For Non - Reserved Ticket -------------------------

// It prompts the user about no. of adults members
//   while tracking the no. of members per transaction
void promptAdult(int *numMembers, int maxTransaction)
{
  int result = 0;
  int answer = 0;

  // Prompt the user about the no. of adults members
  printf("\nHow many adult/s(18+ y.o)(max: %d): ", maxTransaction);
  result = scanf(" %d", &answer);

  // Check the input data validity
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
  } // while Loop

  // Increment the `numMembers` with the current answer
  *numMembers += answer;
  return;
} // promptAdult Function

// It prompts the user about the age of each adult members
//   while tracking their data for transaction
void promptAdultAges(Transactions (*arrayTransaction)[],
                     int *numMembers, Information *category)
{
  int age = 18;
  int result;

  // A loop to ask the user about the age of each members
  for (int i = 0; i < *numMembers; i++)
  {
    printf("\nEnter age(18+): ");
    result = scanf(" %d", &age);

    // Check the input data validity
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
    } // while Loop

    // Store the current adult member's age in the
    //   `arrayTransaction` array with respect to their indeces
    (*arrayTransaction)[i].age = age;
    (*arrayTransaction)[i].price = calculateDiscount(age, category->price);

  } // for Loop

  return;
} // promptAdultAges Function

// It prompts the user about the age of each children members
void promptChildrenAges(Transactions (*arrayTransaction)[],
                        Information *category, int *total, int index)
{
  int maxAge = 17;
  int age = 0;
  int result;

  // A loop to prompt the user about the current child's age
  for (int i = index; i < *total; i++)
  {
    printf("\nEnter age(%d or lower): ", maxAge);
    result = scanf(" %d", &age);

    // Check the input data validity
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
    } // while Loop

    // Store the current age and price in the `arrayTransaction` array
    //   with respect to their indeces
    (*arrayTransaction)[i].age = age;
    (*arrayTransaction)[i].price = calculateDiscount(age, category->price);
  } // for Loop

  return;
} // promptChildrenAges Function

// It prompts the user about the no. of childrens
void promptChildren(Transactions (*arrayTransaction)[],
                    Information *category, int *numMembers,
                    int maxTransaction)
{
  // If the no. of members reach the maximum no. of members per transaction,
  //   then return to the `buyTicket` function
  if (*numMembers == maxTransaction)
  {
    return;
  }

  // Display the current no. of members
  printf("\ncurrent *numMembers (propmtChildren) = %d", *numMembers);
  int result;
  int answer = 0;

  // Prompt the user about the no. of children
  printf("\nHow many children(17-)(max: %d, current %d): ", maxTransaction, *numMembers);
  result = scanf(" %d", &answer);

  // Check the input data validity
  while (!result || answer < 0 || answer > maxTransaction)
  {
    while (answer > maxTransaction - *numMembers)
    {
      printf("\nSorry, we can transact for maximum of %d members only per transaction", maxTransaction);
      printf("\nNo. of available: %d", maxTransaction - *numMembers);
      printf("\nHow many children(17-): ");
      result = scanf(" %d", &answer);
      break;
    } // while Loop

    puts("Please enter valid input\n");
    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }

    printf("\nHow many children(17-): ");
    result = scanf(" %d", &answer);
  } // while Loop

  int index = *numMembers;
  *numMembers += answer; // Increment the current no. of members

  // Prompt the user for each children's age
  promptChildrenAges(arrayTransaction, category, numMembers, index);
  return;
} // promptChildren Function

// It invokes(calls) the three(3) function, consecutively for transaction
void promptUserTransaction(Information *category,
                           Transactions (*arrayTransaction)[],
                           int maxTransaction, int *totalMembers)
{
  // For adults
  promptAdult(totalMembers, maxTransaction);
  promptAdultAges(arrayTransaction, totalMembers, category);

  //For childrens
  promptChildren(arrayTransaction, category, totalMembers, maxTransaction);

  return;
} // promptUserTransaction Function

// It prompts the user to proceed the transaction
// It returns either 1 / 0; signifying "true" or "false"
int proceedTransaction(bool checkBuffer)
{
  // checks if the buffer has some value
  if (checkBuffer)
  {
    char buffer[100];
    scanf(" %s", buffer);
  }

  char choice;
  int result;

  // Prompt the user to proceed the transaction
  printf("\nProceed to buy the transaction[y/n]? ");
  result = scanf(" %c", &choice);

  // Check the input data validity
  while (!result)
  {
    printf("\nPlease enter valid input ");
    char buffer[100];
    scanf("%s", buffer);

    printf("\nProceed to buy the transaction[y/n]? ");
    result = scanf("%d", &choice);
  }

  // if yes, return 1 (true)
  if (choice == 'y' || choice == 'Y')
    return 1;
  // if no, return 0 (false)
  else if (choice == 'n' || choice == 'N')
    return 0;
  else
  {
    printf("\nPlease enter valid input ");
    return proceedTransaction(true);
  }
}

// It appends the current transactions in the `filePath` text file
void appendTransactionNonReserved(Documents *files,
                                  Transactions (*transactionsList)[],
                                  Information *category,
                                  int *totalMember, char *filePath)
{
  files->appendTransaction = fopen(filePath, "a");

  // Loop through each `transactionList` array indeces to get their
  //   information of each transactions
  for (int i = 0; i < *totalMember; i++)
  {
    float price = (*transactionsList)[i].price;
    float tax = price * category->tax;
    fprintf(files->appendTransaction, "\n%- 12s %-7d %-15.2f %.2f",
            category->country, (*transactionsList)[i].age,
            (*transactionsList)[i].price, tax);
  } // for Loop

  fclose(files->appendTransaction);
  return;
} // appendTransactionNonReserved Function

// It updates the index of `arrayReports` to store the informations from `transacitonList` array
void updateSalesReportNonReserved(Documents *files, Report (*arrayReports)[],
                                  Transactions (*transactionsList)[],
                                  Information *category,
                                  int index, int *totalMembers,
                                  int *totalCountries, char *reportFilePath)
{
  float totalPrice = 0;
  float tax = category->tax;
  int total = *totalMembers;

  // Loop through the `transactionList` and add it to the selected category
  for (int i = 0; i < total; i++)
  {
    (*arrayReports)[index].amount += (*transactionsList)[i].price;
    totalPrice += (*transactionsList)[i].price;
  }
  (*arrayReports)[index].tax += (totalPrice * tax);

  // Invoke the `updateSalesReport` function to overwrite the new information
  updateSalesReport(files, reportFilePath, arrayReports, *totalCountries);
  return;
} // updateSalesReportNonReserved Function

// It stores the `transactionList` array's data into `arrayReport` array to track informations
void storeTransactionData(Documents *files, Report (*arrayReport)[],
                          Information *category, Transactions (*transactionsList)[],
                          int *totalMember, int *totalCountries,
                          char *transactionFilePath, char *reportFilePath)
{
  int index;
  int output;

  // check if the selected destination exists in the `arrayReport` array
  if ((output = checkCountry(category->country, arrayReport, totalCountries)))
  {
    // if yes, then increment the quantity of the current category
    //   with the total no. of members
    index = output;
    (*arrayReport)[index].quantity += *totalMember;
  }
  else
  {
    // if it does not yet exist, then create new (push) struct in the `arrayReport` array
    //    and initialize the values for each field (`variables` inside of `struct`)
    index = *totalCountries - 1;
    strcpy((*arrayReport)[index].country, category->country);
    (*arrayReport)[index].quantity = *totalMember;
    (*arrayReport)[index].amount = 0;
    (*arrayReport)[index].tax = 0;
  }

  // Add the transactions in the `transactionFilePath` text file
  appendTransactionNonReserved(files, transactionsList,
                               category, totalMember,
                               transactionFilePath);

  // Update the `arrayReport` array and overwrite the `reportFilePath` text file
  //   to track changes in the current program
  updateSalesReportNonReserved(files, arrayReport, transactionsList,
                               category, index, totalMember,
                               totalCountries, reportFilePath);
}

// It display the total price of current non reserved transaction
void displayPrice(Transactions (*transactionList)[], int totalMember)
{
  float total = 0;

  // Iterate through the `transactionList` array to track the total amount
  for (int i = 0; i < totalMember; i++)
  {
    total += (*transactionList)[i].price;
  }

  // then, display the total amount of current transactions
  printf("\n\nTotal Ticket Price: %.2f", total);
  return;
} // displayPrice Function

// This is the "No Reservation" category from "Buy Ticket" menu
// It prompt the user which destination to choose and tracks the information
//    about the non-reservation transaction
void buyNonReservedTicket(Documents *files, Information (*arrayCategories)[],
                          int *totalCountries, Report (*arrayReport)[],
                          char *transactionFilePath, char *reportFilePath,
                          int *total, int maxTransaction)
{
  // Display the current available destinations
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

  // Check the input data validity
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
  } // while Loop

  if (answer == (*total + 1))
    return;

  // structs and variables to track the current non-reservation transaction
  Information tempCategory = (*arrayCategories)[answer - 1];
  Transactions transactionList[100];
  int totalMember = 0;

  // Prompts the user about the transaction
  promptUserTransaction(&tempCategory, &transactionList, maxTransaction, &totalMember);

  // Display the total amount of current transaction
  displayPrice(&transactionList, totalMember);

  // Prompt the user to proceed
  if (proceedTransaction(false))
  {
    // if yes, then update the `transactionFilePath` and `reportFilePath` text files,
    //   and the `arrayReport` array to track the informations
    storeTransactionData(files, arrayReport, &tempCategory,
                         &transactionList, &totalMember,
                         totalCountries, transactionFilePath,
                         reportFilePath);
  }

  return;
} // buyNonReservedTicket Function

// --------------------- For Reserved Ticket -------------------------

// It appends the `filePath` text file with a data from `currentOutput` and `category`
void appendTransactionReserved(Documents *files, char *filePath,
                               CurrentData *category,
                               CurrentOutput *currentOutput)
{
  float price = currentOutput->price;
  float tax = price * category->tax * 0.01;
  files->appendTransaction = fopen(filePath, "a");

  // Append the current reserved transaction in the `filePath` text file
  fprintf(files->appendTransaction, "\n%-11s %-7d %-15.2f %.2f",
          category->country, currentOutput->age, currentOutput->price, tax);
  fclose(files->appendTransaction);

  return;
} // appendTransactionReserved Function

// It updates the `arrayReport` array to track the data of the current transaction
void updateSalesReportReserved(Report (*arrayReports)[], int index,
                               int tax, CurrentOutput *currentoutput,
                               int *totalCountries, char *reportFilePath,
                               Documents *files)
{
  float finalTax = currentoutput->price * (tax * 0.01);

  // Increment the `index` of `arrayReports` array's amount and tax
  //    to track the total amount of selected destination
  (*arrayReports)[index].amount += currentoutput->price;
  (*arrayReports)[index].tax += finalTax;

  // Invoke the `updateSalesReport` function to overwrite the `reportFilePath` text file
  //   with an updated `arrayReports` infomation
  updateSalesReport(files, reportFilePath, arrayReports, *totalCountries);
}

// It reads the data from `data` file, stores the current data
// It returns either 1, 0, or error
int scanData(FILE *data, CurrentOutput *currentdata)
{
  int result;

  // Get the result of `fscanf` to check the data validity
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
    return 0;
  }
  else
  {
    return 1;
  }
} // scanData Function

// It stores the reserved transactions data from `filePath` text file into the `arrayReports`,
//    then update the `transactionFilePath` text file, and the `reportFilePath` text file
void storeCodeData(Documents *files, char *filePath,
                   int *totalCountries, Report (*arrayReports)[],
                   char *transactionFilePath, char *reportFilePath)
{
  // To track current datas
  CurrentData current;
  CurrentOutput currentoutput;

  // Get the three(3) data (selected country, tax, no. of transaction) and store it in `current` struct
  files->reservedData = fopen(filePath, "r");
  int result = fscanf(files->reservedData, "%s %d %d",
                      current.country, &current.tax, &current.total);

  // check the text file data validity
  if (result != 3)
  {
    fclose(files->reservedData);
    printf("\nProblem with reading the data");
    return;
  }

  int index;
  int output;

  // Check the selected country if it exists in `arrayReport` array
  if ((output = checkCountry(current.country, arrayReports, totalCountries)))
  {
    // if it exists already, increment the quantity with the no. of transaction in the file
    index = output;
    (*arrayReports)[index].quantity += current.total;
  }
  else
  {
    // if it doesn't exist, initialize the `index` of `arrayReports` array
    index = *totalCountries - 1;
    strcpy((*arrayReports)[index].country, current.country);
    (*arrayReports)[index].quantity = current.total;
    (*arrayReports)[index].amount = 0;
    (*arrayReports)[index].tax = 0;
  }

  // Scan (line by line) the data of `files->reservedData` text file
  //   and store the current data in the `currentouput`
  while (scanData(files->reservedData, &currentoutput))
  {
    // Invoke `appendTransactionReserved` function to append the current data
    appendTransactionReserved(files, transactionFilePath,
                              &current, &currentoutput);

    // Invoke `updateSalesReportReserved` function to update the `arrayReports`
    //   and overwrite the `reportFilePath` text file with the current data
    updateSalesReportReserved(arrayReports, index, current.tax,
                              &currentoutput, totalCountries,
                              reportFilePath, files);
  }

  // after storing the data from "reserved transaction," Delete the `filePath` text file
  remove(filePath);

  return;
} // storeCodeData Function

// It prompts the user to proceed the payment of reserved ticket
int proceedPayment(bool checkBuffer)
{
  // Check if the buffer has some value
  if (checkBuffer)
  {
    char buffer[100];
    scanf(" %s", buffer);
  }
  char choice;
  int result;
  printf("\nProceed to buy Ticket[y/n]? ");
  result = scanf(" %c", &choice);

  while (!result)
  {
    printf("\nPlease enter valid input ");
    char buffer[100];
    scanf("%s", buffer);

    printf("\nProceed to buy Ticket[y/n]? ");
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

// This is the "Reserved" category from "Buy Ticket" menu
// It prompt the user to enter the reservation code,
//   analyze the code if it exist, then ask the user to
//   proceed to buy the reserved ticket
void buyReservedTicket(Documents *files,
                       Information (*arrayCategories)[],
                       char *dataRootFile, int *totalCountries,
                       Report (*arrayReport)[],
                       char *transactionFilePath,
                       char *reportFilePath)
{
  int code;
  int result;

  // Prompt the user to enter the code
  printf("\nEnter reservation code: ");
  result = scanf("%d", &code);

  // Check the input data validity
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

  // generate the file path with the current `code`
  generateFilePath(codeFilePath, code);

  // Check if the current generated file doesn't exists
  if (!checkFilePath(codeFilePath))
  {
    printf("\nThe Code (%d) doesn't exist", code);
    return buyReservedTicket(files, arrayCategories,
                             dataRootFile, totalCountries,
                             arrayReport, transactionFilePath,
                             reportFilePath);
  }

  // Prompt the user to proceed the payment of reserved ticket
  if (proceedPayment(false))
  {
    // If proceed,
    //    then store the data from `codeFilePath` text file,
    //    then update the `arrayReport` array
    //    then append the `transactionFilePath` text file
    //    and then overwrite the `reportFilePath` text file to track changes
    storeCodeData(files, codeFilePath, totalCountries, arrayReport, transactionFilePath, reportFilePath);
  }

  // Return to "Buy Ticket" menu
  puts("\nPress any KEY to RETURN");
  char some = getch();
  return;
} //

// ----------------------------- Buy Ticket MENU --------------------------

// This is the main function in this file
// It prompts the user to choose which kind of transaction
//    should be used, either "Reserved" or "No reservation"
// It uses `arrayReports` to track the transaction informations
void buyTicket(Documents *files, Information (*arrayCategories)[],
               Report (*arrayReports)[], unsigned int *total,
               char *dataRootFile, int *totalCountries,
               char *transactionFilePath, char *reportFilePath,
               int maxTransaction)
{
  system("cls");

  int result;
  char menu[4][100] = {
      "Reserved",
      "No reservation",
      "Return to MAIN"};

  // Displays the "Buy Ticket" Menu
  printf("\nBUY TICKET\n");
  for (int i = 0; i < 3; i++)
    printf("\n%d.] %s", (i + 1), menu[i]);

  char choice;
  // Prompt the user to choose which transaction
  printf("\n\nEnter your Choice: ");
  result = scanf(" %c", &choice);

  // Analyze the `choice`
  switch (choice)
  {
  case '1':
    // if 1, then invoke `buyReservedTicket` function
    buyReservedTicket(files, arrayCategories,
                      dataRootFile, totalCountries,
                      arrayReports, transactionFilePath,
                      reportFilePath);

    buyTicket(files, arrayCategories, arrayReports,
              total, dataRootFile, totalCountries,
              transactionFilePath, reportFilePath, maxTransaction);
  case '2':
    // if 2, then invoke `buyNonReservedTicket` function
    buyNonReservedTicket(files, arrayCategories,
                         totalCountries, arrayReports,
                         transactionFilePath, reportFilePath,
                         total, maxTransaction);

    buyTicket(files, arrayCategories, arrayReports,
              total, dataRootFile, totalCountries,
              transactionFilePath, reportFilePath, maxTransaction);
  case '3':
    // if '3', then return to MAIN MENU
    return;
  default:
    puts("Error, invalid input. try again");
    buyTicket(files, arrayCategories, arrayReports,
              total, dataRootFile, totalCountries,
              transactionFilePath, reportFilePath, maxTransaction);
  } // switch-case conditions
} // buyTicket Function