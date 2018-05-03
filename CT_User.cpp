#ifndef _CT_USER_CPP
#define _CT_USER_CPP
#include "CT_User.hpp"
CT_User::CT_User(std::string user) {
  u_name = user;
  MySQL_conn msql = MySQL_conn();
}

//returns true if coin added and not previously in the database, false otherwise
bool CT_User::add_coin(std::string coin_name) {
  //checks if the coin is already in the database before running get_coin_symbol
  msql.MySQL_prep_exe("SELECT IF(coin_name = ?, 0, 1) status FROM CryptoCoin LIMIT 1");
  msql.MySQL_prep()->setString(1, coin_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  if(!exists) {
    std::string coin_symbol = get_coin_symbol(coin_name);
    msql.MySQL_prep_exe("INSERT INTO CryptoCoin VALUES(?,?)");
    msql.MySQL_prep()->setString(1, coin_name);
    msql.MySQL_prep()->setString(2, coin_symbol);
    msql.MySQL_prep()->executeUpdate();
  }
  return exists;
}

//returns true if new user, returns false if existing
bool CT_User::login() {
  //returns 1 if username already exists, 0 if not found
  msql.MySQL_prep_exe("SELECT IF(username = ?, 0, 1) status FROM UserData LIMIT 1");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  //creates user and sets timestamps if new user
  if(!exists) {
    msql.MySQL_prep_exe("INSERT INTO UserData VALUES(?,?,?)");
    msql.MySQL_prep()->setString(1, u_name);
    msql.MySQL_prep()->setInt(2, get_timestamp());
    msql.MySQL_prep()->setInt(3, get_timestamp());
    msql.MySQL_prep()->executeUpdate();
  }

  return exists;
}

//returns true if delete successful, false if coin_id dne
bool CT_User::delete_coinID(int coin_id) {
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

//deletes all records of the current user including user data
void CT_User::delete_curr_user() {
  msql.MySQL_prep_exe("DELETE FROM UserCoinID WHERE u_name = ?");
  msql.MySQL_prep()->setString(1,u_name);
  msql.MySQL_prep()->execute();
  msql.MySQL_prep_exe("DELETE FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1,u_name);
  msql.MySQL_prep()->execute();
}

//adds a record to UserCoinID, returns true if successful and false if the CryptoCoin class for that coin dne
bool CT_User::add_coinID(std::string symbol, int amount) {
  bool exists = false;
  std::string name = coin_name(symbol);
  if(name != "") {
  exists = true;
  msql.MySQL_prep_exe("INSERT INTO UserCoinID (coin_symbol, u_name, add_date, amount, last_price, add_price) VALUES(?,?,?,?,?,?)");
  msql.MySQL_prep()->setString(1, symbol);
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->setInt(3, get_timestamp());
  msql.MySQL_prep()->setInt(4, amount);
  msql.MySQL_prep()->setDouble(5, std::stod(get_price(symbol)));
  msql.MySQL_prep()->setDouble(6, std::stod(get_price(symbol)));
  msql.MySQL_prep()->executeUpdate();
  }
  return exists;
}

//switches the current user to the username in the parameter
//if an empty string is passed does not log a new user in
void CT_User::log_out(std::string user) {
  msql.MySQL_prep_exe("UPDATE UserData SET last_access=? WHERE username=?");
  msql.MySQL_prep()->setInt(1, get_timestamp());
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->executeUpdate();
  msql.MySQL_result(user_coins());
  msql.MySQL_prep_exe("UPDATE UserCoinData SET last_price=? WHERE coin_id =?");

  while(msql.MySQL_fetch()->next()) {
    msql.MySQL_prep()->setDouble(1, curr_price(msql.MySQL_fetch()->getInt(1)));
    msql.MySQL_prep()->setInt(2, msql.MySQL_fetch()->getInt(1));
    msql.MySQL_prep()->executeUpdate();
  }

  if(user != "") {
    u_name = user;
    login();
  }
}

//returns a resultset to retrieve the rows of coin_id for the current user
sql::ResultSet* CT_User::user_coins() {
  msql.MySQL_prep_exe("SELECT coin_id FROM UserCoinID WHERE u_name = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch();
}


//returns timestamp of last time user logged out
long int CT_User::last_access() {
  msql.MySQL_prep_exe("SELECT last_date FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

//returns timestamp of user account creation
long int CT_User::join_date () {
  msql.MySQL_prep_exe("SELECT join_date FROM UserData WHERE username = ?");
  msql.MySQL_prep()->setString(1, u_name);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

//returns timestamp of coinid creation
long int CT_User::coin_start(int coin_id) {
  msql.MySQL_prep_exe("SELECT add_date FROM UserData WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  long int ts = msql.MySQL_fetch()->getInt(1);
  return ts;
}

//returns symbol of coinid
std::string CT_User::coinid_symbol(int coin_id) {
  msql.MySQL_prep_exe("SELECT coin_symbol FROM UserCoinID WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getString("coin_symbol");
}

//returns name of coin given symbol
std::string CT_User::coin_name(std::string coin_symbol) {
  std::string c_name ="";
  msql.MySQL_prep_exe("SELECT IF(coin_symbol = ?, 0, 1) status FROM CryptoCoin LIMIT 1");
  msql.MySQL_prep()->setString(1, coin_symbol);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  bool exists = msql.MySQL_fetch()->getInt(1);

  if(exists) {
    msql.MySQL_prep_exe("SELECT coin_name FROM CryptoCoin WHERE symbol = ?");
    msql.MySQL_prep()->setString(1, coin_symbol);
    msql.MySQL_result(msql.MySQL_prep()->executeQuery());
    c_name =  msql.MySQL_fetch()->getString("coin_name");
  }

  return c_name;
}

//returns amount of coins in a coinid
int CT_User::get_amount(int coin_id) {
  msql.MySQL_prep_exe("SELECT amount FROM UserCoinID WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getInt(1);
}

//returns the current price of 1 coin in USD
double CT_User::curr_price(int coin_id) {
  long int ts = 0;
  return std::stod(get_price(coinid_symbol(coin_id),  ts));
}

//returns the current price of 1 coin from the last day you logged out in USD
double CT_User::last_price(int coin_id) {
  msql.MySQL_prep_exe("SELECT last_price FROM UserCoinID WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getDouble(1);
}

//returns the current price of 1 coin from the day you created the coin in USD
double CT_User::start_price(int coin_id) {
  msql.MySQL_prep_exe("SELECT add_price FROM UserCoinID WHERE coin_id = ?");
  msql.MySQL_prep()->setInt(1, coin_id);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getDouble(1);
}

//returns the current worth of 1 coin in terms of other currencies and timestamps
double CT_User::price_lookup(int coin_id, std::string curr_sym, long int ts) {
  return std::stod(get_price(coinid_symbol(coin_id), curr_sym, ts));
}

//returns the current worth of the amount of cryptocoins in a coinid in USD (amount * price of 1 coin)
double CT_User::curr_worth(int coin_id) {
  return (get_amount(coin_id) * curr_price(coin_id));
}

double CT_User::last_worth(int coin_id) {
  return (get_amount(coin_id) * last_price(coin_id));
}

double CT_User::start_worth(int coin_id) {
  return (get_amount(coin_id) * start_price(coin_id));
}

#endif
