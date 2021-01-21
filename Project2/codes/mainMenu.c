/* 
  The `displayMainMenu` function display the main menu
  while it tracks the modifications of the datas
  throughout the program, those datas are the following:
    * arrayCategories
    * arrayReports
    * currentNumCategories
 */
void displayMainMenu(Information (*arrayCategories)[],
                     Report (*arrayReports)[],
                     int *currentNumCategories, int *totalCountries)
{
  // Clear screen
  system("cls");

  // Display the MAIN menu
  printf("\nFLIGHT RESERVATION SYSTEM\n");
  char menu[5][100] = {
      "Manage Destination",
      "Reserve Ticket",
      "Buy Ticket",
      "Sales Report",
      "EXIT"};
  for (int i = 0; i < 5; i++)
    printf("\n%d.] %s", (i + 1), menu[i]);

  // Propmt user to choose
  char choice;
  printf("\nEnter Choice: ");
  choice = getchar();

  // Analyze the `choice` data
  switch (choice)
  {
  case '1':
    // if 1, then call the `manageDestination` function from `codes/manageDestination.c` file
    manageDestination(arrayCategories, currentNumCategories);

    displayMainMenu(arrayCategories,
                    arrayReports, currentNumCategories,
                    totalCountries);

  case '2':
    // if 2, then call the `reserveTicket` function from `codes/reserveTicket.c` file
    reserveTicket(arrayCategories,
                  currentNumCategories);

    displayMainMenu(arrayCategories,
                    arrayReports, currentNumCategories,
                    totalCountries);
  case '3':
    // if 3, then call the `buyTicket` function from `codes/buyTicket.c` file
    buyTicket(arrayCategories,
              arrayReports, currentNumCategories,
              totalCountries);

    displayMainMenu(arrayCategories,
                    arrayReports, currentNumCategories,
                    totalCountries);
  case '4':
    // if 4, then call the `displaySalesReport` function from `codes/displayReport.c` file
    displaySalesReport(arrayReports, *totalCountries);

    displayMainMenu(arrayCategories,
                    arrayReports, currentNumCategories,
                    totalCountries);
  case '5':
    // if 5, stop executing the program
    exit(0);
  default:
    // if its invalid input, display the error and return to Main
    puts("Error, invalid input. try again");
    displayMainMenu(arrayCategories,
                    arrayReports, currentNumCategories,
                    totalCountries);
  }
} // displayMainMenu Function