#ifndef _CT_USER_CPP
#define _CT_USER_CPP

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

//adds a record to UserCoinID
void CT_User::add_coinID(std::string symbol, int amount) {
  msql.MySQL_prep_exe("INSERT INTO UserCoinID (coin_symbol, u_name, add_date, amount) VALUES(?,?,?,?)");
  msql.MySQL_prep()->setString(1, symbol);
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->setInt(3, get_timestamp());
  msql.MySQL_prep()->setInt(4, amount);
  msql.MySQL_prep()->executeUpdate();
}

//switches the current user to the username in the parameter
//if an empty string is passed does not log a new user in
void CT_User::log_out(std::string user) {
  msql.MySQL_prep_exe("UPDATE UserData SET last_access=? WHERE username=?");
  msql.MySQL_prep()->setInt(1, get_timestamp());
  msql.MySQL_prep()->setString(2, u_name);
  msql.MySQL_prep()->executeUpdate();
  if(user != "") {
    u_name = user;
    login();
  }
}

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
std::string CT_User::coin_name(int coin_symbol) {
  msql.MySQL_prep_exe("SELECT coin_name FROM CryptoCoin WHERE symbol = ?");
  msql.MySQL_prep()->setInt(1, coin_symbol);
  msql.MySQL_result(msql.MySQL_prep()->executeQuery());
  return msql.MySQL_fetch()->getString("coin_name");
}

#endif
