void displaySalesReport(Report (*arrayReport)[], int total)
{
  if (total == 0)
  {
    printf("\nSorry, there's nothing to see here... ");
  }
  else
  {
    printf("%-14s %-9s %-10s %8s\n\n", "Flight", "Quantity", "Amount", "Trave Tax");
    for (int i = 0; i < total; i++)
    {
      printf("%-14s %-9d %-10.2f %.2f\n", (*arrayReport)[i].country, (*arrayReport)[i].quantity, (*arrayReport)[i].amount, (*arrayReport)[i].tax);
    }
  }
  puts("Press any key to RETURN");
  char some = getch();
  return;
}