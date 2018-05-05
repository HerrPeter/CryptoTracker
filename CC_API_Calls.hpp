#ifndef _CC_API_CALLS_HPP
#define _CC_API_CALLS_HPP
#include <string>

class CC_API_Calls {

public:
    CC_API_Calls();
    ~CC_API_Calls();
    static std::string get_price(std::string coin_symbol);
    static std::string get_price(std::string coin_symbol, std::string curr_symbol);
    static std::string get_price(std::string coin_symbol, long int timestamp);
    static std::string get_price(std::string coin_symbol, std::string curr_symbol, long int timestamp);
    static std::string get_coin_symbol(std::string coin_name);
    static long int get_timestamp();
private:
  //void* curl;
};

#endif
