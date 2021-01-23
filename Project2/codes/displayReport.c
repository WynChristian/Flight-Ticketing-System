// This function simply display the current data in the `arrayReport`
void displaySalesReport(Report (*arrayReport)[], int total)
{
  system("cls");

  // Checks if the `total` (current total categories) don't have any data
  if (total == 0)
  {
    printf("\nSorry, there's nothing to see here... ");
  }
  else
  {
    // display the current sales report from `arrayReport` array
    printDash();
    printf("\t\t%-14s %-9s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Trave Tax");
    for (int i = 0; i < total; i++)
    {
      printf("\t\t%-14s %-9d %-10.2f %.2f\n\n", (*arrayReport)[i].country,
             (*arrayReport)[i].quantity, (*arrayReport)[i].amount, (*arrayReport)[i].tax);
    }
    printDash();
  }
  puts("\t\tPress any key to RETURN");
  char some = getch();
  // Return to MAIN
  return;
} // displaySalesReport Function