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
    bool add_coinID(std::string symbol, int amount);
    void log_out(std::string user);
    sql::ResultSet* user_coins();
    long int last_access();
    long int join_date ();
    long int coin_start(int coin_id);
    std::string coinid_symbol(int coin_id);
    std::string coin_name(std::string coin_symbol);
    int get_amount(int coin_id);
    double curr_price(int coin_id);
    double last_price(int coin_id);
    double start_price(int coin_id);
    double price_lookup(int coin_id, std::string curr_sym, long int ts);
    double curr_worth(int coin_id);
    double last_worth(int coin_id);
    double start_worth(int coin_id);
};
#endif
