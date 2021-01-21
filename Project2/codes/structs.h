/*
  These are the collection of structs that are used throughout the whole program
  Structures provide a way to group a set of related 
    variables of diverse types into a single unit of memory. 

  The structure as a whole can be referenced by a single name or pointer; 
    the structure members can be accessed individually too. 

  Structures can be passed to functions and returned from functions. 
  They are defined using the keyword `struct`

  Combining `typedef` with `struct` can make code clearer. 

  When you have a variable containing a struct, you can access its fields using the dot operator (.).
  If you have a pointer to a struct, You have to use the arrow operator (->) to access its fields. 
 */

typedef struct category Category; // For Destination categories
typedef struct info Information;  // For database of current program
typedef struct report Report;     // For Sales Report

// For tracking Transactions
typedef struct currentData CurrentData;
typedef struct Database Database;
typedef struct Database CurrentOutput;
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

struct report
{
  char country[100];
  unsigned int quantity;
  float amount;
  float tax;
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
