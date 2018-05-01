//g++ -Wall -I/usr/include/cppconn -o CT_Setup CryptoTracker_Setup.cpp -L/usr/lib -lmysqlcppconn
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <string>
using namespace std;

bool CC_Setup(string user, string pass);
void MySQL_CC_Setup(sql::Statement *stmt);

int main() {
  char in;
  string usern;
  string passw;

  cout << "\nIn order to use CryptoTracker you need to have a CryptoTracker Database setup."
    << "\nWARNING: If CryptoTracker already exists all data saved in the tables will be lost"
    << "\nWould you like to set up the required database? (y/n): ";
  cin >> in;

  if(in == 'y' || in == 'Y') {
    cout << "\nIn order to setup CryptoTracker it requires an account to be created @localhost"
      << "\nPlease enter a username, and password to an account @localhost for automatic setup"
      << "\nUsername: ";
    cin >> usern;
      cout << "Password: ";
    cin >> passw;
  }

  if(CC_Setup(usern, passw))
    cout << "\nSetup complete!";
  else
    cout << "\nUnable to connect to " << usern << "@localhost";

  cout << endl;
  return 0;
}

bool CC_Setup(string user, string pass) {
  bool ret = true;
  sql::Driver *driver;
  sql::Connection *con;
  sql::Statement *stmt;
  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", user, pass);
  stmt = con->createStatement();

  if(con->isValid())
    MySQL_CC_Setup(stmt);

  else
    ret = false;

  delete con;
  delete stmt;
  return ret;
}

void MySQL_CC_Setup(sql::Statement *stmt) {
  stmt->execute("DROP DATABASE IF EXISTS CryptoTracker");
  stmt->execute("DROP USER IF EXISTS 'CryptoTracker'@'localhost'");
  stmt->execute("CREATE DATABASE CryptoTracker");
  stmt->execute("CREATE USER 'CryptoTracker'@'localhost' IDENTIFIED WITH mysql_native_password BY 'CryptoTracker';");
  stmt->execute("GRANT ALL PRIVILEGES ON CryptoTracker.* TO 'CryptoTracker'@'localhost'");
  stmt->execute("FLUSH PRIVILEGES");
  stmt->execute("USE CryptoTracker");
  stmt->execute("CREATE TABLE CryptoCoin ( coin_name varchar(20), symbol varchar(4), PRIMARY KEY (symbol))");
  stmt->execute("CREATE TABLE UserData ( username varchar(20) NOT NULL, join_date int(10) UNSIGNED, last_date int(10) UNSIGNED, PRIMARY KEY (username))");
  stmt->execute("CREATE TABLE UserCoinID ( coin_id int UNSIGNED NOT NULL AUTO_INCREMENT, coin_symbol varchar(4), u_name varchar(20) NOT NULL, add_date int(10) UNSIGNED, amount int(10), PRIMARY KEY(coin_id), INDEX(coin_symbol), INDEX(u_name), FOREIGN KEY (coin_symbol)  REFERENCES CryptoCoin(symbol), FOREIGN KEY (u_name) REFERENCES UserData(username))");
}
