//g++ -Wall -I/usr/include/cppconn -std=c++11 CT_Data.cpp -L/usr/lib -lmysqlcppconn -lcurl

#include "MySQL_Connect.cpp"
#include "CC_API_Calls.cpp"
#include <string>
#include <iostream>
using namespace std;

string add_coin(MySQL_conn msql, string coin_name) {
  string coin_symbol = get_coin_symbol(coin_name);
  string ret = "The coin was not found.";

  if(coin_symbol != "") {
    ret = "Coin added succesfully.";
    msql.MySQL_prep_exe("INSERT INTO CryptoCoin VALUES(?,?)");
    msql.MySQL_prep()->setString(1, coin_name);
    msql.MySQL_prep()->setString(2, coin_symbol);
    msql.MySQL_prep()->executeUpdate();
  }
  return ret;
}

void add_user(MySQL_conn msql, string uname) {
//  msql.MySQL_exe("INSERT INTO UserData VALUES()");
  msql.MySQL_prep_exe("INSERT INTO UserData VALUES(?,?,?)");
  msql.MySQL_prep()->setString(1, uname);
  msql.MySQL_prep()->setInt(2, get_timestamp());
  msql.MySQL_prep()->setInt(3, get_timestamp());
  msql.MySQL_prep()->executeUpdate();
}

void add_coinID(MySQL_conn msql, int u_id, string symbol, int amount) {
//  string t = to_string(get_timestamp());
//  msql.MySQL_exe("INSERT INTO UserCoinID VALUES(" + symbol + ", " + u_id + ", " + t + ", " + to_string(amount) + ")");
  msql.MySQL_prep_exe("INSERT INTO UserCoinID VALUES(?,?,?,?)");
  msql.MySQL_prep()->setString(1, symbol);
  msql.MySQL_prep()->setInt(2, u_id);
  msql.MySQL_prep()->setInt(3, get_timestamp());
  msql.MySQL_prep()->setInt(4, amount);
  msql.MySQL_prep()->executeUpdate();
}

void log_out(MySQL_conn msql, int u_id) {
//  msql.MySQL_exe("UPDATE UserData SET last_access=" + t + " WHERE id=" + u_id);
  msql.MySQL_prep_exe("UPDATE UserData SET last_access=? WHERE id=?");
  msql.MySQL_prep()->setInt(1, get_timestamp());
  msql.MySQL_prep()->setInt(2, u_id);
  msql.MySQL_prep()->executeUpdate();
}
