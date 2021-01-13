/* Mga structs naman to men */
/// Data type siya men na pinagsama samang ibang data type
/// The way na a-access yung structs is by dot (.) or arrow (->) {kung pointer struct siya}
/// like "reportTrack.totalReport;"

/// yung typedef naman ay pang simplifyer lang siya
/// para mas maikli ang pag initialize ng structs
/// e.g.
/// "SalesReport reportTrack;" instead of "struct salesReport reportTrack;"
typedef struct category Category;       // For Destination categories
typedef struct info Information;        // For database of current program
typedef struct currentUser CurrentUser; // For current user's info
typedef struct salesReport SalesReport; // For sales report
typedef struct files Documents;         // For files
typedef struct report Report;
typedef struct totalReport TotalReport;

typedef struct currentData CurrentData;
typedef struct Database CurrentOutput;
typedef struct Database Database;
typedef struct Database Transactions;

struct category
{
  int price;
  int tax;
  char country[50];
};

struct info
{
  int primaryKey;
  char country[50];
  int price;
  float tax;
};

struct currentUser
{
  int destination;
  int age;
  float payment;
};

struct totalReport
{
  unsigned int totalQuantity;
  unsigned int totalAmount;
};

struct report
{
  char country[100];
  unsigned int quantity;
  float amount;
  float tax;
};

struct files
{
  FILE *getDestinations;
  FILE *appendTransaction;
  FILE *salesReport;
  FILE *reservedData;
};

struct currentData
{
  char country[100];
  int tax;
  int total;
};

struct Database
{
  int age;
  float price;
};
