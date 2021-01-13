void displayMainMenu(Documents *files, Information (*arrayCategories)[], Report (*arrayReports)[], int *total, int totalMembers, char *dataRootFile, int *totalCountries, char *transactionFilePath, char *reportFilePath, int maxTransaction)
{
  printf("\nFLIGHT RESERVATION SYSTEM\n");
  char menu[5][100] = {
      "Manage Destination",
      "Reserve Ticket",
      "Buy Ticket",
      "Sales Report",
      "EXIT"};
  for (int i = 0; i < 5; i++)
    printf("\n%d.] %s", (i + 1), menu[i]);

  char choice;
  printf("\nEnter Choice: ");
  choice = getchar();

  switch (choice)
  {
  case '1':
    manageDestination(files->getDestinations, arrayCategories, total);
    displayMainMenu(files, arrayCategories, arrayReports, total, totalMembers, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);

  case '2':
    reserveTicket(dataRootFile, arrayCategories, total, totalMembers);
    displayMainMenu(files, arrayCategories, arrayReports, total, totalMembers, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
    break;
  case '3':
    buyTicket(files, arrayCategories, arrayReports, total, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
    displayMainMenu(files, arrayCategories, arrayReports, total, totalMembers, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
    break;
  case '4':
    displaySalesReport(arrayReports, *totalCountries);
    displayMainMenu(files, arrayCategories, arrayReports, total, totalMembers, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
    break;
  case '5':
    exit(0);
  default:
    puts("Error, invalid input. try again");
    displayMainMenu(files, arrayCategories, arrayReports, total, totalMembers, dataRootFile, totalCountries, transactionFilePath, reportFilePath, maxTransaction);
  }
}