#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include "Account.h"

using namespace std;

int main() {
  Bank system;
  Account accounts;
  int choice;
  string fname, lname;
  long accountNumber;
  float balance, amount;

  cout << "Welcome to the Online Banking System" << endl;

  do {
    cout << "\n\tSelect one option below ";
    cout << "\n\t1. Open an Account";
    cout << "\n\t2. Balance Enquiry";
    cout << "\n\t3. Deposit";
    cout << "\n\t4. Withdrawal";
    cout << "\n\t5. Close an Account";
    cout << "\n\t6. Show All Accounts";
    cout << "\n\t7. Quit" << endl;
    cout << "\nEnter your choice: ";

    cin >> choice;
    cout << "\n";

    switch (choice) {
    case 1:
      cout << "Enter First Name: ";
      cin >> fname;
      cout << "Enter Last Name: ";
      cin >> lname;
      cout << "Enter initial balance: ";
      cin >> balance;
      accounts = system.OpenAccount(fname, lname, balance);
      cout << endl << "Congratulations Your Account Has Been Created." << endl;
      cout << accounts;
      break;

    case 2:
      cout << "Enter Account Number: ";
      cin >> accountNumber;
      accounts = system.BalanceEnquiry(accountNumber);
      cout << endl << "Your Account Details: " << endl;
      cout << accounts;
      break;

    case 3:
      cout << "Enter Account Number: ";
      cin >> accountNumber;
      cout << "Enter Balance: ";
      cin >> amount;
      accounts = system.Deposit(accountNumber, amount);
      cout << endl << "Total amount deposited: " << endl;
      cout << accounts;
      break;

    case 4:
      cout << "Enter Account Number: ";
      cin >> accountNumber;
      cout << "Enter Balance: ";
      cin >> amount;
      accounts = system.Withdraw(accountNumber, amount);
      cout << endl << "Amount Withdrawn: " << endl;
      cout << accounts;
      break;

    case 5:
      cout << "Enter Account Number: ";
      cin >> accountNumber;
      system.CloseAccount(accountNumber);
      cout << endl << "Account has been closed." << endl;
      cout << accounts;

    case 6:
      system.ShowAllAccounts();
      break;

    case 7:
      cout << "Thank you for using our services. Goodbye." << endl;
      break;

    default:
      cout << "\nPlease enter a valid option." << endl;
      exit(0);
    }
  }

  while (choice != 7);

  return 0;

}