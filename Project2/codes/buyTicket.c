/*
  This is where `Buy Ticket` category located
  Its purpose is to track the transactions and sales report

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
void updateSalesReport(Report (*arrayReports)[], int totalCountries)
{
  // Overwrite the `reportFile` text file with an updated information
  //    which is in the `arrayReports` array
  FILE *file = fopen(reportFile, "w+");
  fprintf(file, "%-15s %-10s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Trave Tax");

  // write all the updated informations
  for (int i = 0; i < totalCountries; i++)
  {
    fprintf(file, "%-14s %-9d %-10.2f %.2f\n",
            (*arrayReports)[i].country, (*arrayReports)[i].quantity,
            (*arrayReports)[i].amount, (*arrayReports)[i].tax);
  } // for Loop

  fclose(file);
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
void promptAdult(int *numMembers)
{
  int result = 0;
  int answer = 0;

  // Prompt the user about the no. of adults members
  printf("\n\t\tHow many adult/s(18+ y.o)(max: %d): ", MAXTRANSACTION);
  result = scanf(" %d", &answer);

  // Check the input data validity
  while (!result || answer < 0 || answer > MAXTRANSACTION)
  {
    while (answer > MAXTRANSACTION)
    {
      printf("\n\t\tSorry, we can transact for maximum of %d members only per transaction", MAXTRANSACTION);
      printf("\n\t\tHow many adults(max: %d): ", MAXTRANSACTION);
      result = scanf(" %d", &answer);
      break;
    }
    puts("\t\tPlease enter valid input\n");
    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }
    printf("\n\t\tHow many adults(max: %d): ", MAXTRANSACTION);
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
    printf("\n\t\tEnter age(18+): ");
    result = scanf(" %d", &age);

    // Check the input data validity
    while (age > 160 || age < 18 || !result)
    {
      if (age < 18)
      {
        printf("\n\t\tAge is too low for adult age(18+)");
      }

      puts("\n\t\tPlease enter valid input\n");
      printf("\n\t\tEnter age(18+): ");
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
    printf("\n\t\tEnter age(%d or lower): ", maxAge);
    result = scanf(" %d", &age);

    // Check the input data validity
    while (age < 0 || age > 18 || !result)
    {
      if (age > 17)
      {
        printf("\n\t\tAge is too high(Must be %d or lower)", maxAge);
      }
      puts("\n\t\tPlease enter valid input\n");
      printf("\n\t\tEnter age(%d or lower): ", maxAge);
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
                    Information *category, int *numMembers)
{
  // If the no. of members reach the maximum no. of members per transaction,
  //   then return to the `buyTicket` function
  if (*numMembers == MAXTRANSACTION)
  {
    return;
  }

  int result;
  int answer = 0;

  // Prompt the user about the no. of children
  printf("\n\t\tHow many children(17-)(max: %d, current %d): ", MAXTRANSACTION, *numMembers);
  result = scanf(" %d", &answer);

  // Check the input data validity
  while (!result || answer < 0 || answer > MAXTRANSACTION)
  {
    while (answer > MAXTRANSACTION - *numMembers)
    {
      printf("\n\t\tSorry, we can transact for maximum of %d members only per transaction", MAXTRANSACTION);
      printf("\n\t\tNo. of available: %d", MAXTRANSACTION - *numMembers);
      printf("\n\t\tHow many children(17-): ");
      result = scanf(" %d", &answer);
      break;
    } // while Loop

    puts("\t\tPlease enter valid input\n");
    if (!result)
    {
      char removeBuffer[100];
      scanf("%s", removeBuffer);
    }

    printf("\n\t\tHow many children(17-): ");
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
                           int *totalMembers)
{
  // For adults
  promptAdult(totalMembers);
  promptAdultAges(arrayTransaction, totalMembers, category);

  //For childrens
  promptChildren(arrayTransaction, category, totalMembers);

  return;
} // promptUserTransaction Function

// It appends the current transactions in the `filePath` text file
void appendTransactionNonReserved(Transactions (*transactionsList)[],
                                  Information *category,
                                  int *totalMember)
{
  FILE *file = fopen(transactionsFile, "a");

  // Loop through each `transactionList` array indeces to get their
  //   information of each transactions
  for (int i = 0; i < *totalMember; i++)
  {
    float price = (*transactionsList)[i].price;
    float tax = price * category->tax;
    fprintf(file, "\n%- 12s %-7d %-15.2f %.2f",
            category->country, (*transactionsList)[i].age,
            (*transactionsList)[i].price, tax);
  } // for Loop

  fclose(file);
  return;
} // appendTransactionNonReserved Function

// It updates the index of `arrayReports` to store the informations from `transacitonList` array
void updateSalesReportNonReserved(Report (*arrayReports)[],
                                  Transactions (*transactionsList)[],
                                  Information *category,
                                  int index, int *totalMembers,
                                  int *totalCountries)
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
  updateSalesReport(arrayReports, *totalCountries);
  return;
} // updateSalesReportNonReserved Function

// It stores the `transactionsList` array's data into `arrayReport` array to track informations
void storeTransactionData(Report (*arrayReport)[],
                          Information *category, Transactions (*transactionsList)[],
                          int *totalMember, int *totalCountries)
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

  // Add the transactions in the `transactionsFile` text file
  appendTransactionNonReserved(transactionsList,
                               category, totalMember);

  // Update the `arrayReport` array and overwrite the `reportFilePath` text file
  //   to track changes in the current program
  updateSalesReportNonReserved(arrayReport, transactionsList,
                               category, index, totalMember,
                               totalCountries);
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
  printf("\n\n\t\tTotal Ticket Price: %.2f", total);
  return;
} // displayPrice Function

// This is the "No Reservation" category from "Buy Ticket" menu
// It prompt the user which destination to choose and tracks the information
//    about the non-reservation transaction
void buyNonReservedTicket(Information (*arrayCategories)[],
                          int *totalCountries, Report (*arrayReport)[],
                          int *total)
{
  system("cls");

  // Display the current available destinations
  printAsterisk();
  puts("\t\tFLIGHT DESTINATION\n");
  for (int i = 0; i < *total; i++)
  {
    printf("\t\t%d. %-19s %d.00\n\n", (i + 1),
           (*arrayCategories)[i].country, (*arrayCategories)[i].price);
  }
  printf("\t\t%d. %s\n", *total + 1, "Return to MAIN\n");
  printAsterisk();

  //Prompt user (Choose categories)
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
  promptUserTransaction(&tempCategory, &transactionList, &totalMember);

  // Display the total amount of current transaction
  displayPrice(&transactionList, totalMember);

  // Prompt the user to proceed
  if (promptUser("\n\t\tProceed to buy the transaction[y/n]? "))
  {
    // if yes, then update the `transactionFilePath` and `reportFilePath` text files,
    //   and the `arrayReport` array to track the informations
    storeTransactionData(arrayReport, &tempCategory,
                         &transactionList, &totalMember,
                         totalCountries);
  }

  return;
} // buyNonReservedTicket Function

// --------------------- For Reserved Ticket -------------------------

// It appends the `filePath` text file with a data from `currentOutput` and `category`
void appendTransactionReserved(CurrentData *category,
                               CurrentOutput *currentOutput)
{
  float price = currentOutput->price;
  float tax = price * category->tax * 0.01;
  FILE *file = fopen(transactionsFile, "a");

  // Append the current reserved transaction in the `filePath` text file
  fprintf(file, "\n%-11s %-7d %-15.2f %.2f",
          category->country, currentOutput->age, currentOutput->price, tax);
  fclose(file);

  return;
} // appendTransactionReserved Function

// It updates the `arrayReports` array to track the data of the current transaction
void updateSalesReportReserved(Report (*arrayReports)[], int index,
                               int tax, CurrentOutput *currentoutput,
                               int *totalCountries)
{
  float finalTax = currentoutput->price * (tax * 0.01);

  // Increment the `index` of `arrayReports` array's amount and tax
  //    to track the total amount of selected destination
  (*arrayReports)[index].amount += currentoutput->price;
  (*arrayReports)[index].tax += finalTax;

  // Invoke the `updateSalesReport` function to overwrite the `reportFilePath` text file
  //   with an updated `arrayReports` infomation
  updateSalesReport(arrayReports, *totalCountries);
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
    printf("\n \t\tError reading data\n");
    return 0;
  }
  else
  {
    return 1;
  }
} // scanData Function

// It stores the reserved transactions data from `filePath` text file into the `arrayReports`,
//    then update the `transactionFilePath` text file, and the `reportFilePath` text file
void storeCodeData(char *filePath,
                   int *totalCountries, Report (*arrayReports)[])
{
  // To track current datas
  CurrentData current;
  CurrentOutput currentoutput;

  // Get the three(3) data (selected country, tax, no. of transaction) and store it in `current` struct
  FILE *file = fopen(filePath, "r");
  int result = fscanf(file, "%s %d %d",
                      current.country, &current.tax, &current.total);

  // check the text file data validity
  if (result != 3)
  {
    fclose(file);
    printf("\n\t\tProblem with reading the data");
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

  // Scan (line by line) the data of `file` text file
  //   and store the current data in the `currentouput`
  while (scanData(file, &currentoutput))
  {
    // Invoke `appendTransactionReserved` function to append the current data
    appendTransactionReserved(&current, &currentoutput);

    // Invoke `updateSalesReportReserved` function to update the `arrayReports`
    //   and overwrite the `reportFilePath` text file with the current data
    updateSalesReportReserved(arrayReports, index, current.tax,
                              &currentoutput, totalCountries);
  }

  // after storing the data from "reserved transaction," Delete the `filePath` text file
  remove(filePath);

  return;
} // storeCodeData Function

// This is the "Reserved" category from "Buy Ticket" menu
// It prompt the user to enter the reservation code,
//   analyze the code if it exist, then ask the user to
//   proceed to buy the reserved ticket
void buyReservedTicket(Information (*arrayCategories)[],
                       int *totalCountries,
                       Report (*arrayReport)[])
{
  system("cls");

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
  strcpy(codeFilePath, databaseRootFile);

  // generate the file path with the current `code`
  generateFilePath(codeFilePath, code);

  // Check if the current generated file doesn't exists
  if (!checkFilePath(codeFilePath))
  {
    printf("\n\t\tThe Code (%d) doesn't exist", code);
    return buyReservedTicket(arrayCategories,
                             totalCountries,
                             arrayReport);
  }

  // Prompt the user to proceed the payment of reserved ticket
  if (promptUser("\n\t\tProceed to buy Ticket[y/n]? "))
  {
    // If proceed,
    //    then store the data from `codeFilePath` text file,
    //    then update the `arrayReport` array
    //    then append the `transactionFilePath` text file
    //    and then overwrite the `reportFilePath` text file to track changes
    storeCodeData(codeFilePath, totalCountries, arrayReport);
  }

  // Return to "Buy Ticket" menu
  puts("\n\t\tPress any KEY to RETURN");
  char some = getch();
  return;
} // buyReservedTicket Function

// ----------------------------- Buy Ticket MENU --------------------------

// This is the main function in this file
// It prompts the user to choose which kind of transaction
//    should be used, either "Reserved" or "No reservation"
// It uses `arrayReports` to track the transaction informations
void buyTicket(Information (*arrayCategories)[],
               Report (*arrayReports)[], unsigned int *total,
               int *totalCountries)
{
  system("cls");
  FLUSH;

  int result;
  char menu[4][100] = {
      "Reserved",
      "No reservation",
      "Return to MAIN"};

  // Displays the "Buy Ticket" Menu
  printSlash();
  printf("\n\t\tBUY TICKET\n");
  for (int i = 0; i < 3; i++)
    printf("\n\t\t%d.] %s\n\n", (i + 1), menu[i]);
  printSlash();

  char choice;
  // Prompt the user to choose which transaction
  printf("\n\n\t\tEnter your Choice: ");
  result = scanf(" %c", &choice);

  // Analyze the `choice`
  switch (choice)
  {
  case '1':
    // if 1, then invoke `buyReservedTicket` function
    buyReservedTicket(arrayCategories,
                      totalCountries,
                      arrayReports);

    buyTicket(arrayCategories, arrayReports,
              total, totalCountries);
  case '2':
    // if 2, then invoke `buyNonReservedTicket` function
    buyNonReservedTicket(arrayCategories,
                         totalCountries, arrayReports,
                         total);

    buyTicket(arrayCategories, arrayReports,
              total, totalCountries);
  case '3':
    // if '3', then return to MAIN MENU
    return;
  default:
    puts("\t\tError, invalid input. try again");
    buyTicket(arrayCategories, arrayReports,
              total, totalCountries);
  } // switch-case conditions
} // buyTicket Function
