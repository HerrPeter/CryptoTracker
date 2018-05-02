//g++ -Wall -I/usr/include/cppconn -std=c++11 CT_User.hpp -L/usr/lib -lmysqlcppconn -lcurl
#ifndef _CT_USER_HPP
#define _CT_USER_HPP
#include "MySQL_Connect.cpp"
#include "CC_API_Calls.cpp"

class CT_User {
  private:
    std::string u_name;
    MySQL_conn msql;
  public:
    CT_User(std::string user);
    bool add_coin(std::string coin_name);
    bool login();
    bool delete_coinID(int coin_id);
    void delete_curr_user();
    void add_coinID(std::string symbol, int amount);
    void log_out(std::string user);
    sql::ResultSet* user_coins();
    long int last_access();
    long int join_date ();
    long int coin_start(int coin_id);
    std::string coinid_symbol(int coin_id);
    std::string coin_name(int coin_symbol);
};

#include "CT_User.cpp"
#endif
