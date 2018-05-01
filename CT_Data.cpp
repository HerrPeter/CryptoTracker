//g++ -Wall -I/usr/include/cppconn -std=c++11 CT_Data.cpp -L/usr/lib -lmysqlcppconn -lcurl

#include "MySQL_Connect.cpp"
#include "CC_API_Calls.cpp"
#include <string>
#include <iostream>
using namespace std;

//returns true if coin added and not previously in the database, false otherwise
bool add_coin(MySQL_conn msql, string coin_name) {
  //checks if the coin is already in the database before running get_coin_symbol
  msql.MySQL_prep_exe("SELECT IF(coin_name = ?, 0, 1) status FROM CryptoCoin LIMIT 1");
  msql.MySQL_prep()->setString(1, coin_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  if(!exists) {
    string coin_symbol = get_coin_symbol(coin_name);
    msql.MySQL_prep_exe("INSERT INTO CryptoCoin VALUES(?,?)");
    msql.MySQL_prep()->setString(1, coin_name);
    msql.MySQL_prep()->setString(2, coin_symbol);
    msql.MySQL_prep()->executeUpdate();
  }
  return exists;
}

//returns true if new user, returns false if existing
bool login(MySQL_conn msql, string uname) {
  //returns 1 if username already exists, 0 if not found
  msql.MySQL_prep_exe("SELECT IF(username = ?, 0, 1) status FROM UserData LIMIT 1");
  msql.MySQL_prep()->setString(1, uname);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  //creates user and sets timestamps if new user
  if(!exists) {
    msql.MySQL_prep_exe("INSERT INTO UserData VALUES(?,?,?)");
    msql.MySQL_prep()->setString(1, uname);
    msql.MySQL_prep()->setInt(2, get_timestamp());
    msql.MySQL_prep()->setInt(3, get_timestamp());
    msql.MySQL_prep()->executeUpdate();
  }

  return exists;
}

//returns true if delete successful, false if coin_id dne
bool delete_coinID(MySQL_conn msql, int coin_id) {
  msql.MySQL_prep_exe("SELECT IF(coin_id = ?, 0, 1) status FROM UserCoinID LIMIT 1");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  if(exists) {
    msql.MySQL_prep_exe("DELETE FROM UserCoinID WHERE coin_id = ?");
    msql.MySQL_prep()->setInt(1, coin_id);
    msql.MySQL_prep()->execute();
  }

  return exists;
}

void delete_curr_user(MySQL_conn msql, string u_name) {
  msql.MySQL_prep_exe("DELETE FROM UserCoinID WHERE u_name = ?");
  msql.MySQL_prep()->setString(1,u_name);
  msql.MySQL_prep()->execute();
  msql.MySQL_prep_exe("DELETE FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1,u_name);
  msql.MySQL_prep()->execute();
}

void add_coinID(MySQL_conn msql, string u_name, string symbol, int amount) {
  msql.MySQL_prep_exe("INSERT INTO UserCoinID (coin_symbol, u_name, add_date, amount) VALUES(?,?,?,?)");
  msql.MySQL_prep()->setString(1, symbol);
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->setInt(3, get_timestamp());
  msql.MySQL_prep()->setInt(4, amount);
  msql.MySQL_prep()->executeUpdate();
}

void log_out(MySQL_conn msql, string u_name) {
  msql.MySQL_prep_exe("UPDATE UserData SET last_access=? WHERE username=?");
  msql.MySQL_prep()->setInt(1, get_timestamp());
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->executeUpdate();
}

/*int **user_coins(string u_name) {
  msql.MySQL_prep_exe("SELECT coin_id FROM UserCoinID WHERE u_name = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_fetch(msql.MySQL_prep->executeQuery());
}*/

long int last_access(MySQL_conn msql, string u_name) {
  msql.MySQL_prep_exe("SELECT last_date FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

long int join_date (MySQL_conn msql, string u_name) {
  msql.MySQL_prep_exe("SELECT join_date FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

long int coin_start(MySQL_conn msql, int coin_id) {
  msql.MySQL_prep_exe("SELECT add_date FROM UserData WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

string coinid_symbol(MySQL_conn msql, int coin_id) {
  msql.MySQL_prep_exe("SELECT coin_symbol FROM UserCoinID WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getString("coin_symbol");
}
