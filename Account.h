#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class InsufficientFunds {};
int MIN_BALANCE = 0;

class Account {
  private:
    long accountNumber;
  string firstName;
  string lastName;
  float balance;
  static long NextAccountNumber;

  public:
    Account() {}
  Account(string fname, string lname, float balance);
  long getAccNo() {
    return accountNumber;
  }
  string getFirstName() {
    return firstName;
  }
  string getLastName() {
    return lastName;
  }
  float getBalance() {
    return balance;
  }

  void Deposit(float amount);
  void Withdraw(float amount);
  static void setLastAccountNumber(long accountNumber);
  static long getLastAccountNumber();
  friend ofstream & operator << (ofstream & ofs, Account & acc);
  friend ifstream & operator >> (ifstream & ifs, Account & acc);
  friend ostream & operator << (ostream & os, Account & acc);
};

long Account::NextAccountNumber = 0;

class Bank {
  private:
    map < long, Account > accounts;
  public:
    Bank();
  Account OpenAccount(string fname, string lname, float balance);
  Account BalanceEnquiry(long accountNumber);
  Account Deposit(long accountNumber, float amount);
  Account Withdraw(long accountNumber, float amount);
  void CloseAccount(long accountNumber);
  void ShowAllAccounts();
  ~Bank();
};

Account::Account(string fname, string lname, float balance) {
  NextAccountNumber++;
  accountNumber = NextAccountNumber;
  firstName = fname;
  lastName = lname;
  this -> balance = balance;
}
void Account::Deposit(float amount) {
  balance += amount;
}

void Account::Withdraw(float amount) {
  if ((balance - amount) < MIN_BALANCE)
    throw InsufficientFunds();
  balance -= amount;
}

void Account::setLastAccountNumber(long accountNumber) {
  NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber() {
  return NextAccountNumber;
}

ofstream & operator << (ofstream & ofs, Account & acc) {
  ofs << acc.accountNumber << endl;
  ofs << acc.firstName << endl;
  ofs << acc.lastName << endl;
  ofs << acc.balance << endl;
  return ofs;
}

ifstream & operator >> (ifstream & ifs, Account & acc) {
  ifs >> acc.accountNumber;
  ifs >> acc.firstName;
  ifs >> acc.lastName;
  ifs >> acc.balance;
  return ifs;
}

ostream & operator << (ostream & os, Account & acc) {
  os << "First Name: " << acc.getFirstName() << endl;
  os << "Last Name: " << acc.getLastName() << endl;
  os << "Account Number: " << acc.getAccNo() << endl;
  os << "Balance: " << acc.getBalance() << endl;
  return os;
}

Bank::Bank() {
  Account account;
  ifstream infile;

  infile.open("bank_ledger.txt");
  if (!infile) {
    return;
  }
  while (!infile.eof()) {
    infile >> account;
    accounts.insert(pair < long, Account > (account.getAccNo(), account));
  }
  Account::setLastAccountNumber(account.getAccNo());
  infile.close();
}

Account Bank::OpenAccount(string fname, string lname, float balance) {
  ofstream outfile;
  Account account(fname, lname, balance);
  accounts.insert(pair < long, Account > (account.getAccNo(), account));
  outfile.open("bank_ledger.txt", ios::trunc);
  map < long, Account > ::iterator itr;
  for (itr = accounts.begin(); itr != accounts.end(); itr++) {
    outfile << itr -> second;
  }
  outfile.close();
  return account;
}

Account Bank::BalanceEnquiry(long accountNumber) {
  map < long, Account > ::iterator itr = accounts.find(accountNumber);
  return itr -> second;
}

Account Bank::Deposit(long accountNumber, float amount) {
  map < long, Account > ::iterator itr = accounts.find(accountNumber);
  itr -> second.Deposit(amount);
  return itr -> second;
}

Account Bank::Withdraw(long accountNumber, float amount) {
  map < long, Account > ::iterator itr = accounts.find(accountNumber);
  itr -> second.Withdraw(amount);
  return itr -> second;
}

void Bank::CloseAccount(long accountNumber) {
  map < long, Account > ::iterator itr = accounts.find(accountNumber);
  cout << "Account has been closed." << itr -> second;
  accounts.erase(accountNumber);
}

void Bank::ShowAllAccounts() {
  map < long, Account > ::iterator itr;
  cout << "\nALL ACCOUNTS INCLUDE: " << endl;
  for (itr = accounts.begin(); itr != accounts.end(); itr++) {
    cout << "Account " << itr -> first << endl << itr -> second << endl;
  }
}

Bank::~Bank() {
  ofstream outfile;
  outfile.open("bank_ledger.txt", ios::trunc);
  map < long, Account > ::iterator itr;
  for (itr = accounts.begin(); itr != accounts.end(); itr++) {
    outfile << itr -> second;
  }
  outfile.close();
}